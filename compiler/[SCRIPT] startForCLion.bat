cd cmake-build-visual-studio
set program=compiler.exe
echo. > ..\result.txt

%program% ..\testRustProgramm.rs >> ..\result.txt