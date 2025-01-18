#include <stdio.h>
#include <string.h>
#define DEBUG 1

// Fonction d'interpretation d'un graphcet.
// Cette fonction est propre a un graphcet donnée
void grafcet_interpreter()
{
  char buf[256];
  int but0,but1,an0,an1,oldbut0,oldbut1,risebut0,risebut1,fallbut0,fallbut1;
  int stable;
  int e0,e1,e2,e3;
  int old_e0,old_e1,old_e2,old_e3;
  int appel_e0, appel_e1, appel_e2, appel_e3;
  int reponse_e0, reponse_e1, reponse_e2, reponse_e3;
        
  e0=1;
  e1=0;
  e2=0;
  e3=0;
        
  while (1)
    {
		// On initialise les nouveaux boutons
			oldbut0=but0;
			oldbut1=but1;
		

      // ToDo
            
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

/*
 int main ()
{

	//Acquisition des entrées et initialisation des variables internes
	int e0=1,e1=0,e2=0; //x1,x2,x3; s'apparente aux etats d'une MAE
	int but0=0, but1=0, but2=0; // correpond aux boutons de la carte
	int rise_but0=0, rise_but1=0,rise_but2=0;
	int old_but0=but0,old_but1=but1,old_but2=but2; // au debut les "anciens boutons" sont initialisés à 0
	int pot; // potentiometre

	//Acquisition des entrées et initialisation des variables internes

	int appel_e0=0, reponse_e0=0, appel_e1=0, reponse_e1=0, appel_e2=0, reponse_e2=0;
	int old_e0, old_e1,old_e2;
	int stable=0;
	int verif, verif1;

	while (1)
	{

		// On initialise les nouveaux boutons
			old_but0=but0;
			old_but1=but1;
			old_but2=but2;

		printf("Veuillez entrer la valeur de but0 : \n");
		scanf("%d", &but0);
		printf("Veuillez entrer la valeur de but1 :\n");
		scanf("%d", &but1);
		printf("Veuillez entrer la valeur de but2 :\n");
		scanf("%d",&but2);
		printf("Et de pot :\n");
		scanf("%d", &pot);

		// On détecte un front montant
				if (old_but0==0 && but0==1) {
					rise_but0=1;
				}else{
					rise_but0=0;
				}
			// On détecte un front montant
				if (old_but1==0 && but1==1) {
					rise_but1=1;
				}else{ 
					rise_but1=0;
				}
			// On détecte un front montant
				if (old_but2==0 && but2==1) {
					rise_but2=1;
				}else {
					rise_but2=0;
				}
		stable=0;

		while (stable==0)
		{
			// Initialisation de appel_eX et reponse_eX
				
					appel_e0=0;
					reponse_e0=0;
					appel_e1=0;
					reponse_e1=0;
					appel_e2=0;
					reponse_e2=0;

			// Initialisation de old_e0
				old_e0=e0;
			// Initialisation de old_e1
				old_e1=e1;
			// Initialisation de old_e2
				old_e2=e2;
 			
			// Calcul de appel_eX et reponse_eX

			if(e0==1 && rise_but0==1 && pot>128){
				appel_e1=1;
				reponse_e0=1;
			}
			if(e1==1 && rise_but1==1 && pot<128){
				appel_e2=1;
				reponse_e1=1;
			}
			if(e2==1 && rise_but2==1 && pot>128){
				appel_e0=1;
				reponse_e2=1;
			}

			
			//Calcul de eX
			if (DEBUG) printf("reponse_e0=%d\n", reponse_e0);
			verif1 =(!reponse_e0) ;
			if (DEBUG) printf("verif1= %d\n",verif1);
			verif =(e0 && ~(reponse_e0));
			if (DEBUG) printf("verif= %d\n",verif);
			
			e0=(appel_e0 || (e0 && !(reponse_e0)));
			e1=(appel_e1 || (e1 && !(reponse_e1)));
			e2=(appel_e2 || (e2 && !(reponse_e2)));
			
			printf("Valeur de e0 =%d et appel_e0=%d et but0=%d et reponse_e0=%d et rise_but0=%d\n", e0,appel_e0,but0,reponse_e0,rise_but0);
			printf("Valeur de e1 =%d et appel_e1=%d et but1=%d et reponse_e1=%d et rise_but1=%d\n", e1,appel_e1,but1,reponse_e1,rise_but1);
			printf("Valeur de e2 =%d et appel_e2=%d et but2=%d et reponse_e2=%d et rise_but2=%d\n", e2,appel_e2,but2,reponse_e2,rise_but2);
			
			
			//Test Stabilité
			if (e0==old_e0 && e1==old_e1 && e2==old_e2)
			{
				stable=1;
				printf("Atteinte de stabilité\n");
			}
			
		}
		// Si on atteint la stabilité alors il faut faire changer sortir les variables (changer les états !)
	}


	return 0;
}
* */
