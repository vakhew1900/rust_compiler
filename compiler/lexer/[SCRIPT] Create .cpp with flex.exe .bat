set program=flex.exe

%program% lex.l
del lex.yy.cpp
ren lex.yy.c lex.yy.cpp