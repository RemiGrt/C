/*=====================================
*
*        oO  ADN   Oo
*
*=====================================
*
* File : score.h
* Date : 20 nov 10
* Author : Hilaire Thibault
*
*=====================================
*
* Algorithme de degré de ressemblance
*/


/* Fonction qui retourne le maxi de 3 nombres
Paramètres :
- a,b,c : trois entiers dont on veut le maximum
Retour :
- le maximum des trois */
int maxi( int a, int b, int c);


/* Fonction qui calcule la similarité entre deux chaînes en 
utilisant l'algorithme de Needleman et Wunsch
Paramètres :
- ch1 et ch2 : deux chaines de caractères
Retour :
- indice de similarité (entier) */
int NeedlemanWunsh( char* ch1, char* ch2);


/* Fonction qui calcule le pourçentage d'inclusion d'une chaine dans une autre
Paramètres :
- ch1 et ch2 : deux chaines de caractères
Retour :
- le pourçentage d'inclusion (réel entre 0 et 1)*/
float pourcentageInclusion( char* ch1, char* ch2);
