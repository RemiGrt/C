

mainP1.out : mainP1.o arbre.o
	gcc mainP1.o arbre.o -o mainP1.out 

arbre.o : arbre.c arbre.h
	gcc -c arbre.c

mainP1.o : mainP1.c arbre.h
	gcc -c mainP1.c

clean :
	rm *.o
