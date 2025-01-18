#include <stdio.h>
#include <stdlib.h>


int strcmp1(char* s1, char* s2){
  int cpt=0;
  int i=0;
  while(s1[i]!='\0' || s2[i]!='\0'){
    if(s1[i]>s2[i]){
      cpt=1;
      break;
    }
    else if(s1[i]<s2[i]){
      cpt=-1;
      break;
    }
    i++;
  }
  return cpt;
}

int strcmp2(char* s1, char* s2){
  int cpt=0;
  int i=0;
  while(*s1!='\0' || *s2!='\0'){
    if(*s1>*s2){
      cpt=1;
      break;
    }
    else if(*s1 < *s2){
      cpt=-1;
      break;
    }
    s1++;
    s2++;
  }
  return cpt;
}

char* strchrCustom(char* s1, char c){
  while(*s1!='\0'){
    if(*s1==c){
      return s1;
    }
    s1++;
  }
  return NULL;
}

// Recherche target dans str
char* strstr(char* str, char* target){
  char* start;
  start=strchrCustom(str,*target);
  printf("strstr start %p %c\n",start, *start); 
  if(start!=NULL){
    if(strcmp2(start, target)==0){
      return start;
    }else{
      return NULL;
    }
  }else{
    printf("Le premier car de target ne correspond à aucun de str\n");
    return NULL;
  }
}


void upper(char* str){
/* boucle tant qu’on n’est pas arrivé à la fin de la chaine */
while (*str){
  /* test si on peut mettre en majuscule */
  if (*str>='a' && *str<='z')
    /* on rajoute la différence entre maj et min */
    *str += 'A'-'a';
  /* on passe au caractère suivant */
  str++;
 }
}

unsigned int strlen2( char* s){
  unsigned int i;
  for( i=0; s[i]!='\0'; i++);
  return i;
}

void verlan(char* str){
  int cpt=0;
  char temp;
  for(int i=strlen2(str);i>cpt;i--){
    temp=*(str+cpt);
    *(str+cpt)=*(str+i-1);
    *(str+i-1)=temp;
    cpt++;
  }
}

int main(){

  char* chaine1=malloc(50);
  char* chaine2=malloc(50);
  printf("Chaine 1 puis chaine2:");
  scanf("%s %s",chaine1,chaine2);
  //
  printf("strcmp1 %d\n",strcmp1(chaine1,chaine2));
  printf("strcmp2 %d\n",strcmp2(chaine1,chaine2));
  printf("strchrCustom (cherche a) %p \n", strchrCustom(chaine1, 'a'));
  
  printf("strstr %p\n",strstr(chaine1,chaine2));
  //
  upper(chaine1);
  printf("upper %s\n", chaine1);
  printf("Ex4 Chaine 1:");
  scanf("%s", chaine1);
  printf("Chaine1: %s\n",chaine1);
  verlan(chaine1);
  printf("Chaine1: %s\n",chaine1);
}
