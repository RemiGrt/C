#include <stdio.h>
int a = 27;
int chose(int a); 
int machin();
int chose(int a) { return a+17+machin(); }
int machin() { return a; }
int main() { 
int a = 1; // a = 1
a = chose(a); //a = 1+17+27=45
printf("%d\n", a); 
return 0; 
}