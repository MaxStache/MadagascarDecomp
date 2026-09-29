[CmdletBinding()]
param(
    [ValidateSet(
        "D3D Debug", "D3D Release", "D3D Metrics",
        "D3D Design Debug", "D3D Design Release", "D3D Design Metrics",
        "OGL Debug", "OGL Release", "OGL Metrics",
        "OGL Design Debug", "OGL Design Release", "OGL Design Metrics")]
    [string]$Configuration = "D3D Release",

    # Delete this configuration's outputs before building.
    [switch]$Rebuild,

    # Delete this configuration's outputs and stop.
    [switch]$Clean,

    # Parallel compiles. Configurations with debug info share one PDB and
    # always compile serially.
    [int]$Jobs = [Environment]::ProcessorCount,

    # Visual C++ Toolkit 2003 root; auto-detected if omitted.
    [string]$ToolkitDir,

    # Windows SDK root (Platform SDK or Windows Kits\10); auto-detected if omitted.
    [string]$WinSdkDir,

    # RenderWare Graphics SDK root; defaults to $env:RWGSDK, then .\rwsdk.
    [string]$RwgSdk,

    # Build /MTd configurations against the single-threaded debug CRT (/MLd).
    # Turned on automatically when libcmtd.lib/libcpmtd.lib are not installed
    # (the toolkit lacks them).
    [switch]$SingleThreadedDebugCrt
)

$ErrorActionPreference = "Stop"
Set-StrictMode -Version 2

$Root     = $PSScriptRoot
$Win32Dir = Join-Path $Root "src\console\game_framework\win32"
# In dependency order; static libraries are linked into the executable.
$Projects = @(
    (Join-Path $Win32Dir "gfcore\gfcore.vcproj"),
    (Join-Path $Root "src\console\plugins\loading_screen\win32\loadingscreen.vcproj"),
    (Join-Path $Win32Dir "game_framework\game_framework.vcproj")
)

# Libraries every VS2003 linker configuration inherits unless it sets $(NoInherit).
$InheritedLibs = "kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib"

# --------------------------------------------------------------------------
# Toolchain discovery
# --------------------------------------------------------------------------

function Find-Toolkit {
    $candidates = @($ToolkitDir, $env:VCToolkitInstallDir,
                    "${env:ProgramFiles(x86)}\Microsoft Visual C++ Toolkit 2003",
                    "$env:ProgramFiles\Microsoft Visual C++ Toolkit 2003")
    foreach ($c in $candidates) {
        if ($c -and (Test-Path (Join-Path $c "bin\cl.exe"))) { return (Resolve-Path $c).Path }
    }
    throw "Visual C++ Toolkit 2003 not found. Pass -ToolkitDir <path>."
}

# Returns @{ Include = @(...); Lib = @(...); Flags = @(...); Name = "..." }
function Find-WinSdk {
    # Era-appropriate Platform SDK: headers work with cl 13.10 unmodified.
    $classic = @($WinSdkDir, $env:MSSdk,
                 "$env:ProgramFiles\Microsoft Platform SDK",
                 "${env:ProgramFiles(x86)}\Microsoft Platform SDK",
                 "$env:ProgramFiles\Microsoft Platform SDK for Windows Server 2003 R2",
                 "${env:ProgramFiles(x86)}\Microsoft Platform SDK for Windows Server 2003 R2")
    foreach ($c in $classic) {
        if ($c -and (Test-Path (Join-Path $c "Include\windows.h"))) {
            return @{ Name = "Platform SDK ($c)"; Include = @("$c\Include"); Lib = @("$c\Lib"); Flags = @() }
        }
    }

    # Windows 10/11 SDK.
    $kits = if ($WinSdkDir) { $WinSdkDir } else { "${env:ProgramFiles(x86)}\Windows Kits\10" }
    $versions = Get-ChildItem (Join-Path $kits "Include") -Directory -ErrorAction SilentlyContinue |
        Where-Object { (Test-Path "$($_.FullName)\um\windows.h") -and
                       (Test-Path "$kits\Lib\$($_.Name)\um\x86\kernel32.lib") } |
        Sort-Object { [version]$_.Name } -Descending
    if (-not $versions) {
        throw "No Windows SDK found. Install the Windows 10/11 SDK (x86 libs) or pass -WinSdkDir <path>."
    }
    $v = $versions[0].Name
    return @{
        Name    = "Windows SDK $v"
        Include = @("$kits\Include\$v\um", "$kits\Include\$v\shared")
        Lib     = @("$kits\Lib\$v\um\x86")
        # Keep the modern headers within what cl 13.10 can parse.
        Flags   = @("/D_WIN32_WINNT=0x0501", "/DWINVER=0x0501", "/DNTDDI_VERSION=0x05010000",
                    "/DWIN32_LEAN_AND_MEAN",
                    "/wd4068",   # unknown pragma
                    "/wd4163",   # not available as an intrinsic function
                    "/wd4616")   # #pragma warning: invalid warning number
    }
}

