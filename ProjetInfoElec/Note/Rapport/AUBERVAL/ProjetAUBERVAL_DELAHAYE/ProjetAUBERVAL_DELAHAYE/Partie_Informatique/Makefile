# Var
IH = -I./ast

###### Grafcet ###############
grafcet.out : y.tab.o lex.yy.o ast.o
	gcc y.tab.o lex.yy.o ast.o -o $@

ast.o : ./ast/ast.c ./ast/ast.h
	gcc -c ./ast/ast.c $(IH)

y.tab.o : ./bison/y.tab.c ./bison/y.tab.h ./ast/ast.h
	gcc -c ./bison/y.tab.c -I./bison $(IH)

lex.yy.o : ./lex/lex.yy.c ./ast/ast.h ./bison/y.tab.h
	gcc -c ./lex/lex.yy.c -I./bison $(IH)

######## Assembleur ##################
asm.out : ./asm/asm.c ./asm/asm.h ./vm/
	gcc ./asm/asm.c -I./asm/ -I./vm -o  $@

cleano :
	rm -f *.o
cleanout :
	rm -f *.out


