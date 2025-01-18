/**
* \file graphinterpreter.c
* @brief code c permetant de simuler un G7
*/
#include <stdio.h>
#include <stdlib.h>
/***/
int but1=0,but2=0,An=0;/*!<variable pour la simulation des capteurs*/
int Stable=0;/*!<etat de stabilité du G7*/
int X1=0,X2=0,X3=0,X4=0;/*!< etape du G7*/
int Appel_X1=0,Appel_X2=0,Appel_X3=0,Appel_X4=0 ;/*!<utilisé pour calculer le changement d'étape*/
int Reponse_X1=0,Reponse_X2=0,Reponse_X3=0,Reponse_X4=0;/*!<utilisé pour calculer le changement d'étape*/
int Old_X1=0,Old_X2=0,Old_X3=0,Old_X4=0;/*!<utilisé pour calculer la stabilité*/
int Old_but1=0,Old_but2=0;/*!<utilisé pour calculer les front montants sur les boutons*/
int rise_but1=0,rise_but2=0;/*!<utilisé pour calculer les front montants sur les boutons*/


/*************/
int main()
{

// Etat initial
X1=1;

while(1){

    Stable=0;

    // Test
    // Acquisition des entrées et initialisation des variables internes
    printf("Etape:X%d%d%d%d\nb1 b2 An\n",X1,X2,X3,X4);
    scanf("%d %d %d",&but1,&but2,&An);

    // Détection front montant
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
        // Reinit Appel/Réponse état
        Appel_X1=0;Appel_X2=0;Appel_X3=0;Appel_X4=0;
        Reponse_X1=0;Reponse_X2=0;Reponse_X3=0;Reponse_X4=0;

        // X1 > X2
        if(X1==1 && rise_but1 && An<128)
        {
            Appel_X2=1;
            Reponse_X1=1;
        }

        // X2 > X3
        if(X2==1 && rise_but1 && An>128)
        {
            Appel_X3=1;
            Reponse_X2=1;
        }

        // X3 > X4
        if(X3==1 && rise_but1 && An<128)
        {
            Appel_X4=1;
            Reponse_X3=1;
        }

        // X4 > X1
        if(X4==1 && rise_but2)
        {
            Appel_X1=1;
            Reponse_X4=1;
        }

        // Calcul évolution
        X1= Appel_X1 || (X1 && !(Reponse_X1));
        X2= Appel_X2 || (X2 && !(Reponse_X2));
        X3= Appel_X3 || (X3 && !(Reponse_X3));
        X4= Appel_X4 || (X4 && !(Reponse_X4));

        // Test stabilité
        if((X1==Old_X1) && (X2==Old_X2) &&(X3==Old_X3) && (X4==Old_X4))
            Stable=1;

        // Affectation Old_VALEUR
        Old_X1=X1; Old_X2=X2; Old_X3=X3; Old_X4=X4;
        Old_but1=but1;
        Old_but2=but2;
    }


}
    return 0;
}