# --------------------------------------------------------------------------
# Helpers
# --------------------------------------------------------------------------

function Quote([string]$s) {
    if ($s -eq "" -or $s -match '[\s"]') { return '"' + ($s -replace '"', '\"') + '"' }
    return $s
}

# Expands $(VAR) from the environment, as Visual Studio does for unknown macros.
function Expand-Macros([string]$s) {
    return [regex]::Replace($s, '\$\(([^)]+)\)', {
        param($m)
        $val = [Environment]::GetEnvironmentVariable($m.Groups[1].Value)
        if ($null -eq $val) { throw "Unknown macro $($m.Value) in project file." }
        $val
    })
}

function Resolve-ProjPath([string]$projDir, [string]$p) {
    $p = (Expand-Macros $p).Trim()
    if (-not [IO.Path]::IsPathRooted($p)) { $p = Join-Path $projDir $p }
    return [IO.Path]::GetFullPath($p)
}

function Split-List([string]$s, [string]$sep = '[,;]') {
    if (-not $s) { return @() }
    return @($s -split $sep | ForEach-Object { $_.Trim() } | Where-Object { $_ })
}

function Get-Attrs($node) {
    $h = @{}
    if ($node) { foreach ($a in $node.Attributes) { if ($a.Name -ne "Name") { $h[$a.Name] = $a.Value } } }
    return $h
}

$script:TimeCache = @{}
function Get-MTime([string]$path) {
    if (-not $script:TimeCache.ContainsKey($path)) {
        $script:TimeCache[$path] = if (Test-Path -LiteralPath $path) { (Get-Item -LiteralPath $path).LastWriteTimeUtc } else { $null }
    }
    return $script:TimeCache[$path]
}

# --------------------------------------------------------------------------
# vcproj -> command lines
# --------------------------------------------------------------------------

