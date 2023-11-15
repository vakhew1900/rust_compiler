@echo off
set /p filename=Enter filename: 
if "%filename%"=="" (
    echo U didnt enter filename.
) else (
    "./cmake-build-visual-studio/compiler.exe" "./tests/%filename%"
)
pause