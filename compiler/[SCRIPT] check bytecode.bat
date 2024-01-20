set "destination_folder=.\cmake-build-visual-studio\code_generation\src"
cd %destination_folder%
"C:\Program Files\Java\jdk-17.0.2\bin\javap.exe" -verbose ModuleClass.class 
pause