function Get-ClFlags([hashtable]$t, [string]$projDir) {
    $f = New-Object System.Collections.ArrayList
    $known = "AdditionalIncludeDirectories AdditionalOptions AssemblerListingLocation BrowseInformation BrowseInformationFile CompileAs DebugInformationFormat EnableFunctionLevelLinking InlineFunctionExpansion ObjectFile Optimization OptimizeForProcessor PrecompiledHeaderFile PrecompiledHeaderThrough PreprocessorDefinitions ProgramDataBaseFileName RuntimeLibrary StringPooling SuppressStartupBanner UsePrecompiledHeader WarnAsError WarningLevel ExceptionHandling BasicRuntimeChecks RuntimeTypeInfo".Split(' ')
    foreach ($k in $t.Keys) { if ($known -notcontains $k) { throw "Unsupported compiler setting '$k' in project file." } }

    if ($t["SuppressStartupBanner"] -eq "TRUE") { [void]$f.Add("/nologo") }
    switch ($t["Optimization"]) { "0" { [void]$f.Add("/Od") } "1" { [void]$f.Add("/O1") } "2" { [void]$f.Add("/O2") } "3" { [void]$f.Add("/Ox") } }
    switch ($t["InlineFunctionExpansion"]) { "1" { [void]$f.Add("/Ob1") } "2" { [void]$f.Add("/Ob2") } }
    switch ($t["OptimizeForProcessor"]) { "1" { [void]$f.Add("/G5") } "2" { [void]$f.Add("/G6") } "3" { [void]$f.Add("/G7") } }
    foreach ($d in Split-List $t["AdditionalIncludeDirectories"]) { [void]$f.Add("/I" + (Quote (Resolve-ProjPath $projDir $d))) }
    foreach ($d in Split-List $t["PreprocessorDefinitions"] ';') { [void]$f.Add("/D" + (Quote $d)) }
    if ($t["StringPooling"] -eq "TRUE") { [void]$f.Add("/GF") }
    if ($t["ExceptionHandling"] -ne "FALSE") { [void]$f.Add("/EHsc") }
    switch ($t["BasicRuntimeChecks"]) { "1" { [void]$f.Add("/RTCs") } "2" { [void]$f.Add("/RTCu") } "3" { [void]$f.Add("/RTC1") } }
    switch ($t["RuntimeLibrary"]) { "0" { [void]$f.Add("/MT") } "1" { [void]$f.Add($(if ($SingleThreadedDebugCrt) { "/MLd" } else { "/MTd" })) } "2" { [void]$f.Add("/MD") } "3" { [void]$f.Add("/MDd") } "4" { [void]$f.Add("/ML") } "5" { [void]$f.Add("/MLd") } }
    if ($t["EnableFunctionLevelLinking"] -eq "TRUE") { [void]$f.Add("/Gy") }
    if ($t["RuntimeTypeInfo"] -eq "TRUE") { [void]$f.Add("/GR") }
    if ($t["WarningLevel"]) { [void]$f.Add("/W" + $t["WarningLevel"]) }
    if ($t["WarnAsError"] -eq "TRUE") { [void]$f.Add("/WX") }
    switch ($t["DebugInformationFormat"]) { "1" { [void]$f.Add("/Z7") } "3" { [void]$f.Add("/Zi") } "4" { [void]$f.Add("/ZI") } }
    switch ($t["CompileAs"]) { "1" { [void]$f.Add("/TC") } "2" { [void]$f.Add("/TP") } }
    if ($t["ProgramDataBaseFileName"]) {
        $pdb = $t["ProgramDataBaseFileName"]
        if ($pdb -match '[\\/]$') { $pdb += "vc70.pdb" }
        [void]$f.Add("/Fd" + (Quote (Resolve-ProjPath $projDir $pdb)))
    }
    foreach ($o in Split-List $t["AdditionalOptions"] '\s+') { [void]$f.Add($o) }
    # BrowseInformation (.sbr) is skipped: the toolkit has no bscmake.
    return ,$f
}

