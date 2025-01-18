/**
* \file 
* 				asm.h
* \author 
* 				Jeanne Baumier & Thomas Broussard
* \date 
* 				6 février 2017
* \brief 
* 				Regroupe les fonctions permettant de convertir un fichier assembleur en un fichier .o
* \version 
* 				1 
* \date 
* 				11/02/17
* \brief 
* 				Suppression des instructions présentes dans le programme (remplacé par instructions.h)
*/

#ifndef __ASM_H__
#define __ASM_H__

/*#define MAX_LABELS_SIZE 1000
#define MAX_IDENTS_SIZE 1000
#define MAX_SEGMENT_SIZE 1000*/
#define TAILLE_BUFFER 1000
/*
##############################################
#####    Déclaration des fonctions 	   #######
##############################################
*/

/** \fn  
 * 			void parseAsm (FILE* fichier_src)
 * \brief 
 * 			Convertis un fichier source contenant des instructions en un fichier contenant des instructions représentées par des entiers
 * \param[in] 
 * 			*fichier_src 			Fichier source
 */
void parseAsm (FILE*);


/** \fn  
 * 			void resolveReferences()
 * \brief 
 * 			Permet de compléter toute les références indéfinies
 */
void resolveReferences();


/** \fn  
 * 			void generateBinary(FILE* fichier_dest)
 * \brief 
 * 			Génère le fichier .bin grâce au tableau codeSegment, précédemment complété par les 1ère et 2ème parse
 * \param[in] 
 * 			*fichier_dest 		Fichier de destination
 */
void generateBinary(FILE*);


/** \fn  
 * 			void AddInstruction(char* line)
 * \brief 
 * 			Permet de décoder une instruction et remplir le tableau codeSegment avec
 * \param[in] 
 * 			*line 			Ligne à décoder (sous forme d'une chaîne de caractères regroupant l'intégralité de la ligne
 */
 void AddInstruction(char* line);
 
 /** \fn  
 * 			void addLabel(char *line, int addr)
 * \brief 
 * 			Complète le tableau de structures contenant les labels (variable globale)
 * \param[in] 
 * 			*line 		Ligne courante
 * \param[in] 
 * 			addr 		Adresse de la ligne courante
 */
void addLabel(char *line, int addr);


/** \fn  
 * 			void dumpBinaryCode(char* filename)
 * \brief 
 * 			Créé un fichier de debug permettant de vérifier que la source a été correctement convertie
 * \param[in] 
 * 			*filename 		Fichier source
 */
void dumpBinaryCode(char*);


/** \fn  
 * 			void Clean_Memory()
 * \brief 
 * 			Supprime les espaces mémoires alloués dynamiquement dans le programme
 */
 void Clean_Memory();

#endif
