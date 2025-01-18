/**
* \file Instructions.h
* \author Jeanne Baumier & Thomas Broussard
* \date 6 février 2017
* \brief Regroupe toutes les instructions utiles pour l'exécution du compilateur
* 			 
*/
#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

/*! Effectue une addition entre deux valeurs situées au sommet de la pile */
#define I_ADD		0		
/*! Effectue une multiplication entre deux valeurs situées au sommet de la pile */
#define I_MULT		1	
/*! Effectue une soustraction entre deux valeurs situées au sommet de la pile */
#define I_SUB			2		
/*! Effectue une division entre deux valeurs situées au sommet de la pile et garde l'entier inférieur*/
#define I_DIV			3		
/*! Vérifie si les deux valeurs au sommet de la pile sont égales ou non  (renvoie '1' ou '0') */
#define I_EQ			12		
/*! Vérifie si la valeur au sommet de la pile est supérieure à la valeur en dessous dans la pile (renvoie '1' ou '0') */
#define I_EQS			13
/*! Vérifie si la valeur au sommet de la pile est inférieure à la valeur en dessous dans la pile (renvoie '1' ou '0') */
#define I_EQI			14
/*! Effectue un ET entre deux valeurs situées au sommet de la pile ('1' ou '0') */
#define I_AND		20
/*! Inverse la valeur au sommet de la pile ('1' ou '0') */
#define I_NOT		21 
/*! Effectue un OU entre deux valeurs situées au sommet de la pile ('1' ou '0') */
#define I_OR			22	 
/*! Effectue un OU EXCLUSIF entre deux valeurs situées au sommet de la pile ('1' ou '0') */
#define I_XOR			23 
/*! Ajoute une valeur immédiate dans la pile d'exécution */
#define I_PUSHI		100
/*! Ajoute une valeur contenue dans le tableau de variable dans la pile d'exécution */
#define I_PUSH		101 
/*! Sauvegarde la valeur au sommet de la pile dans le tableau de variable */
#define I_POP			102	 
/*! Permet d'exécuter un Jump si la condition qui le précède est fausse */
#define I_JF				200 
/*! Permet d'exécuter un Jump inconditionnel */
#define I_J				201	
/*! Indique la fin du programme */
#define I_HALT		400	


#endif