function Get-Project([string]$vcproj, [string]$config) {
    [xml]$x = Get-Content -LiteralPath $vcproj
    $projDir = Split-Path $vcproj
    $cfgName = "$config|Win32"
    $cfg = $x.VisualStudioProject.Configurations.Configuration | Where-Object { $_.Name -eq $cfgName }
    if (-not $cfg) { throw "$vcproj has no configuration '$cfgName'." }

    $clBase = Get-Attrs $cfg.SelectSingleNode("Tool[@Name='VCCLCompilerTool']")
    $objDir = Resolve-ProjPath $projDir $cfg.IntermediateDirectory
    $pchFile = if ($clBase["PrecompiledHeaderFile"]) { Resolve-ProjPath $projDir $clBase["PrecompiledHeaderFile"] } else { $null }

    $units = @()
    foreach ($file in $x.SelectNodes("//File")) {
        if ($file.RelativePath -notmatch '\.(c|cpp|cxx)$') { continue }
        $fc = $file.SelectSingleNode("FileConfiguration[@Name='$cfgName']")
        if ($fc -and $fc.GetAttribute("ExcludedFromBuild") -eq "TRUE") { continue }

        $cl = $clBase.Clone()
        if ($fc) {
            $over = Get-Attrs $fc.SelectSingleNode("Tool[@Name='VCCLCompilerTool']")
            foreach ($k in $over.Keys) {
                # Empty per-file lists mean "inherit" in VS2003 project files.
                if ($over[$k] -ne "" -or $k -notmatch 'AdditionalIncludeDirectories|PreprocessorDefinitions') { $cl[$k] = $over[$k] }
            }
        }

        $src = Resolve-ProjPath $projDir $file.RelativePath
        $obj = Join-Path $objDir ([IO.Path]::GetFileNameWithoutExtension($src) + ".obj")
        $flags = Get-ClFlags $cl $projDir
        $pchMode = $cl["UsePrecompiledHeader"]
        if ($pchMode -eq "1" -or $pchMode -eq "3") {
            $sw = if ($pchMode -eq "1") { "/Yc" } else { "/Yu" }
            [void]$flags.Add($sw + (Quote $cl["PrecompiledHeaderThrough"]))
            [void]$flags.Add("/Fp" + (Quote $pchFile))
        }
        $units += [pscustomobject]@{
            Source = $src; Obj = $obj; Flags = $flags
            CreatesPch = ($pchMode -eq "1"); UsesPch = ($pchMode -eq "3")
            DebugInfo = [bool]$cl["DebugInformationFormat"]
        }
    }

    $lib  = Get-Attrs $cfg.SelectSingleNode("Tool[@Name='VCLibrarianTool']")
    $link = Get-Attrs $cfg.SelectSingleNode("Tool[@Name='VCLinkerTool']")
    return [pscustomobject]@{
        Name = $x.VisualStudioProject.Name; Dir = $projDir; ObjDir = $objDir
        Type = $cfg.ConfigurationType; Units = $units; Pch = $pchFile
        RuntimeLibrary = $clBase["RuntimeLibrary"]
        Librarian = $lib; Linker = $link
        Output = Resolve-ProjPath $projDir $(if ($cfg.ConfigurationType -eq "4") { $lib["OutputFile"] } else { $link["OutputFile"] })
    }
}

# --------------------------------------------------------------------------
# Compiling
# --------------------------------------------------------------------------

function Test-UpToDate($unit, [string]$cmd) {
    $objTime = Get-MTime $unit.Obj
    $depFile = "$($unit.Obj).d"
    if (-not $objTime -or -not (Test-Path -LiteralPath $depFile)) { return $false }
    $lines = [IO.File]::ReadAllLines($depFile)
    if ($lines.Count -eq 0 -or $lines[0] -ne $cmd) { return $false }
    for ($i = 1; $i -lt $lines.Count; $i++) {
        $t = Get-MTime $lines[$i]
        if (-not $t -or $t -gt $objTime) { return $false }
    }
    return $true
}

