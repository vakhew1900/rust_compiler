del lexer.c
del simple_tab.h
del simple_tab.c
flex.exe simple.flex.txt
move lex.yy.c lexer.c
bison.exe -d simple.y