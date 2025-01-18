#include <stdio.h>
#include <stdlib.h>
#include "individu.h"


int main(){
  char* s1=(char*)malloc(10);
  char* s2=(char*)malloc(10);
  printf("Saisir s1 puis s2\n");
  scanf("%s", s1);
  scanf("%s", s2);
  printf("Inclusion de s1 et s2 %f, soit %f pour cent \n",inclusion(s1,s2),inclusion(s1,s2)*100);
}

