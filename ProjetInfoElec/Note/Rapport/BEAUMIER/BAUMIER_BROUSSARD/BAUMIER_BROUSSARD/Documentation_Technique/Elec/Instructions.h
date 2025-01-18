/**
* \file Instructions.h
* \author Jeanne Baumier & Thomas Broussard
* \date 6 fevrier 2017
* \brief Regroupe toutes les instructions utiles pour l'execution du compilateur
* 			 
*/
#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

/*! Effectue une addition entre deux valeurs situees au sommet de la pile */
#define I_ADD		0		
/*! Effectue une multiplication entre deux valeurs situees au sommet de la pile */
#define I_MULT		1	
/*! Effectue une soustraction entre deux valeurs situees au sommet de la pile */
#define I_SUB			2		
/*! Effectue une division entre deux valeurs situees au sommet de la pile et garde l'entier inferieur*/
#define I_DIV			3		
/*! Verifie si les deux valeurs au sommet de la pile sont egales ou non  (renvoie '1' ou '0') */
#define I_EQ			12		
/*! Verifie si la valeur au sommet de la pile est superieure a la valeur en dessous dans la pile (renvoie '1' ou '0') */
#define I_EQS			13
/*! Verifie si la valeur au sommet de la pile est inferieure a la valeur en dessous dans la pile (renvoie '1' ou '0') */
#define I_EQI			14
/*! Effectue un ET entre deux valeurs situees au sommet de la pile ('1' ou '0') */
#define I_AND		20
/*! Inverse la valeur au sommet de la pile ('1' ou '0') */
#define I_NOT		21 
/*! Effectue un OU entre deux valeurs situees au sommet de la pile ('1' ou '0') */
#define I_OR			22	 
/*! Effectue un OU EXCLUSIF entre deux valeurs situees au sommet de la pile ('1' ou '0') */
#define I_XOR			23 
/*! Ajoute une valeur immediate dans la pile d'execution */
#define I_PUSHI		100
/*! Ajoute une valeur contenue dans le tableau de variable dans la pile d'execution */
#define I_PUSH		101 
/*! Sauvegarde la valeur au sommet de la pile dans le tableau de variable */
#define I_POP			102	 
/*! Permet d'executer un Jump si la condition qui le precède est fausse */
#define I_JF				200 
/*! Permet d'executer un Jump inconditionnel */
#define I_J				201	
/*! Indique la fin du programme */
#define I_HALT		400	


#endif
