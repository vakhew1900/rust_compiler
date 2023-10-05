set program=flex.exe

%program% lex.l

ren lex.yy.c lex.yy.cpp