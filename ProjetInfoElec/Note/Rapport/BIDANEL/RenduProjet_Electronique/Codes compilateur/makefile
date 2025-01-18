all : main vm_codops asm



#Assembleur

vm_codops : vm_codops.o

	gcc -o $@ $^  -Wall

vm_codops.o: vm_codops.c  vm_codops.h 

	gcc -o $@ -c $< -Wall



#Grafcet

main : main.o

	gcc -o $@ $^  -Wall

main.o : main.c

	gcc -o $@ -c $< -Wall



#Assembleur_2

asm : asm.o

	gcc -o $@ $^  -Wall

asm.o: asm.c

	gcc -o $@ -c $< -Wall