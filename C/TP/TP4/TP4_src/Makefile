# options de compilation
CC = gcc
CCFLAGS = -Wall -I/opt/X11/include/
LIBS = -lX11
LIBSDIR = -L/opt/X11/lib/

# fichiers du projet
SRC = labyrinthe.c lecture.c affichage.c
OBJ = $(SRC:.c=.o)
EXEC = laby.out


# règle initiale
all: $(EXEC)

# règles de compilation
lecture.o: lecture.h
labyrinthe.o: lecture.h
affichage.o: affichage.h
%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<
	
# règles d'édition de liens
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(LIBSDIR)

# règles supplémentaires
clean:
	#rm -f *.o
	ls $(OBJ)
mproper:
	rm -f $(EXEC) *.o
