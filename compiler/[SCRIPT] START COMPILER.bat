@echo off
setlocal enabledelayedexpansion

:input_filename
rem Проверка наличия аргумента (имени файла)
if "%1"=="" (
    set /p filename=Enter filename:
    if not exist ".\tests\!filename!" (
        echo The specified file "!filename!" does not exist.
        pause
        goto :input_filename
    )
) else (
    set "filename=%1"
)

set "source_folder=.\tests"
set "compiler_folder=.\cmake-build-visual-studio"
set "destination_folder=.\cmake-build-visual-studio\code_generation\src"

rem Запуск compiler.exe с передачей файла в аргументах
cd %compiler_folder%
compiler.exe ..\%source_folder%\!filename!

rem Проверка кода возврата compiler.exe
if !errorlevel! neq 0 (
    echo Error: compiler.exe exited with non-zero status.
    pause
    goto :end_script
)

cd ..\

rem Копирование файла RTL.class в целевую папку
copy .\Rust_RTL\RTL.class %destination_folder%

rem Переход в целевую папку и запуск
cd %destination_folder%
echo.
echo ===============OUTPUT====START======================
echo.
java -noverify -classpath . ModuleClass

echo.
echo ===============OUTPUT====FINISH=====================
echo.
goto :file_end

rem когда вылетаю по ошибке то вновь оказываюсь на уровне директории compiler
:end_script
rem echo an errorlevel
cd ..\
goto :input_filename

:file_end
rem echo file_end
cd ..\..\..\
goto :input_filename
endlocal
