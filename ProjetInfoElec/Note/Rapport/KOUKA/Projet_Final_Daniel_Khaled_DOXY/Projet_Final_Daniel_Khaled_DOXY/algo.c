#include <stdio.h>
#include <stdlib.h>

void grafcet_interpreter()
{
    int stable = 0;
    int appel_e1,appel_e2,appel_e3,appel_e4;
    int reponse_e1,reponse_e2,reponse_e3,reponse_e4;
    int but1,but2,pot,old_but1,old_but2,rise_but1,rise_but2;
    int e1,e2,e3,e4;
    int old_e1,old_e2,old_e3,old_e4;
    int T1,T2,T3,T4;
    
    //init de e1 & oldbut
     e1= 1; e2 =0; e3 =0; e4 =0;
     old_but1 =0; old_but2=0;
     rise_but1 = 0;
      
     while (1)
     {
		 
         printf (" Veuillez entrer les valeurs des boutons \n");
         scanf ("%d %d %d",&but1,&but2,&pot);
        


		//calcul des rise_but //front montant
         if (old_but1 == 0 && but1 == 1)
         {
             rise_but1 = 1;
         }
         else
         {
			 rise_but1 = 0;
		 }
		 
		 if (old_but2 == 0 && but2 == 1)
         {
             rise_but2 = 1;
         }
         else
         {
			 rise_but2 = 0;
		 }
		 
        //lecture des entrées
         T1 = (rise_but1 && (pot < 128));
         T2 = (rise_but1 && (pot > 128));
         T3 = (rise_but1 && (pot < 128));
         T4 = rise_but2;
         
        //appel_x <= 0 ; reponse_x <= 0 ; stable <= 0
         appel_e1 =0;   appel_e2 =0;   appel_e3 =0;   appel_e4 =0;
         reponse_e1 =0; reponse_e2 =0; reponse_e3 =0; reponse_e4 =0;
         stable =0;
        
         while (stable ==0)
         {
	    // old ex = ex
         old_e1 =e1;
         old_e2 =e2;
         old_e3 =e3;
         old_e4 =e4;
           
           //calcul de appel_x & Reponse_x
            if((e1 == 1) && T1)
            {        
	         appel_e2 = 1;
             reponse_e1 = 1;
            } 
            if((e2 == 1) && T2)
            {        
		     appel_e3 = 1;
             reponse_e2 = 1;
            }
            if((e3 == 1) && T3)
            {   
		     appel_e4 = 1;
             reponse_e3 = 1;
            }
			if((e4 == 1) && T4)
			{        
			  appel_e1 = 1;
			  reponse_e4 = 1;
			}
			
		// calcul des états ex
		e1 = appel_e1 || (e1 && !(reponse_e1));
		e2 = appel_e2 || (e2 && !(reponse_e2));
		e3 = appel_e3 || (e3 && !(reponse_e3));
		e4 = appel_e4 || (e4 && !(reponse_e4));
		
		
		   // calcul de la stabilité
			if(old_e1==e1 && old_e2==e2 && old_e3==e3 && old_e4==e4)
			{
				stable = 1;
			}
         }
         
         // affectation des sorties
         if(e1 == 1)
         {
			 printf("E1 active \n");
		 }
		 else if(e2 == 1)
		 {
			 printf("E2 active \n");
		 }
		 else if(e3 == 1)
		 {
			 printf("E3 active \n");
		 }
		 else
		 {
			 printf("E4 active \n");
		 }
	}
}

int main(int argc, char** argv)
{
	grafcet_interpreter();
	return 0;
}
