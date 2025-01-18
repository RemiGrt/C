#=====================================
#
#        oO  ARBRE   Oo
#
#=====================================
#
# File : Makefile
# Date : 26 nov 10
# Author : Hilaire Thibault
#
#=====================================


# options de compilation
CC = gcc
CCFLAGS = -Wall -g -lm
LIBS = 
LIBSDIR = 

# 1ère règle
all: P1.out P2.out P3.out

# règles de compilation
arbre.o: arbre.h
lectureInfixee.o: lectureInfixee.h arbre.h
equation.o: arbre.h
mainP1.o: arbre.h
mainP2.o: arbre.h lectureInfixee.h equation.h
mainP3.o: arbre.h lectureInfixee.h equation.h

%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<
# règles d'édition de liens
P1.out: mainP1.o arbre.o
	$(CC) $(CCFLAGS) -o $@ $^
P2.out: mainP2.o arbre.o lectureInfixee.o equation.o
	$(CC) $(CCFLAGS) -o $@ $^ -lm
P3.out: mainP3.o arbre.o lectureInfixee.o equation.o
	$(CC) $(CCFLAGS) -o $@ $^ -lm
# règles supplémentaires
clean:
	rm -f *.o *.out
