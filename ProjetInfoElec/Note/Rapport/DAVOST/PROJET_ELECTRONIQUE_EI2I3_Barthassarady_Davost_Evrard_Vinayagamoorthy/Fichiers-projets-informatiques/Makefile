# options de compilation
CC = gcc
CCFLAGS = -Wall
LIBS = -lX11 
LIBSDIR = -L/usr/X11R6/lib

# fichiers du projet
SRC = vm_codops.c asm.c
OBJ = $(SRC:.c=.o)
EXEC = run.out

# tt les fichier de la liste de dépendance
Gsept: vm_codops.o asm.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LIBS) $(LIBSDIR)
asm.o: asm.c asm.h
vm_codops.o: vm_codops.c vm_codops.o

#< 1er fichier de la liste de dépendance
vm_codops.o: vm_codops.c vm_codops.o
	$(CC) $(CCFLAGS) -o $@ -c $<


