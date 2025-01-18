# Chemin vers les fichiers headers
HEAD = ./head
LIB = ./lib
######################  EX1  ######################################
# -lm inclus la librairie math
td6_ex1 : td6_ex1.o libfonc.o
	gcc td6_ex1.o libfonc.o -o td6_ex1 -lm

# -I donne le chemin vers les headers
# inutile de les préciser si ils sont das le dossier courant  
td6_ex1.o : td6_ex1.c $(HEAD)/struct.h
	gcc -c td6_ex1.c -I$(HEAD)

libfonc.o : $(LIB)/libfonc.c $(HEAD)/struct.h
	gcc -c $(LIB)/libfonc.c -I$(HEAD)

######################  EX2 ######################################
# Generation du Binaire (edition de lien)
td6_ex2: td6_ex2.o libfonc2.o
	gcc td6_ex2.o libfonc2.o -o td6_ex2
# generation objet (Complilation)
libfonc2.o: $(LIB)/libfonc2.c $(HEAD)/ex2.h
	gcc -c $(LIB)/libfonc2.c -I$(HEAD)  
# generation objet (Complilation)
td6_ex2.o: td6_ex2.c $(HEAD)/ex2.h
	gcc -c td6_ex2.c -I$(HEAD)	

###################################################################
clean:
	rm -rf *.o

mproper:
	rm -rf a.out *.o
