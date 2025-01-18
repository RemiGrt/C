
# Var
H = ../vm

asm: asm.o
	gcc asm.o -o asm

asm.o: asm.c $(H)/vm_codops.h
	gcc -c asm.c -I$(H)


clean:
	rm asm.o
assembleur:
	gcc -S asm.c -I$(H)
