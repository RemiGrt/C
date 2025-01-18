#include <stdlib.h>
#include <stdio.h>

int grafcet_interpreteur(){
	//Affectation
	
	int stable=0;
	int appel_e1,appel_e2,appel_e3,appel_e4;
	int reponse_e1,reponse_e2,reponse_e3,reponse_e4;
	int but1,but2,pot,old_but1,old_but2,rise_but1,rise_but2;
	int Pot;
	int e1,e2,e3,e4,old_e1,old_e2,old_e3,old_e4;
	
	//On entre dans l'étape 1
		e1= 1;
		e2= 0;
		e3= 0;
		e4= 0;
	
	while(1){
		//lecture des entrées
		printf("\nbouton1? \n");
		scanf("%d",&but1);	
		printf("\nbouton2? \n");
		scanf("%d",&but2);
		printf("\npotentiomètre? \n");
		scanf("%d",&Pot);

		old_but1= 0; old_but2= 0;

		//Calcule des rise up
		if(old_but1==0 &&  but1==1){
			rise_but1=1;
		}
		else{
			rise_but1=0;
		}
		if(old_but2==0 && but2==1){
			rise_but2=1;
		}
		else{
			rise_but2=0;
		}
		//Etape 3 // initialise à 0 les appels et reponses 
		
		if((e1==1) && (rise_but1==1 && Pot<128)){
				appel_e2=1;//Mise à 1 de e2
		stable=0;
	
		printf("rise but 1 %d\n",rise_but1);
		while(stable==0){
			//Etape 4
			old_e1=e1;
			old_e2=e2;
			old_e3=e3;
			old_e4=e4;
			appel_e1=0;
			appel_e2=0;
			appel_e3=0;
			appel_e4=0;
			reponse_e1=0;
			reponse_e2=0;
			reponse_e3=0;
			reponse_e4=0;
			
			
			//Etape 5 Condition de passage au étapes suivantes
			
			if((e1==1) && (rise_but1==1 && Pot<128)){
				appel_e2=1;//Mise à 1 de e2
				reponse_e1=1;//Mise à 0 de e1
				printf("\nrentré dans condition 1");
			}
			if((e2==1) && (rise_but1==1 && Pot>128)){	
				appel_e3=1;//Mise à 1 de e3
				reponse_e2=1;//Mise à 0 de e2
				printf("\nrentré dans condition 2");
			}
			if((e3==1) && (rise_but1==1 && Pot<128)){
				appel_e4=1;//Mise à 1 de e4
				reponse_e3=1;//Mise à 0 de e3
				printf("\nrentré dans condition 3");
			}
			if((e4==1) && (rise_but2==1)){
				appel_e1=1;//Mise à 1 de e1
				reponse_e4=1;//Mise à 0 de e4
				printf("\nrentré dans condition 4");
			}	

			
			//Etape 6 Calcul des etats e_x ((formule cf poly pour passer à une autre étape)

			e1 = appel_e1 || (e1 && !(reponse_e1));
			e2 = appel_e2 || (e2 && !(reponse_e2));
			e3 = appel_e3 || (e3 && !(reponse_e3));
			e4 = appel_e4 || (e4 && !(reponse_e4));

			//Etape 7 Calcul de la stabilité
			if(e1==old_e1 && e2==old_e2 && e3==old_e3 && e4==old_e4){
				stable=1; //état actuel égal à l'ancien état
			}
		 }
	
			//Etape 8 Affectation ds sorties
		if (e1==1){
			printf("etape 1 active");
			}
		if (e2==1){
			printf("etape 2 active");
			}
		if (e3==1){
			printf("etape 3 active");
			}
		if (e4==1){
			printf("etape 4 active");
			}			
	}
return 0;		
}
 
void main(){
	grafcet_interpreteur();

}			
		