# Runs compile tasks with up to $parallel concurrent cl.exe processes.
function Invoke-Compiles($tasks, [int]$parallel, [string]$cwd) {
    $queue = New-Object System.Collections.Queue
    foreach ($t in $tasks) { $queue.Enqueue($t) }
    $running = New-Object System.Collections.ArrayList
    $failed = 0

    while ($queue.Count -gt 0 -or $running.Count -gt 0) {
        while ($queue.Count -gt 0 -and $running.Count -lt $parallel) {
            $t = $queue.Dequeue()
            $psi = New-Object System.Diagnostics.ProcessStartInfo
            $psi.FileName = "cl.exe"
            $psi.Arguments = $t.Args
            $psi.WorkingDirectory = $cwd
            $psi.UseShellExecute = $false
            $psi.RedirectStandardOutput = $true
            $psi.RedirectStandardError = $true
            $psi.CreateNoWindow = $true
            Write-Verbose "cl $($t.Args)"
            $p = [System.Diagnostics.Process]::Start($psi)
            [void]$running.Add(@{ Task = $t; Proc = $p
                                  Out = $p.StandardOutput.ReadToEndAsync()
                                  Err = $p.StandardError.ReadToEndAsync() })
        }

        $done = @($running | Where-Object { $_.Proc.HasExited })
        if ($done.Count -eq 0) { Start-Sleep -Milliseconds 20; continue }

        foreach ($r in $done) {
            [void]$running.Remove($r)
            $r.Proc.WaitForExit()
            $t = $r.Task
            $deps = New-Object System.Collections.Generic.List[string]
            $deps.Add($t.Unit.Source)
            $msgs = @()
            foreach ($line in ($r.Out.Result + $r.Err.Result) -split "`r?`n") {
                if ($line -match '^Note: including file:\s*(.+)$') {
                    $inc = $Matches[1].Trim()
                    if (-not $inc.StartsWith($script:SystemPrefix[0], "OrdinalIgnoreCase") -and
                        -not $inc.StartsWith($script:SystemPrefix[1], "OrdinalIgnoreCase")) { $deps.Add($inc) }
                } elseif ($line.Trim() -and $line.Trim() -ne [IO.Path]::GetFileName($t.Unit.Source)) {
                    $msgs += $line
                }
            }
            if ($t.Unit.UsesPch -and $script:PchFile) { $deps.Add($script:PchFile) }

            $name = [IO.Path]::GetFileName($t.Unit.Source)
            if ($r.Proc.ExitCode -eq 0) {
                Write-Host "  $name"
                $msgs | ForEach-Object { Write-Host "    $_" -ForegroundColor Yellow }
                $all = @($t.Cmd) + ($deps | Select-Object -Unique)
                [IO.File]::WriteAllLines("$($t.Unit.Obj).d", [string[]]$all)
            } else {
                $failed++
                Write-Host "  $name  FAILED" -ForegroundColor Red
                $msgs | ForEach-Object { Write-Host "    $_" -ForegroundColor Red }
                Remove-Item -LiteralPath "$($t.Unit.Obj).d" -ErrorAction SilentlyContinue
            }
            $r.Proc.Dispose()
        }
    }
    return $failed
}

function Build-Objects($proj, [string[]]$extraFlags) {
    New-Item -ItemType Directory -Force $proj.ObjDir | Out-Null
    $script:PchFile = $proj.Pch
    $parallel = if (@($proj.Units | Where-Object DebugInfo).Count -gt 0) { 1 } else { [Math]::Max(1, $Jobs) }

    $mk = {
        param($u)
        $cmd = (@("/c") + $extraFlags + $u.Flags + @("/showIncludes", ("/Fo" + (Quote $u.Obj)), (Quote $u.Source))) -join " "
        [pscustomobject]@{ Unit = $u; Cmd = $cmd; Args = $cmd }
    }

    # The precompiled header must exist before anything that uses it.
    $pchUnits = @($proj.Units | Where-Object CreatesPch)
    $pchStale = $false
    foreach ($u in $pchUnits) {
        $t = & $mk $u
        if (-not (Test-UpToDate $u $t.Cmd) -or -not (Get-MTime $proj.Pch)) {
            $pchStale = $true
            if ((Invoke-Compiles @($t) 1 $proj.Dir) -gt 0) { return $false }
            $script:TimeCache.Clear()
        }
    }

    $todo = @()
    foreach ($u in $proj.Units | Where-Object { -not $_.CreatesPch }) {
        $t = & $mk $u
        if ($pchStale -and $u.UsesPch) { $todo += $t }
        elseif (-not (Test-UpToDate $u $t.Cmd)) { $todo += $t }
    }
    if ($todo.Count -eq 0) {
        if (-not $pchStale) { Write-Host "  (objects up to date)" }
        return $true
    }
    $failed = Invoke-Compiles $todo $parallel $proj.Dir
    $script:TimeCache.Clear()
    if ($failed -gt 0) { Write-Host "$failed file(s) failed to compile." -ForegroundColor Red; return $false }
    return $true
}

