#include <stdio.h>
#include <stdlib.h>
#include "vm.codops.h"
#define DEBUG 0
#define SIZE_TAB 100

int pc=0;
int sp=-1;
int code[SIZE_TAB];
int stack[SIZE_TAB];
int variable[SIZE_TAB];


void run(){
  while(code[pc]!=I_HALT){
    switch(code[pc]){
    case I_PUSHI:
#if DEBUG
  printf("run: I_PUSHI\n");      
#endif      
      sp++;
      stack[sp]=code[pc+1];
      pc=pc+2;
      break;
      
    case I_MULT:
#if DEBUG
  printf("run: I_MULT\n");      
#endif      
      stack[sp-1]=stack[sp-1]*stack[sp];
      sp--;
      pc++;
      break;
      
    case I_ADD:
#if DEBUG
  printf("run: I_ADD\n");      
#endif      
      stack[sp-1]=stack[sp-1]+stack[sp];
      sp--;
      pc++;
      break;

    case I_EQ:
#if DEBUG
  printf("run: I_EQ\n");      
#endif
      stack[sp-1]=(stack[sp-1]==stack[sp]);
      sp--;
      pc++;
      break;
      
    case I_J:
#if DEBUG
  printf("run: I_J\n");
#endif
      pc=code[pc+1];
      break;
      
    case I_PUSH:
#if DEBUG
  printf("run: I_PUSH\n");
#endif      
      sp++;
      stack[sp]=variable[code[pc+1]];
      pc=pc+2;
      break;
      
    case I_POP:
#if DEBUG
  printf("run: I_POP\n");
#endif
      variable[code[pc+1]]=stack[sp];
      sp--;
      pc=pc+2;
      break;

    case I_JF:
#if DEBUG
  printf("run: I_JF\n");
#endif
      pc=(stack[sp]==1)?code[pc+1]:pc+2;
      break;
    }
#if DEBUG
    printf("run: stack: %d %d %d %d %d \n",stack[0],stack[1],stack[2],
           stack[3],stack[4]);
    printf("run: sp %d\n",sp); 
    printf("run: pc %d\n",pc); 
    printf("run: variable: %d %d %d %d %d \n",variable[0],variable[1],variable[2], variable[3],variable[4]);       
#endif


  
  }
#if DEBUG
  printf("run: I_HALT\n");      
#endif
}

void readBin(char *filename){
  char line[SIZE_TAB];
  int nbInst,i,co,v;
  FILE* f=fopen(filename,"r");
  if(f==NULL){
    printf("Erreur d'ouverture du fichier\n");
    exit(EXIT_FAILURE);
  }
  fgets(line, SIZE_TAB, f);
  sscanf(line,"%d",&nbInst);
#if DEBUG
  printf("readBin: nbInst %d\n",nbInst);
#endif
  
  for(i=0;i<nbInst;i++){
    fscanf(f,"%d:%d",&co,&v);
    code[co]=v;
#if DEBUG
    printf("readBin: code[%d] %d\n",i,code[i]);
#endif
    
  }
  fclose(f);
}

int main(int argc, char *argv[]){
  variable[0]=1;
  readBin(argv[1]);  
  run();
  return 0;
}
