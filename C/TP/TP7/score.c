#include <stdio.h>
#include <string.h>
#include "individu.h"

int max3(int a,int b, int c){
  int max;
  if(a>b){
    max=(c>a)?c:a;
  }else{
    max=(c>b)?c:b;
  }
  if(DEBUG)printf("\t max3 de %d,%d,%d est %d\n",a,b,c,max);
  return max;
}

//int maxtab(int* tab){
//  if(DEBUG)printf("\t maxtab\n");
//  int max=tab[0];
//  for(int i=1;i<sizeof(tab);i++){
//    if(DEBUG)printf("\t tab[i] %d\n",tab[i]);
//    if(tab[i]>max)
//      max=tab[i];
//  }
//  if(DEBUG)printf("\t max %d\n",max);
//    
//  return max;
//}

int needlemanwunsch(char* seq1, char* seq2){
  if(DEBUG)printf("\t needlemanwunsch\n");
  int l1=strlen(seq1)+1;
  int l2=strlen(seq2)+1;
  int tab[l1*l2];
  int cout;
  for(int i=0;i<l1;i++){
    tab[i*l2]=0;
  }
  for(int i=0;i<l2;i++){
    tab[i]=0;
  }

  for(int i=1;i<l1;i++){
    for(int j=1;j<l2;j++){
      cout= (seq1[i-1]==seq2[j-1])? 1:-1;
      tab[i*l2 + j] = max3(tab[(i-1)*l2+j]-1,tab[i*l2+j-1]-1,
                           tab[(i-1)*l2+j-1]+cout);
    }
  }

  // Calcul du max du tableau
  int max=tab[0];
  
  for(int i=1;i<l1*l2;i++){
    if(DEBUG)printf("\t tab[i] %d\n",tab[i]);
    if(tab[i]>max)
      max=tab[i];
  }
  if(DEBUG)printf("\t max %d\n",max);
  
  
  return max;
}



float inclusion(char* seq1, char* seq2){
  if(DEBUG)printf("\t inclusion\n");
  int min = (strlen(seq1)<strlen(seq2))?strlen(seq1):strlen(seq2);
  if(DEBUG)printf("\t inclusion min %d\n",min);
  return (float)needlemanwunsch(seq1,seq2)/min;
}

void calculSimilarite(t_individu* individu, char* seq){
  if(DEBUG)printf("\t DEBUG calculSimilarite \n");
  individu->simil=inclusion(individu->sequence, seq)*100;
}
