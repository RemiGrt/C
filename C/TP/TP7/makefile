# Var
H = ./head
F = ./fonc
IH = -I./head

mainP3.out : mainP3.o individu.o score.o
	gcc mainP3.o individu.o score.o -o mainP3.out

mainP2.out : mainP2.o individu.o score.o
	gcc mainP2.o individu.o score.o -o mainP2.out

mainP1.out : mainP1.o individu.o
	gcc mainP1.o individu.o -o mainP1.out

tp7 : tp7.o individu.o 
	gcc tp7.o individu.o -o tp7


mainP1.o : mainP1.c individu.h
	gcc -c mainP1.c

mainP2.o : mainP2.c individu.h
	gcc -c mainP2.c

mainP3.o : mainP3.c individu.h
	gcc -c mainP3.c

tp7.o : tp7.c individu.h
	gcc -c tp7.c

individu.o : individu.c individu.h
	gcc -c individu.c 

score.o : score.c individu.h
	gcc -c score.c

clean:
	rm *.o
