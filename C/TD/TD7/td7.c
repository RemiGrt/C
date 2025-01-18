#include <stdio.h>
#include <string.h>


void displayString(char *tab){
  int i=0;
  while(tab[i]!='\0'){
    printf("%c",tab[i]);
    i++;
  }
  printf(" Taille sans \\0:%d\n",i);
  printf("\n");
}

int main(){

  char car[10]="Hello!";
  char bob[50]= "Hello!";
  printf("Strlen: %ld sizeof: %ld\n", strlen(bob),sizeof(bob));
  
  char car2[]="      ";
  char car3[]="Car3           ";
  
  //STRLEN
  printf("Strlen car: %ld\n",strlen(car));
  printf("Sizeof car: %ld\n",sizeof(car));

  //STRCPY
  strcpy(car2, car);
  displayString(car); 
  displayString(car2);
  
  // STRCAT
  strcat(car3, car);
  displayString(car3);

 
}
