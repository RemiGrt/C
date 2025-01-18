/*c'est la chaîne de compilation-assemblage. Ce programme traduit en C de l’algorithme
d’interprétation du grafcet.*/

#include <stdio.h>
#include  <stdlib.h>

int main()
{
	// oldbut c'est l'ancienne valeur du bouton, risebut c'est le resultat de la comparaison entres les boutons
	int but0, but1, old_but0 = 0, old_but1 = 0, risebut0, risebut1;
	int e0, e1, e2, e3, appel_e0, appel_e1, appel_e2, appel_e3, reponse_e0, reponse_e1, reponse_e2, reponse_e3;
	int old_e0, old_e1, old_e2, old_e3;
	int stable = 0;
	int pot;
	e0 = 1; e1 = 0; e2 = 0; e3 = 0;
	
	while(1)
	{	
		//Lecture des entrées boutons et potentiomètre
		printf("Saisir les valeurs du bouton 0, bouton 1 et potentiometre\n");
		scanf("%d", &but0);
		scanf("%d", &but1);
		scanf("%d", &pot);
	
		//Calcul des fronts
	
		if(old_but0 == 0 && but0 == 1)
		{
			risebut0 = 1;
			printf("risebut0 = %d\n", risebut0);
		}
		else 
		{
			risebut0 = 0;
			printf("risebut0 = %d\n", risebut0);
		}

		old_but0 = but0;
		printf("old_but0 = %d\n", old_but0);
	
		if(old_but1 == 0 && but1 == 1)
		{
			risebut1 = 1;
			printf("risebut1 = %d\n", risebut1);
		}
		else 
		{
			risebut1 = 0; 
			printf("risebut1 = %d\n", risebut1);
		}

		old_but1 = but1;
		printf("old_but1 = %d\n", old_but1);
		
		stable = 0;
		// Condition tant que stable est égal à 0	
		while(stable == 0)
		{
			printf("On est dans la boucle while\n");			
			//initialisation de appel_eX et reponse_eX	
			appel_e0 = 0;
			appel_e1 = 0;
		        appel_e2 = 0;
			appel_e3 = 0;
			reponse_e0 = 0;
		        reponse_e1 = 0;
			reponse_e2 = 0;
			reponse_e3 = 0;
		
			//initialisation de old_eX
			old_e0 = e0;
			old_e1 = e1;
			old_e2 = e2;
			old_e3 = e3;
			
			//printf("On est dans e0\n");
			printf("Saisir les valeurs du bouton 0, bouton 1 et potentiometre\n");
			scanf("%d", &but0);
			scanf("%d", &but1);
			scanf("%d", &pot);
			
			//Calcul de appel_eX et reponse_eX		
			if(e0 == 1 && risebut0 == 1 && (pot > 128))
			{
				reponse_e0 = 1;
				appel_e0 = 0;
				appel_e1 = 1;
				
				printf("on est dans e1\n");
				printf("Saisir les valeurs du bouton 0, bouton 1 et potentiometre\n");
				scanf("%d", &but0);
				scanf("%d", &but1);
				scanf("%d", &pot);
			} 
			if(e1 == 1 && risebut0 == 1 && (pot < 128))
			{
				reponse_e1 = 1;
				appel_e1 = 0;
				appel_e2 = 1;
				printf("on est dans e2\n");
				printf("Saisir les valeurs du bouton 0, bouton 1 et potentiometre\n");
				scanf("%d", &but0);
				scanf("%d", &but1);
				scanf("%d", &pot);
			}
			if(e2 == 1 && risebut0 == 1 && (pot > 128))
			{
				reponse_e2 = 1;
				appel_e2 = 0;
				appel_e3 = 1;
				printf("on est dans e3\n");
				printf("Saisir les valeurs du bouton 0, bouton 1 et potentiometre\n");
				scanf("%d", &but0);
				scanf("%d", &but1);
				scanf("%d", &pot);
			}
			if(e3 == 1 && risebut1 == 1)
			{
				reponse_e3 = 1;
				appel_e3 = 0;
				appel_e0 = 1;
				printf("on est dans e0\n");
			}
		
			//Calcul de e0, e1, e2, e3
			e0 = appel_e0 ||(e0 && ~(reponse_e0));
			e1 = appel_e1 ||(e1 && ~(reponse_e1));
			e2 = appel_e2 ||(e2 &&~(reponse_e2));
			e3 = appel_e3 ||(e3 && ~(reponse_e3));

			//Calcul de la stabilite
			if((e0 == old_e0) &&(e1 == old_e1) && (e2 == old_e2) && (e3 == old_e3))
			{
				stable = 1;
			}
			printf("e0 = %d, e1 = %d, e2 = %d, e3 = %d, stable = %d\n\n", e0, e1, e2, e3, stable);
		}	
	}
}
