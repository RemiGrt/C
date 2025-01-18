# options de compilation
CC = gcc
CCFLAGS = -Wall
LIBS = 
LIBSDIR = 

# 1ère règle
all: P1.out P2.out P3.out P4.out

# règles de compilation
individu.o: individu.h score.h
mainP1.o: individu.h 
mainP2.o: score.h
mainP3.o: individu.h score.h

%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<
	
# règles d'édition de liens
P1.out: individu.o mainP1.o score.o
	$(CC) $(CCFLAGS) -o $@ $^
P2.out: score.o mainP2.o score.o
	$(CC) $(CCFLAGS) -o $@ $^
P3.out: score.o individu.o mainP3.o
	$(CC) $(CCFLAGS) -o $@ $^
P4.out: score.o individu.o mainP4.o
	$(CC) $(CCFLAGS) -o $@ $^
	
	
# règles supplémentaires
clean:
	rm -f *.o *.out
