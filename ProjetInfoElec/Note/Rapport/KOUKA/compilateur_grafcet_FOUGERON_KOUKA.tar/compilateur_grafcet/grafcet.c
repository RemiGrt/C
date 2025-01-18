#include <stdio.h>
#include <stdlib.h>




int grafcet_interpreter()
{
	int stable = 0;
	int appel_e1,appel_e2,appel_e3,appel_e4;
	int reponse_e1,reponse_e2,reponse_e3,reponse_e4;
	int but1,but2,pot,old_but1,old_but2,rise_but1,rise_but2;
	int e1,e2,e3,e4;
	int old_e1,old_e2,old_e3,old_e4;
	int T1,T2,T3,T4;
	int cmpt;
	 
	 /* Initialisation des ei et des old_buti */
	 e1= 1; e2 =0; e3 =0; e4 =0;
	 old_but1 =0; old_but2=0;
	 rise_but1 = 0;
	 rise_but2 = 0;
	  
	 while (1)
	 {
		 /* lecture des entrées */
		 printf ("\n Veuillez entrer la valeur du bouton n°1 \n");
		 scanf ("%d",&but1);
		 printf ("\n Veuillez entrer la valeur du bouton n°2\n");
		 scanf ("%d",&but2);
		 printf ("\n Veuillez entrer la valeur du potentiomètre\n");
		 scanf ("%d",&pot);
	     
	     
		 /* calcul de rise_but 1*/
		 if (old_but1==0 && but1==1)
		 {
			 rise_but1 =1;
		 } else {
			 rise_but1 =0;
		 }
		 
		 /* calcul de rise_but 2 */
		 if (old_but2==0 && but2==1)
		 {
			 rise_but2 =1;
		 } else {
			 rise_but2 =0;
		 }
		 
		 T1 = (rise_but1 && (pot < 128));
	     T2 = (rise_but1 && (pot > 128));
	     T3 = (rise_but1 && (pot < 128));
	     T4 = rise_but2;
	     
	     
		 
		 /* Initialisation des appels et reponses */
		 
		 appel_e1 =0; appel_e2 =0;appel_e3 =0;appel_e4 =0;
		 reponse_e1 =0;reponse_e2 =0;reponse_e3 =0;reponse_e4 =0;
		 stable =0;
		 
		 while (stable ==0)
		 {
			 old_e1 =e1;
			 old_e2 =e2;
			 old_e3 =e3;
			 old_e4 =e4;
			 
			 
			 /* calcul des appels et des reponses */
			 if((e1 == 1) && T1)
			 {		appel_e2 = 1;
					reponse_e1 = 1;
			 }
			 if((e2 == 1) && T2)
			 {		appel_e3 = 1;
					reponse_e2 = 1;
			 }
			 if((e3 == 1) && T3)
			 {		appel_e4 = 1;
					reponse_e3 = 1;
			 }
			 if((e4 == 1) && T4)
			 {		appel_e1 = 1;
					reponse_e4 = 1;
			 }
			 
			#if 1
			printf("\n appel_e1 : %d \n reponse_e1 : %d", appel_e1, reponse_e1);
			printf("\n appel_e2 : %d \n reponse_e2 : %d", appel_e2, reponse_e2);
			printf("\n appel_e3 : %d \n reponse_e3 : %d", appel_e3, reponse_e3);
			printf("\n appel_e4 : %d \n reponse_e4 : %d", appel_e4, reponse_e4);
			#endif
			
			
			 
			 /*Calcul des évolutions*/
			 
			 e1 = appel_e1 || (e1 && !(reponse_e1));
			 e2 = appel_e2 || (e2 && !(reponse_e2));
			 e3 = appel_e3 || (e3 && !(reponse_e3));
			 e4 = appel_e4 || (e4 && !(reponse_e4));

			 /*calcul de la stabilité*/
			 if (e1 == old_e1 && e2 == old_e2 && e3 == old_e3 && e4 == old_e4)
			 {
					stable = 1;			 
			 }	      

	     
	     }
	     
		#if 1
			cmpt ++;
		#endif
		
		#if 1
		printf("\n itération boucle stable : %d", cmpt);
		#endif
		
		#if 1
		printf("\n e1 : %d \n e2 : %d \n e3 : %d \n e4 : %d", e1, e2, e3, e4);
		#endif
}
	 
		
	return 0;
}

int main()
{
		grafcet_interpreter();
		return 0;
}
