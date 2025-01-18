#include <stdio.h>
#include "vm_codops.h"

// Define to configure grafcet
#define BOUTON0 0
#define AM 1
#define BOUTON1 2
#define X0 3
#define OLD_X0 4
#define APPEL_X0 5
#define REPONSE_X0 6
#define X1 7
#define OLD_X1 8
#define APPEL_X1 9
#define REPONSE_X1 10
#define X2 11
#define OLD_X2 12
#define APPEL_X2 13
#define REPONSE_X2 14
#define X3 15
#define OLD_X3 16
#define T3 17
#define APPEL_X3 18
#define REPONSE_X3 19
#define STABLE 20
#define OLD_BOUTON0 21
#define OLD_BOUTON1 22

// prototype
void GrafcetInterpreter(int* variable);


int main(int argc, char ** argv)
{
	int variable[100];

	GrafcetInterpreter(variable);
}


void GrafcetInterpreter(int* variable)
{
	int choix, tmp;
	
	// etat initial : X0
		
	variable[X0] = 1;
	variable[X1] = 0;
	variable[X2] = 0;
	variable[X3] = 0;
	
	while (1)
	{
		variable[STABLE] = 0;		
		
		variable[BOUTON0] = 0;
		variable[BOUTON1] = 0;
		variable[OLD_BOUTON0] = variable[BOUTON0];
		variable[OLD_BOUTON1] = variable[BOUTON1];
		
		do
		{
			printf("Choix des evolutions : (tapez  : 0 pour le bouton 0, 1 pour le bouton 1, 2 pour Am, 3 pour afficher les valeurs des objects, 10 pour arreter le programme) \n");
			scanf("%d", &choix);		
			switch(choix)
			{
				case 0 :
					printf("tapez la valeur pour le bouton 0 (0 etat bas, 1 etat actif) \n");
					scanf("%d" , &tmp);
//					printf(" rmp : %d \n", tmp);
					if (tmp == 0 || tmp == 1)
						variable[BOUTON0] = tmp;
					else	
					{
						printf("INCORRECT VALUE, bouton 0 is desactivated \n");
						variable[BOUTON0] = 0;
					} 
					break;
					
				case 1 :
					printf("tapez la valeur pour le bouton 1 (0 etat bas, 1 etat actif) \n");
					scanf("%d" , &tmp);
				
					if (tmp == 0 || tmp == 1)
						variable[BOUTON1] = tmp;
					else
					{
						printf("INCORRECT VALUE, bouton 1 is desactivated \n");
						variable[BOUTON1] = 0; 
					}
					break;
										
				case 2 :
					printf("tapez la valeur pour Am (entre 0 et 360) \n");
					scanf("%d" , &tmp);
//					printf("tmp : %d \n", variable[AM]);
				
					if (tmp > -1 && tmp < 361)
						variable[AM] = tmp;
					else
					{
						printf("INCORRECT VALUE, Am is set to 0 \n");
						variable[AM] = 0;
					} 
					break;
				
				case 3 :
					printf("valeur bouton0 : %d \n", variable[BOUTON0]);
					printf("valeur bouton1 : %d \n", variable[BOUTON1]);
					printf("valeur Am : %d \n", variable[AM]);
					break;
					
				case 10 :
					printf("ceci est la fin du programme \n");
					return;
					break;
					
				default :
					printf("ERROR value \n");
		
			}
			
			do
			{
				printf("Voulez vous rechanger un object (0 pour non, 1 pour oui) \n");
				scanf("%d", &choix);
			}while( (choix != 0) && (choix != 1) );
		
		}	
		while(choix == 1);
	
		while(variable[STABLE] == 0)
		{
			variable[OLD_X0] = variable[X0];
			variable[OLD_X1] = variable[X1];
			variable[OLD_X2] = variable[X2];
			variable[OLD_X3] = variable[X3];
			
			variable[APPEL_X0] = 0;
			variable[REPONSE_X0] = 0;
			variable[APPEL_X1] = 0;
			variable[REPONSE_X1] = 0;
			variable[APPEL_X2] = 0;
			variable[REPONSE_X2] = 0;
			variable[APPEL_X3] = 0;
			variable[REPONSE_X3] = 0;
		
			if (variable[X0] == 1)
				printf("X0 est l'état actuel \n");
			if (variable[X1] == 1)
				printf("X1 est l'état actuel \n");
			if (variable[X2] == 1)
				printf("X2 est l'état actuel \n");
			if (variable[X3] == 1)
				printf("X3 est l'état actuel \n");
				
			if(variable[X0] == 1 && (variable[OLD_BOUTON0] == 0 && variable[BOUTON0] == 1) && variable[AM] < 128)	// front montant du bouton et am < 128
			{
				variable[APPEL_X1] = 1;
				variable[REPONSE_X0] = 1;
				printf(" on appelle X1 \n" );
			}
			
			if(variable[X1] == 1 &&  (variable[OLD_BOUTON0] == 0 && variable[BOUTON0] == 1) && variable[AM] > 128)
			{
				variable[APPEL_X2] = 1;
				variable[REPONSE_X1] = 1;
				printf(" on appelle X2 \n" );
			}
			
			if(variable[X2] == 1 && (variable[OLD_BOUTON0] == 0 && variable[BOUTON0] == 1) && variable[AM] < 128)
			{
				variable[APPEL_X3] = 1;
				variable[REPONSE_X2] = 1;
				printf(" on appelle X3 \n" );
			}
		
			if(variable[X3] == 1 && (variable[OLD_BOUTON1] == 0 && variable[BOUTON1] == 1))
			{
				variable[APPEL_X0] = 1;
				variable[REPONSE_X3] = 1;
				printf(" on appelle X0 \n" );
			}
				
//			printf("calcul deqq chose %x et son opposé %x  et avec le ! %x \n", (variable[REPONSE_X0]), ~(variable[REPONSE_X0]),  !(variable[REPONSE_X0]));
//			printf("calcul deqq chose %x  et son opposé %x  et avec le ! %x \n", (variable[X0]), ~(variable[X0]),  !(variable[X0]));		
			
			variable[X0] = variable[APPEL_X0] || (variable[X0] && !(variable[REPONSE_X0]));
			variable[X1] = variable[APPEL_X1] || (variable[X1] && !(variable[REPONSE_X1]));
			variable[X2] = variable[APPEL_X2] || (variable[X2] && !(variable[REPONSE_X2]));
			variable[X3] = variable[APPEL_X3] || (variable[X3] && !(variable[REPONSE_X3]));
		
			if (variable[OLD_X0] == variable[X0] && variable[OLD_X1] == variable[X1] && variable[OLD_X2] == variable[X2] && variable[OLD_X3] == variable[X3])
				variable[STABLE] = 1;
		}
	}
}






























