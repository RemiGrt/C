all : vm grafcet assembleur

assembleur : assembleur.o
	gcc -Wall -o $@ $^
	
assembleur.o : assembleur.c assembleur.h
	gcc -Wall -o $@ -c $<

vm : vm.o
	gcc -Wall -o $@ $^
	
vm.o : vm.c vm_codops.h
	gcc -Wall -o $@ -c $<
	
grafcet : grafcet.o
	gcc -Wall -o $@ $^
	
grafceet.o : grafcet.c
	gcc -Wall -o $@ -c $<
