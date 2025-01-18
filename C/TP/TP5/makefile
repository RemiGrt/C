# Var
H = ./head
F = ./fonc
IH = -I./head

tp5 : tp5.o carte.o partie.o
	gcc tp5.o carte.o partie.o -o tp5

tp5.o : tp5.c $(H)/carte.h $(H)/partie.h
	gcc -c tp5.c $(IH)

carte.o : $(F)/carte.c $(H)/carte.h
	gcc -c $(F)/carte.c $(IH)

partie.o : $(F)/partie.c $(H)/partie.h
	gcc -c $(F)/partie.c $(IH)
