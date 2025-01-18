# Var
H = ./head

# Edition de lien
TP4 : TP4.o lecture.o affichage.o deplace.o
	gcc TP4.o lecture.o affichage.o deplace.o \
	-lX11 -L/usr/X11R6/lib -o TP4

lecture.o : lecture.c $(H)/affichage.h
	gcc -c lecture.c -I$(H) 

affichage.o : affichage.c $(H)/affichage.h 
	gcc -c affichage.c -I$(H) -lX11 -L/usr/X11R6/lib

deplace.o : deplace.c $(H)/affichage.h
	gcc -c deplace.c -I$(H)

TP4.o : TP4.c $(H)/lecture.h $(H)/affichage.h
	gcc -c TP4.c -I$(H) 


clean :
	rm -rf *.o

mproper :
	rm TP4
