#include <stdio.h>
#include <string.h>
#define DEBUG 1

// Fonction d'interpretation d'un graphcet.
// Cette fonction est propre a un graphcet donnée
void grafcet_interpreter()
{
  /*char buf[256];
  int but0,but1,an0,an1,oldbut0,oldbut1,risebut0,risebut1,fallbut0,fallbut1;
  int stable;
  int e0,e1,e2,e3;
  int old_e0,old_e1,old_e2,old_e3;
  int appel_e0, appel_e1, appel_e2, appel_e3;
  int reponse_e0, reponse_e1, reponse_e2, reponse_e3;
  
  int but0,but1,an0,old_but0,old_but1,rise_but0,rise_but1;*/

int e0,e1,e2,e3;

int appel_e0,appel_e1,appel_e2,appel_e3;

int reponse_e0,reponse_e1,reponse_e2,reponse_e3;

int old_e0,old_e1,old_e2,old_e3;
        
  e0=1;
  e1=0;
  e2=0;
  e3=0;
        
        
  while (1)
    {

      // ToDo
            old_but0 = but0;
		old_but1 = but1;
		int stable=0;
	
		printf("entrez état du bouton 0\n");
		scanf("%d",&but0);
		printf("entrez état du bouton 1\n");
		scanf("%d",&but1);
		printf("entrez valeur de an0\n");
		scanf("%d",&an0);

		if(old_but0 == 0 && but0 == 1)
		{
			rise_but0 = 1;
		}
		else
		{
			rise_but0 = 0;
		}

		if(old_but1 == 0 && but1 == 1)
		{
			rise_but1 = 1;
		}
		else
		{
			rise_but1 = 0;
		}


		while (stable == 0)
		{

			old_e0 = e0;
			old_e1 = e1;
			old_e2 = e2;
			old_e3 = e3;
	
			appel_e0 = 0;
			appel_e1 = 0;
			appel_e2 = 0;
			appel_e3 = 0;

			reponse_e0 = 0;
			reponse_e1 = 0;
			reponse_e2 = 0;
			reponse_e3 = 0;

		// Franchissement des différentes étapes
			if (e0 == 1 && an0>128 && rise_but0 == 1)
			{
				appel_e1 = 1;
				reponse_e0 = 1;
			}

			if (e1 == 1 && an0<128 && rise_but0 == 1)
			{
				appel_e2 = 1;
				reponse_e1 = 1;
			}

			if (e2 == 1 && an0>128 && rise_but0 == 1)
			{
				appel_e3 = 1;
				reponse_e2 = 1;
			}

			if (e3 == 1 && rise_but1 == 1)
			{
				appel_e0 = 1;
				reponse_e3 = 1;
			}

			// Calcul des évolutions
			e0 = appel_e0 | (e0 & !reponse_e0);
			e1 = appel_e1 | (e1 & !reponse_e1);
			e2 = appel_e2 | (e2 & !reponse_e2);
			e3 = appel_e3 | (e3 & !reponse_e3);

			// Test de stabilité
			if (e0 == old_e0 && e1 == old_e1 && e2 == old_e2 && e3 == old_e3)
			{
				stable = 1;
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
}


int main(int argc, char **argv)
{
  grafcet_interpreter();
  return 0;
}

