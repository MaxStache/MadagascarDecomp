
@echo off
setlocal

set "VERBOSE="
set "VTABLE="

:parse_args
if "%~1"=="" goto args_done

if "%~1"=="--vtable" (
    set "VTABLE=1"
) else (
    set "VERBOSE=%~1"
)

shift
goto parse_args

:args_done
echo BUILDING...

python .\tools\build.py --pdb --keep-unused --define DECOMP_ENABLE_CONSOLE --define DECOMP_DEBUG_WINDOWED
if errorlevel 1 (
    echo BUILD FAILED - skipping reccmp.
    exit /b 1
)

call ".\.venv\Scripts\activate.bat"
pushd ".\src\console\game_framework\win32\bin\Win32 D3D Release"

echo CHECKING...
if "%VERBOSE%"=="" (
    REM --svg-icon "%~dp0assets\GameIcon.png" --svg "%~dp0progress.svg"
    reccmp-reccmp --target GAME --total 8244 --nolib --html "%~dp0report.html"
) else (
    reccmp-reccmp --target GAME --verbose %VERBOSE%
)

if "%VTABLE%"=="1" (
    echo CHECKING VTABLES...
    reccmp-vtable --target GAME
)

popd
endlocal