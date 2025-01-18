#repertoire
#VPATH=lib

#option de compilation
CC = gcc
LIBS = -llib
DIR = ./lib

main: main.o affiche.o
	$(CC) $(DIR)/affiche.o main.o -o main 

affiche.o: affiche.h affiche.c
	$(CC) -c $(DIR)/affiche.c -o $(DIR)/affiche.o

#regle supplementaire
clean:
	rm -rf *.o
	rm -rf $(DIR)/*.o
