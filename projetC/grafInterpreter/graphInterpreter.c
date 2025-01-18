#include <stdio.h>
#include <stdlib.h>

/*
#1 Lecture des entrées 
#2 Calcul des fronts
#3 Tant que stable==0

   #4 Initialisation de appel_ex et reponse_ex
   #5 Initialisation de old_ex
   #6 Sauvegarde des etats dans old_ex
   #7 Calcul de appel_ex et reponse_ex
   #8 Calcul des ex
   #8 Calcul de la stabilité
    

    Fin Tant que

*/

int but1=0,but2=0,An=0;
int rise_but1=0,rise_but2=0;
int Old_but1=0,Old_but2=0;

int Stable=0;

int X1=0,X2=0,X3=0,X4=0;

int Appel_X1=0,Appel_X2=0,Appel_X3=0,Appel_X4=0 ;
int Reponse_X1=0,Reponse_X2=0,Reponse_X3=0,Reponse_X4=0;
int Old_X1=0,Old_X2=0,Old_X3=0,Old_X4=0;





int main()
{


	X1=1;
	while(1)
	{

		Stable=0;

		// Lecture des entrées
		printf("Etape:X%d%d%d%d\nbut1 but2 An\n",X1,X2,X3,X4);
	    	scanf("%d %d %d",&but1,&but2,&An);

	    	//Calcul des fronts
		if(Old_but1==0 && but1)
			rise_but1=1;
	    	else
			rise_but1=0;

	    	if(Old_but2==0 && but2)
			rise_but2=1;
	    	else
			rise_but2=0;


	    	while(Stable==0)
	    	{
			// Initialisation de Appel/Reponse
			Appel_X1=0;Appel_X2=0;Appel_X3=0;Appel_X4=0;
			Reponse_X1=0;Reponse_X2=0;Reponse_X3=0;Reponse_X4=0;

		
			if(X1==1 && rise_but1 && An<128)
			{
			    Appel_X2=1;
			    Reponse_X1=1;
			}

		
			if(X2==1 && rise_but1 && An>128)
			{
			    Appel_X3=1;
			    Reponse_X2=1;
			}

		
			if(X3==1 && rise_but1 && An<128)
			{
			    Appel_X4=1;
			    Reponse_X3=1;
			}

		
			if(X4==1 && rise_but2)
			{
			    Appel_X1=1;
			    Reponse_X4=1;
			}

			//Calcul de l'evolution 

			X1= Appel_X1 || (X1 && !(Reponse_X1));
			X2= Appel_X2 || (X2 && !(Reponse_X2));
			X3= Appel_X3 || (X3 && !(Reponse_X3));
			X4= Appel_X4 || (X4 && !(Reponse_X4));

			// Test stabilité
		
			if((X1==Old_X1) && (X2==Old_X2) &&(X3==Old_X3) && (X4==Old_X4))
			{
				Stable=1;
			}

		
			Old_X1=X1; Old_X2=X2; Old_X3=X3; Old_X4=X4;
			Old_but1=but1;
			Old_but2=but2;


		}	


	}


	return 0;


}
