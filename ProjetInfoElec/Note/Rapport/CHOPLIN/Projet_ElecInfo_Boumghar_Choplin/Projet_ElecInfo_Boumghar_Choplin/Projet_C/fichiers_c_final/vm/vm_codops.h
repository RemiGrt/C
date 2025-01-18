
/*! \mainpage Projet Informatique
 *
 * \section Introduction
 * Nous avons reçu comme projet de réaliser un interpréteur de grafcet. Nous allons vous présenter ici les différentes parties de ce projet.
 * Vous trouverez dans le menu de gauche la description de chaque blocks. Pour réaliser
 * ce projet nous avons programmé un compilateur, un assembleur et une machine virtuelle.
 * Voici le fonctionnement de l'interpréteur : pour commencer le compilateur va analyser un grafcet et générer un fichier avec des instructions en assembleur
 * puis l'assembleur va convertir le fichier assembleur en opcode. Enfin la machine virtuelle va être capable d'interpréter cet opcode et de générer de nouvelles valeurs de variable.
 * Par la suite le projet a évolué il fallait être capable d'interpréter le grafcet sur le microcontroleur.
 * Pour cela il falait envoyer l'opcode généré par l'assembleur sur le microcontôleur c'est le role du programme serialtransfer.
 * La machine virtuelle se trouvera alors sur le microcontroleur et le tableau de variables sera constutué des entrées d'un système, comme par exemple des capteurs, et de ses sorties, par exemple un moteur.
 *
 *\section Liste_des_fichiers_utiles:
 * - asm.c
 * - asm.harderr
 * - ast.c
 * - serialtransfer.c
 * - evm.c
 * - vm_codops.h
/


/*! \file vm_codops.h
 * \details
 * \section Présentation
 *
 * Ce programme définit la valeur des instructions en opcode
 * 
 *
*/


#define I_ADD 0
#define I_MULT 1
#define I_PUSHI 100
#define I_HALT 400
#define I_PUSH 101
#define I_EQ 12
#define I_POP 102
#define I_JF 200 
#define I_J 201
#define I_LS 13
#define I_AND 300


#define I_SUB 66
#define I_NEG 67
#define I_GT 68
#define I_OR 69
#define I_NOT 70
