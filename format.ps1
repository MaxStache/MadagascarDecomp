$cf = "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\bin\clang-format.exe"

$exclude = @(
    "$PWD\rwsdk\*"
)

$files = @(Get-ChildItem -Recurse -Include *.c,*.cpp,*.h | Where-Object {
    $path = $_.FullName
    -not ($exclude | Where-Object { $path -like $_ })
})

$i = 0
foreach ($f in $files) {
    $i++
    Write-Progress -Activity "clang-format" -Status "$i / $($files.Count): $($f.Name)" -PercentComplete ($i / $files.Count * 100)
    & $cf -i --style=file $f.FullName
}
Write-Progress -Activity "clang-format" -Completed
Write-Host "Formatted $($files.Count) files."