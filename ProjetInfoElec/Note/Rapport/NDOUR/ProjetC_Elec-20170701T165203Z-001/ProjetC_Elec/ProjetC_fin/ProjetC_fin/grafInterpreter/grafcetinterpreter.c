#include <stdlib.h>
#include <stdio.h>
#include "vm_codops.h"

void grafcetinterpreter()
{
int but0, but1, old_but0, old_but1, e0, e1, e2, e3, old_e0, old_e1, old_e2, old_e3, appel_e0, appel_e1, appel_e2, appel_e3, reponse_e0, reponse_e1, reponse_e2, reponse_e3, stable, risebut0, risebut1, pot, led0;

e0=1; e1=0; e2=0; e3=0;
but0=0; but1=0;

while (1)
{
old_but0= but0; old_but1= but1;
printf("valeur de but0:");
scanf("%d",&but0);
printf("valeur de but1:");
scanf("%d",&but1);
printf("valeur de pot:");
scanf("%d",&pot);

//permet de vérifier si le bouton était déjà enfoncé ou pas
 if(old_but0==0 && but0==1) {risebut0=1; }
 else { risebut0=0;}

 if(old_but1==0 && but1==1) {risebut1=1;}
 else{risebut1=0;}
 stable = 0;

 while(stable==0){
   // initialisation des appel, reponse et sauvegarde de eX dans old_eX
	appel_e0=0; reponse_e0=0; appel_e1=0; reponse_e1=0; appel_e2=0; reponse_e2=0; appel_e3=0; reponse_e3=0;
  	old_e0=e0; old_e1=e1; old_e2=e2; old_e3=e3;
     // calcul des appels et reponses
	if(e0==1 && risebut0==1 && pot>128)
	{
         appel_e1=1; reponse_e0=1;
	
	}
	if(e1==1 && risebut0==1 && pot<128)
	{
         appel_e2=1; reponse_e1=1;
	 
	}
	if(e2==1 && risebut0==1 && pot>128)
	{
         appel_e3=1; reponse_e2=1;

	}
	if(e3==1 && risebut1==1)
	{
         appel_e0=1; reponse_e3=1;
	}
        // Calcul des eX
      	e0= appel_e0 || (e0 && !(reponse_e0));
	e1= appel_e1 || (e1 && !(reponse_e1)); 
        e2= appel_e2 || (e2 && !(reponse_e2));
        e3= appel_e3 || (e3 && !(reponse_e3));
       //calcul de la stabilité
	if(e0==old_e0 && e1==old_e1 && e2==old_e2 && e3== old_e3)
        {
          stable=1;
        }
        
//si e0==1 eteindre led0 puis allumer led1 (led1=1) si e3=1
       if(e0==1) {led0=0;}
       if(e1==1) {led0=0;}
       if(e2==1) {led0=0;}
       if(e3==1) {led0=1;}
  }
 printf("but0=%d, but1= %d, risebut0=%d, risebut1=%d, old_but0= %d, old_but1= %d\n", but0, but1, risebut0, risebut1, old_but0, old_but1);
 printf("reponse_e0=%d, reponse_e1= %d, reponse_e2=%d, reponse_e3=%d, appel_e0=%d, appel_e1=%d, appel_e2=%d, appel_e3=%d\n", reponse_e0, reponse_e1,   reponse_e2, reponse_e3, appel_e0, appel_e1, appel_e2, appel_e3);
 printf("old_e0=%d, old_e1= %d, old_e2=%d, old_e3=%d\n", old_e0, old_e1, old_e2, old_e3);
 printf("e0=%d, e1= %d, e2=%d, e3=%d, stable= %d, led0=%d\n", e0, e1, e2, e3, stable, led0);


}
}

int main(){
grafcetinterpreter();
return 0;
}     
      
