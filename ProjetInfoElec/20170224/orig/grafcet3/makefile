debug: y.tab.o lex.yy.o ast.o
	gcc y.tab.o lex.yy.o ast.o -o debug
y.tab.o: y.tab.c
	gcc -c y.tab.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
ast.o: ast.c
	gcc -c ast.c

rundebug:
	./debug < safe.grafcet
