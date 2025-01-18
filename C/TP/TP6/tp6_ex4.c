#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG 0

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

void verlan2(char* str, int start, int stop){
  int cpt=0;
  char temp;
  for(int i=stop+1;i>start+cpt;i--){
    temp=*(str+start+cpt);
    *(str+cpt+start)=*(str+i-1);
    *(str+i-1)=temp;
    cpt++;
  }
}

void decoupe(char* str){
  int start=0;
  int stop=0;
  
  int cpt=0;
  char temp;
  for(int j=0;j<=strlen(str);j++){
    
    if(DEBUG)printf("Decoupe j %d %c\n",j,str[j]);
    if(str[j]<65 || j==strlen(str)){
      stop=j-1;
      
      if(DEBUG)printf("Decoupe start %d\n",start);
      if(DEBUG)printf("Decoupe stop %d\n",stop);
       // Inver
      verlan2(str,start,stop);

      start=j+1;
    }
  }
}



              
int main(int argc, char *argv[]){

  for(int i=0;i<argc;i++){
    printf("%s\n",argv[i]);
  }
  char* chaine1=malloc(50);
  char* chaine2=malloc(50);


  char chaine3[]="winter is coming";
  //char chaine3[]="winter";
  
  printf("Chaine3: %s\n strlen %ld\n",chaine3, strlen(chaine3));
  
  decoupe(chaine3);
  printf("Chaine3: %s\n strlen %ld\n",chaine3, strlen(chaine3));
  
  printf("Ex4 Chaine 1:");
  scanf("%s", chaine1);
  printf("Chaine1: %s\n",chaine1);
  verlan(chaine1);
  printf("Chaine1: %s\n",chaine1);
  printf("Chaine3: %s\n",chaine3);
  free(chaine1);
  free(chaine2);
}
