
asm : mainASM.o asm.o
	  gcc -o $@ $^

asm.o : asm.c asm.h
	    gcc -o $@ -c $< -Wall
	    
mainASM.o : mainASM.c asm.h vm_codops.h
			gcc -o $@ -c $< -Wall

clean :
	rm -f *.o asm
