#include <stdio.h>
#include <string.h>
#define DEBUG 1

/*! \page interpreteur Interpréteur de grafcet
 *
 * \date 30 Juin 2017
 * 
 * \section intro_sec Introduction
 *
 * Fonction d'interpretation d'un graphcet.
 * Cette fonction est propre à un graphcet donné
 */

/*! \file graphInterpreter.c
 */
 
/*! \fn  grafcet_interpreter()
 * \brief Fonction permettant d'interpréter un grafcet donné
 * 		  Ici il s'agit du grafcet pour un coffre-fort
 */
void grafcet_interpreter()
{
	char buf[256];
	int But0, But1, an0, stable;	//boutons et stabilité
	int Old_But0=0, Old_But1=0; // anciennes valeurs des boutons
	int Appel_e0, Appel_e1, Appel_e2, Appel_e3; //Appels
	int Reponse_e0, Reponse_e1, Reponse_e2, Reponse_e3; //Réponses	
	int Old_e0=0, Old_e1=0, Old_e2=0, Old_e3=0; //Anciennes valeurs d'étapes
	int e0=1, e1=0, e2=0, e3=0; // étapes
	int riseBut0, riseBut1;
        
	e0=1;
	e1=0;
	e2=0;
	e3=0;
        
        
  while (1)
    {
		// Pour le débuggage
        printf("But 0 : ");
		scanf("%d",&But0);
		printf("\n");
		
		printf("But 1 : ");
		scanf("%d",&But1);
		printf("\n");
		
		printf("an0 : ");
		scanf("%d",&an0);
		printf("\n");
		
		// Les balises permettent de valider les étapes que nous avons réaliser à mesure de l'avancement du projet

		if(Old_But0==0 && But0==1) // calcul de front sur but0 OK ASM
		{
			riseBut0=1;
		}
		else riseBut0=0;

		if(Old_But1==0 && But1==1) // calcul de front sur but1 OK ASM
		{
			riseBut1=1;
		}
		else riseBut1=0;

		Old_But0=But0;
		Old_But1=But1;
		
		stable=0;
		
		while(stable==0) // test stabilité //OK ASM
		{
			Appel_e0=0; //OK ASM
			Appel_e1=0;
			Appel_e2=0;
			Appel_e3=0;
			
			Reponse_e0=0;
			Reponse_e1=0;
			Reponse_e2=0;
			Reponse_e3=0;
			
			if(e0==1 && riseBut0==1 && an0>128) // OK ASM
			{
				Appel_e1=1;
				Reponse_e0=1;
			}

			if(e1==1 && riseBut0==1 && an0<128) //OK ASM
			{
				Appel_e2=1;
				Reponse_e1=1;
			}

			if(e2==1 && riseBut0==1 && an0>128) //OK ASM
			{
				Appel_e3=1;
				Reponse_e2=1;
			}

			if(e3==1 && riseBut1==1) //ok ASM
			{
				Appel_e0=1;
				Reponse_e3=1;
			}
			
			//Calcul des évolutions
			e0=Appel_e0 | (e0 & ~(Reponse_e0)); //OK ASM les 4
			e1=Appel_e1 | (e1 & ~(Reponse_e1));
			e2=Appel_e2 | (e2 & ~(Reponse_e2));
			e3=Appel_e3 | (e3 & ~(Reponse_e3));
			
			//Test stabilité
			if(e0==Old_e0 && e1==Old_e1 && e2==Old_e2 && e3==Old_e3) //OK ASM
			{
				stable=1;
				printf("Stabilité OK\n");
			}
			
			Old_e0=e0; 
			Old_e1=e1;
			Old_e2=e2;
			Old_e3=e3;
			
			
			//~ printf("e0 : %d\n",e0);
			//~ printf("Appel_e1 : %d\n",Appel_e1);
			//~ printf("Old_e0 : %d\n",Old_e0);
			//~ printf("Reponse_e0 : %d\n",Reponse_e0);
			//~ printf("riseBut0 : %d\n",riseBut0);
			//~ printf("Old_But0 : %d\n",Old_But0);	
		}
		
		//~ printf("e0 : %d  ", e0);
		//~ printf("e1 : %d  ", e1);
		//~ printf("e2 : %d  ", e2);
		//~ printf("e3 : %d  \n", e3);
		
		// On vérifie que nous passons bien dans toutes les étapes
		if(e0==1)
		{	
			printf("ETAPE 0\n");
		}
		
		if(e1==1)
		{
			printf("ETAPE 1\n");
		}
		
		if(e2==1)
		{
			printf("ETAPE 2\n");
		}
		
		if(e3==1)
		{
			printf("ETAPE 3\n");
		}
            
#if DEBUG
      printf("\te0\te1\te2\te3\n");
      printf("Eold\t%d\t%d\t%d\t%d\n",old_e0,old_e1,old_e2,old_e3);
      printf("Appel\t%d\t%d\t%d\t%d\n",appel_e0,appel_e1,appel_e2,appel_e3);
      printf("Reponse\t%d\t%d\t%d\t%d\n",reponse_e0,reponse_e1,reponse_e2,reponse_e3);
      printf("Ecur \t%d\t%d\t%d\t%d\n",e0,e1,e2,e3);
      printf("---------------------------------\n");
#endif
                
    }

}

/*! \fn  main(int argc, char **argv)
 * \brief main permettant d'exécuter la fonction graphInterpreter
 */
int main(int argc, char **argv)
{
  grafcet_interpreter();
  return 0;
}