# --------------------------------------------------------------------------
# Linking
# --------------------------------------------------------------------------

# Runs link.exe via a response file unless the output is newer than every input
# and the command is unchanged.
function Invoke-Link([string]$output, [string[]]$linkArgs, [string[]]$inputs, [string]$cwd, [string[]]$mode = @()) {
    $rsp = "$output.rsp"
    $body = $linkArgs -join "`r`n"
    $outTime = Get-MTime $output
    if ($outTime -and (Test-Path -LiteralPath $rsp) -and ([IO.File]::ReadAllText($rsp) -eq $body)) {
        $stale = $inputs | Where-Object { $t = Get-MTime $_; $t -and $t -gt $outTime }
        if (-not $stale) { Write-Host "  (up to date)"; return $true }
    }
    New-Item -ItemType Directory -Force (Split-Path $output) | Out-Null
    [IO.File]::WriteAllText($rsp, $body)
    Write-Verbose "link @$rsp`n$body"
    Push-Location $cwd
    try { & link.exe @mode "@$rsp" | ForEach-Object { Write-Host "    $_" } } finally { Pop-Location }
    if ($LASTEXITCODE -ne 0) {
        Remove-Item -LiteralPath $rsp -ErrorAction SilentlyContinue
        return $false
    }
    Write-Host "  -> $output"
    return $true
}

function Build-Library($proj) {
    # The toolkit has no lib.exe; "link /lib" is the same tool (/lib must come first).
    $linkArgs = @("/nologo", ("/OUT:" + (Quote $proj.Output))) + @($proj.Units | ForEach-Object { Quote $_.Obj })
    return Invoke-Link $proj.Output $linkArgs @($proj.Units.Obj) $proj.Dir @("/lib")
}

function Build-Executable($proj, [string[]]$depLibs) {
    $l = $proj.Linker
    $a = New-Object System.Collections.ArrayList
    [void]$a.Add("/OUT:" + (Quote $proj.Output))
    if ($l["SuppressStartupBanner"] -eq "TRUE") { [void]$a.Add("/nologo") }
    switch ($l["LinkIncremental"]) { "1" { [void]$a.Add("/INCREMENTAL:NO") } "2" { [void]$a.Add("/INCREMENTAL") } }
    if ($l["GenerateDebugInformation"] -eq "TRUE") { [void]$a.Add("/DEBUG") }
    if ($l["ProgramDatabaseFile"]) { [void]$a.Add("/PDB:" + (Quote (Resolve-ProjPath $proj.Dir $l["ProgramDatabaseFile"]))) }
    switch ($l["SubSystem"]) { "1" { [void]$a.Add("/SUBSYSTEM:CONSOLE") } "2" { [void]$a.Add("/SUBSYSTEM:WINDOWS") } }
    [void]$a.Add("/MACHINE:X86")
    foreach ($d in Split-List $l["AdditionalLibraryDirectories"]) { [void]$a.Add("/LIBPATH:" + (Quote (Resolve-ProjPath $proj.Dir $d))) }
    foreach ($n in Split-List $l["IgnoreDefaultLibraryNames"]) { [void]$a.Add("/NODEFAULTLIB:$n") }
    if ($SingleThreadedDebugCrt) {
        # Prebuilt libraries (RenderWare debug libs) and /MTd dependency projects
        # still request the MT debug CRT, even when this project itself is /MT.
        [void]$a.Add("/NODEFAULTLIB:libcmtd.lib")
        [void]$a.Add("/NODEFAULTLIB:libcpmtd.lib")
    }
    foreach ($o in Split-List $l["AdditionalOptions"] '\s+') { [void]$a.Add($o) }
    foreach ($u in $proj.Units) { [void]$a.Add((Quote $u.Obj)) }
    foreach ($d in $depLibs) { [void]$a.Add((Quote $d)) }
    foreach ($lib in (Split-List $l["AdditionalDependencies"] '\s+') + (Split-List $InheritedLibs '\s+')) { [void]$a.Add($lib) }
    return Invoke-Link $proj.Output $a (@($proj.Units.Obj) + $depLibs) $proj.Dir
}

