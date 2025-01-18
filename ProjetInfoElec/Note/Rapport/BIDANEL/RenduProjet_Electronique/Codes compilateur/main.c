/********************************************************************************
|   Nom fichier : main.c
|   auteurs: BIDANEL Matthieu FRIAA Chiheb
|   
|   Descriptions : Grafcet du coffre fort réalisé en langage c
|   
|   Commentaires : 
|
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

void grafcet();

int main(int argc, char** argv){
	grafcet();
	return 0;
}


void grafcet(){
	int stable;
	
	int X0;
	int Old_X0;
	int Appel_X0;
	int Reponse_X0;
	
	int X1;
	int Old_X1;
	int Appel_X1;
	int Reponse_X1;
	
	int X2;
	int Old_X2;
	int Appel_X2;
	int Reponse_X2;
	
	int X3;
	int Old_X3;
	int Appel_X3;
	int Reponse_X3;
	
	int an0;
	int but0;
	int but1;

	int old_but0;
	int old_but1;

	int rise_but0;
	int rise_but1;

	int T0;
	int T1;
	int T2;
	int T3;

	X0 = 1;
	X1 = 0;
	X2 = 0;
	X3 = 0;
	but0 = 0;
	but1 = 0;

	while(1){

		old_but0 = but0;
		old_but1 = but1;

		printf("\n\n\nValeurs de an, but0, but1 : ");
		scanf("%d", &an0);
		scanf("%d", &but0);
		scanf("%d", &but1);

		//Calcul rise_but
		if(old_but0 == 0 && but0 == 1){
			rise_but0 = 1;
		}
		else{
			rise_but0 = 0;
		}

		if(old_but1 == 0 && but1 == 1){
			rise_but1 = 1;
		}
		else{
			rise_but1 = 0;
		}
		#if DEBUG
		printf("\nrise_but0 : %d", rise_but0);
		printf("\nrise_but1 : %d", rise_but1);
		#endif

		stable = 0;

		#if DEBUG
		int compteur = 0;
		#endif

		while(stable == 0){


			#if DEBUG
			printf("\nnouvelle itération");
			#endif

			Appel_X0 = 0;
			Reponse_X0 = 0;

			Appel_X1 = 0;
			Reponse_X1 = 0;

			Appel_X2 = 0;
			Reponse_X2 = 0;

			Appel_X3 = 0;
			Reponse_X3 = 0;

			T0 = (rise_but0 == 1 && an0<128);
			T1 = (rise_but0 == 1 && an0>128);
			T2 = (rise_but0 == 1 && an0<128);
			T3 = (rise_but1 == 1);

			Old_X0 = X0;
			Old_X1 = X1;
			Old_X2 = X2;
			Old_X3 = X3;

			//Franchissements
			if(X0 == 1 && T0 == 1){
				Appel_X1 = 1;
				Reponse_X0 = 1;
			}
			if(X1 == 1 && T1 == 1){
				Appel_X2 = 1;
				Reponse_X1 = 1;
			}
			if(X2 == 1 && T2 == 1){
				Appel_X3 = 1;
				Reponse_X2 = 1;
			}
			if(X3 == 1 && T3 == 1){
				Appel_X0 = 1;
				Reponse_X3 = 1;
			}

			#if DEBUG
			printf("\n Appel_X0 : %d \n Reponse_X0 : %d", Appel_X0, Reponse_X0);
			printf("\n Appel_X1 : %d \n Reponse_X1 : %d", Appel_X1, Reponse_X1);
			printf("\n Appel_X2 : %d \n Reponse_X2 : %d", Appel_X2, Reponse_X2);
			printf("\n Appel_X3 : %d \n Reponse_X3 : %d", Appel_X3, Reponse_X3);
			#endif

			//Calcul des évolutions
			X0 = Appel_X0 || (X0 && !(Reponse_X0));
			X1 = Appel_X1 || (X1 && !(Reponse_X1));
			X2 = Appel_X2 || (X2 && !(Reponse_X2));
			X3 = Appel_X3 || (X3 && !(Reponse_X3));

			//Test stabilité
			if((X0 == Old_X0) && (X1 == Old_X1) && (X2 == Old_X2) && (X3 == Old_X3)){
				stable = 1;
			}
			#if DEBUG
			compteur ++;
			#endif
		}
		#if DEBUG
		printf("\nitération boucle stable : %d", compteur);
		#endif
		#if DEBUG
		printf("\n X0 : %d \n X1 : %d \n X2 : %d \n X3 : %d", X0, X1, X2, X3);
		#endif
	}
}