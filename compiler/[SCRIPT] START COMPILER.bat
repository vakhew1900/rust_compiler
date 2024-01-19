@echo off
setlocal

rem Проверка наличия аргумента (имени файла)
if "%1"=="" (
    set /p filename=Enter filename: 
    if not exist ".\tests\%filename%" (
        echo The specified file "%filename%" does not exist.
        pause
        exit /b 1
    )
) else (
    set "filename=%1"
)

set "source_folder=.\tests"
set "compiler_folder=.\cmake-build-visual-studio"
set "destination_folder=.\cmake-build-visual-studio\code_generation\src"

rem Запуск compiler.exe с передачей файла в аргументах
cd %compiler_folder%
compiler.exe ..\%source_folder%\%filename%

cd ..\

rem Копирование файла RTL.class в целевую папку
copy .\Rust_RTL\RTL.class %destination_folder%

rem Переход в целевую папку и запуск
cd %destination_folder%
echo.
echo ===OUTPUT===
echo.
java -noverify -classpath . ModuleClass

endlocal
pause