# --------------------------------------------------------------------------
# Main
# --------------------------------------------------------------------------

$tk  = Find-Toolkit
$sdk = Find-WinSdk
if (-not $RwgSdk) { $RwgSdk = if ($env:RWGSDK) { $env:RWGSDK } else { Join-Path $Root "rwsdk" } }
if (-not (Test-Path (Join-Path $RwgSdk "include"))) { throw "RenderWare SDK not found at '$RwgSdk'. Set `$env:RWGSDK or pass -RwgSdk." }
$env:RWGSDK = (Resolve-Path $RwgSdk).Path

$env:PATH    = "$tk\bin;$env:PATH"
$env:INCLUDE = (@("$tk\include") + $sdk.Include) -join ";"
$env:LIB     = (@("$tk\lib") + $sdk.Lib) -join ";"
$script:SystemPrefix = @("$tk\", ((Split-Path $sdk.Include[0]) + "\"))

# Fall back to the single-threaded debug CRT when the MT one isn't installed
# (the free toolkit omits it; a full VS .NET 2003 install has it).
$hasMtDebugCrt = [bool]($env:LIB -split ';' | Where-Object { $_ -and (Test-Path (Join-Path $_ "libcmtd.lib")) -and (Test-Path (Join-Path $_ "libcpmtd.lib")) })
if (-not $hasMtDebugCrt -and -not $SingleThreadedDebugCrt) { $SingleThreadedDebugCrt = [switch]$true; $autoStCrt = $true } else { $autoStCrt = $false }

$projs = $Projects | ForEach-Object { Get-Project $_ $Configuration }

if ($Clean -or $Rebuild) {
    foreach ($p in $projs) {
        Remove-Item -LiteralPath $p.ObjDir -Recurse -Force -ErrorAction SilentlyContinue
        foreach ($f in @($p.Output, "$($p.Output).rsp")) { Remove-Item -LiteralPath $f -Force -ErrorAction SilentlyContinue }
    }
    Write-Host "Cleaned [$Configuration]."
    if ($Clean) { exit 0 }
}

Write-Host "Configuration: $Configuration"
Write-Host "Compiler:      $tk"
Write-Host "Windows SDK:   $($sdk.Name)"
Write-Host "RenderWare:    $env:RWGSDK"
if ($autoStCrt -and @($projs | Where-Object { $_.RuntimeLibrary -eq "1" }).Count -gt 0) {
    Write-Host "Note:          libcmtd.lib/libcpmtd.lib not found; using the single-threaded debug CRT (/MLd)." -ForegroundColor Yellow
}
$sw = [Diagnostics.Stopwatch]::StartNew()

$depLibs = @()
foreach ($p in $projs) {
    Write-Host "`n== $($p.Name)" -ForegroundColor Cyan
    if (-not (Build-Objects $p $sdk.Flags)) { Write-Host "`nBuild FAILED." -ForegroundColor Red; exit 1 }
    $ok = if ($p.Type -eq "4") { Build-Library $p } else { Build-Executable $p $depLibs }
    if (-not $ok) { Write-Host "`nBuild FAILED ($($p.Name) link)." -ForegroundColor Red; exit 1 }
    if ($p.Type -eq "4") { $depLibs += $p.Output }
}

Write-Host ("`nBuild succeeded in {0:N1}s: {1}" -f $sw.Elapsed.TotalSeconds, $projs[-1].Output) -ForegroundColor Green
