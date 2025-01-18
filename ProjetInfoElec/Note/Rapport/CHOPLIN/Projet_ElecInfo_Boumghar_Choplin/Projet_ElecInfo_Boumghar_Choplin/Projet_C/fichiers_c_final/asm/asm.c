#include "asm.h"

/*! \file asm.c
 *
 * \details
 *
 * \section Présentation
 * 
 * Ce programme permet d'assembler un fichier assembleur safe.asm en bytecode dans un fichier safe.bin *
 *
 * Il fonctionne en deux parties :
 * - 1ère phase d'assemblage : 
 *        - Génère un tableau de OP_CODE
 *        - Analyse et décode les instructions
 *        - Construit la liste des réfèrences indéfinies
 * - 2ème phase d'assemblage :
 *        - Complète le tableau de OP_CODE
 *        - Résoud les références indéfinies
 *
 *
 * \section Compilation
 * - Utilisation en console: ./asm.o      
 *
 * - Commande de compilation : gcc asm.c -o asm.o
 *
 * \section Liste_des_fonctions:
 *  - void addInstructionName(char *name, int opcod, int type, char *format, int nbops)
 *  - void addCode(char *line, int opcod, char *format, int type)
 *  - void decodeInstruction(char *line)
 *  - void resolveReferences(void)
 *  - void addLabel(char labelname[MAX_LINE_SIZE],int addr)
 *  - void parseAsm(FILE *fin)
 *  - void generateBinary(FILE *fout)
*/

int currentLabel; //variable pour l'indice du tableau des labels
int currentInst; //variable pour l'indice du tableau opcode, instruction en cours de traitement
int currentRef; //variable pour l'indice du tableau des références
int instructionDico; //variable pour l'indice du dictionnaire à remplir
char line[MAX_LINE_SIZE]; //tableau qui contient la ligne du fichier .asm étudiée
unsigned int codeSegment[MAX_CODESEGMENT_SIZE]; //tableau de l'opcode décodé


/*! \brief La fonction addInstructionName(char *name, int opcod, int type, char *format, int nbops)
// permet la construction d'un dictionnaire d'instruction, on ajoute alors à partir du main
// toutes les instructions que l'on utilisera en assembleur.
// Elles peuvent être de 3 types :
// - type 0 : elles ne demandent pas de décodage d'opérandes supplementaires (0 argument)
// - type 1 : le décodage d'un entier est nécessaire. Il y a une opérande (1 argument)
// - type 3 : le decodage d'une chaine de caracteres representant une etiquette est necessaire. Il y a une opérande (1 argument)
*/

void addInstructionName(char *name, int opcod, int type, char *format, int nbops)
{
	//on remplit la structure de l'instruction demandée
    tabInstructionNames[instructionDico].name = name; //nom de l'instruction en assembleur
    tabInstructionNames[instructionDico].opcod = opcod; //son opcode
    tabInstructionNames[instructionDico].type = type; //son type (0, 1 ou 3)
    tabInstructionNames[instructionDico].format = format; //son format (le type de l'opérande par exemple "%s	%d" pour le type 1)
    tabInstructionNames[instructionDico].nbops = nbops; //nombre d'opérande
    instructionDico++; //on attend l'instruction suivante à remplir dans le dictionnaire
}


/*! \brief La fonction addCode(char *line, int opcod, char *format, int type)
// est appelé après le décodage de l'instruction. Son type a été déterminé, on peut
// donc récupérer l'instruction décodée et son opérande puis le placer dans le tableau d'opcode.
//	Cette fonction fait le gros du travail de la phasee 1, en identifiant le type de l'instruction, en faisant
// le decodage supplémentaire, et en ajoutant des references.
*/

void addCode(char *line, int opcod, char *format, int type)
{
    printf("\netude de addCode\n");
    printf("type : -%d-\n",type);
    printf("opcod : -%d-\n",opcod);
    printf("line : -%s-\n\n",line);

    int i=0,j=0;
    int argument=0;
    int detectionEtiquette=0;
    char etiquetteTrouvee[MAX_LINE_SIZE];

    if(type == 0) //si c'est une instruction de type0 (pas d'opérande)
    {
	codeSegment[currentInst]=opcod; //on place l'opcode correspondant à l'instruction décodée dans le tableau
	currentInst++; //on attend l'instruction suivante
    }
    else if(type == 1) //si c'est une instruction de type1 (1 opérande)
    {
	codeSegment[currentInst]=opcod; //on place l'opcode correspondant à l'instruction décodée dans le tableau
	currentInst++; //on peut maintenant décoder son argument (un entier)

	while(line[i]!='\n') //tant que la fin de ligne n'est pas trouvée on va chercher la valeur de l'entier
	{
	    printf("dans addCoce caractere etudie : -%c-\n", line[i]);
	    printf("valeur de l'argument : -%d-\n",argument);
		
	    argument *= 10; //on multiplie l'argument par 10 afin d'y stocker le nouveau caractère qui va compléter le chiffre précédemment étudié
		
	    if((line[i]>='0') && (line[i]<='9')) //si le caractère est bien un nombre
	    {
			if(line[i-1]=='-') //si le nombre est négatif
			{
				argument -= line[i]-48;
			}
			else
			{
				argument += line[i]-48; //on étudie un caractère donc étudie sa valeur en ASCII, il faut donc le décoder pour obtenir l'entier
			}
	    }
	i++;
	}
	printf("valeur de l'argument finale : -%d-\n",argument);
	codeSegment[currentInst] = argument; //l'argument est décodé on peut donc le placer dans le tableau d'opcode
	printf("valeur de l'argument stocké : -%u-\n",codeSegment[currentInst]);
	currentInst++; //on attend l'instruction suivante	
    }
    else if(type == 3)//si c'est une instruction de type3 (une opérande)
    {
	codeSegment[currentInst]=opcod; //on place l'opcode correspondant à l'instruction décodée dans le tableau
	currentInst++; //on peut maintenant décoder son argument (une chaine de caractère)
	codeSegment[currentInst]=-1; //on indique dans l'opcode qu'il y a une étiquette on la résolvera lorsque toutes les instructions auront été décodées

	while(line[i]!='\n') //tant que le caractère de fin de chaîne n'est pas trouvé
	{
	    printf("caractere etudie -%c-\n",line[i]);
	    if(line[i]==0x09)	//si on trouve une tabulation
	    {
			detectionEtiquette++; //on incrémente une variable, on s'attend à trouver deux tabulations avant l'argument
			printf("valeur de detectionEtiquette : -%d-\n", detectionEtiquette);
			i++;
	    }
	    else if(detectionEtiquette==2)	//le début de l'argument est trouvé
	    {
			etiquetteTrouvee[j] = line[i]; //on mémorise le caractère étudié afin de reconstruire l'argument
			printf("caractere stocke : -%c-\n",etiquetteTrouvee[j]);		
			j++;
			etiquetteTrouvee[j] = '\0';
			i++;
	    }
	    else
	    {
			i++;
	    }
	}

	for(i=0;i<MAX_LINE_SIZE;i++)
	{
	    tabReferences[currentRef].label[i]=etiquetteTrouvee[i]; //on place alors l'argument trouvé dans le tableau de référence à résoudre
	}
	printf("etiquette trouvee : -%s-\n",etiquetteTrouvee);
	printf("etiquette stockee : -%s-\n",tabReferences[currentRef].label);
	tabReferences[currentRef].addrInCode=currentInst; // on indique à quel indice du tableau opcode se trouve cette référenceS
	currentRef++; //on attend la référence suivante
	currentInst++; //on attend l'instruction suivante
    }
    else
    {
		printf("erreur dans l'ajout au tableau codeSegment\n");
    }
}

/*! \brief La fonction decodeInstruction(char *line) est appelee par la boucle
// principale d'analyse lorsque la ligne d'assembleur lue n'est pas une étiquette
// (pas de : dans la ligne) ni un commentaire (pas de # dans la ligne).
// Elle fait appel à addCode() pour remplir codeSegment lorsque l'instruction est identifiée.
*/  
void decodeInstruction(char *line)
{
    int typeInstructionDecodee=-1, opcodDecodee=-1;
    int instructionDecodee=0;
    int i=0;	
    char *format;

    //identifier le type de l'instruction 0/1 ou 3
    for(i=0; i<MAX_IDENTS_SIZE; i++)
    {
		if(strstr(line,tabInstructionNames[i].name)) //on compare la ligne étudiée à notre dictionnaire afin de déterminer les caractéristiques de l'instruction
		{	
			//on vient placer les caractèristiques de l'instruction dans des variables pour faciliter le décodage supplémentaire lors de l'appel de addcode
			printf("instruction trouvee dans le dictionnaire : %s\n",tabInstructionNames[i].name);
			typeInstructionDecodee = tabInstructionNames[i].type;
			opcodDecodee = tabInstructionNames[i].opcod;
			format = tabInstructionNames[i].format;
			instructionDecodee=1;
			i = MAX_IDENTS_SIZE; //instruction décodé alors on sort de la boucle
		}
    }

    //appel addCode pour remplir codeSegment lorsque l'instruction est identifiée
    if(instructionDecodee=1)
    {	
		printf("instruction decodee : %d\n",opcodDecodee);
		addCode(line, opcodDecodee, format, typeInstructionDecodee);
    }
    else
    {
		printf("erreur de decodage\n");
    }   
}

/*! \brief La fonction resolveReferences(void) est appelee après l'analyse de l'assembleur
// afin re remplacer les références non résolus de l'opcode par l'adresse de l'opcode à laquelle
// elle renvoie. Pour cela on utilise le tableau des références et le tableau des labels. 
*/ 

void resolveReferences(void)
{
    int i,j;

    for(i=0;i<currentRef;i++) //on parcourt le tableau des reférences
    {
		for(j=0;j<currentRef;j++) //on parcourt le tableau des labels
		{
			if(!strcmp(tabReferences[i].label,tab_labels[j].label)) //une fois la référence trouvée dans le tableau des labels
			{
				codeSegment[tabReferences[i].addrInCode]=tab_labels[j].addr; //on place l'adresse à laquelle elle renvoie dans le tableau d'opcode
				j=currentRef;//on sort de la boucle pour passer à la référence suivante
			}
		}
    }
}


/*! \brief La fonction addLabel(char labelname[MAX_LINE_SIZE],int addr) est appelée
// lorsque qu'une étiquette est identifié lors de l'analyse de l'assembleur.
// Elle permet de déterminer l'étiquette et de la placer dans le tableau des labels
*/ 

void addLabel(char labelname[MAX_LINE_SIZE],int addr)
{
    int i=0;

    while(labelname[i]!='\n') //on parcourt la ligne tant que le caractère de fin de chaîne n'est pas trouvé
    {
        if(labelname[i]==':') //on remplace les ':' par le caractère de fin de chaîne
        {
            labelname[i]='\0'; //ca marque la fin du nom de l'étiquette
        }
	i++;
    }

    printf("labelname : -%s-\n",labelname);

    for(i=0;i<MAX_LINE_SIZE;i++) //on parcourt de nouveau la ligne qui ne comprend plus les ':'
    {
        tab_labels[currentLabel].label[i] = labelname[i]; //on la recopie dans le nom de l'étiquette
    }

    printf("labelname dans le tableau de label : -%s-\n",tab_labels[currentLabel].label);
    tab_labels[currentLabel].addr = addr; //on indique à quelle adresse on a rencontré cette étiquette
    printf("adresse dans le tableau de label : -%d-\n",tab_labels[currentLabel].addr);
    currentLabel++; //on attend l'étiquette suivante
}

/*! \brief Cette fonction parseAsm(FILE *fin) parcourt les lignes du fichier
// source assembleur tant qu'elle n'a pas rencontre de ligne avec
// "halt" à l'interieur. Pour chaque ligne il y a trois cas de figure:
// - si la ligne de texte contient un #, il s'agit d'un commentaire alors
//   on passe à la ligne suivante
// - si la ligne de texte contient un :, il s'agit d'une etiquette et
//   on la declare
// - sinon, il s'agit d'une instruction et on appelle decodeInstruction()
*/

void parseAsm(FILE *fin)
{
    malloc(sizeof(line));

    while(!strstr(line,"halt")) //tant que la fin du fichier marqué par halt n'est pas atteint
    {	
		fgets(line, 100, fin); //on récupère la ligne du fichier à étudier
	
		printf("-%s-\n",line);
        
        if(strstr(line,"#")) //si la ligne comprend un '#'
        {
            printf("# identifié\n");
			//il s'agit d'un commentaire, on ne fait rien
        }
        else if(strstr(line,":")) //si la ligne comprend ':'
        {
            printf(": identifié\n");
			addLabel(line,currentInst); //il s'agit d'une étiquette on appel alors addLabel() pour l'étudier
        }
        else //si la ligne n'est pas un commentaire ni une étiquette alors il s'agit d'une instruction
        {
			printf("instruction identifié\n");
            decodeInstruction(line); //on appel decodeInstruction pour la décoder
        }
    }
	printf("end identifié\n");
	fgets(line, 20, fin);
	printf("-%s-\n",line);
}

/*! \brief Cette fonction generateBinary(FILE *fout) permet de
// générer le fichier .bin qui contient l'opcode décodé ainsi que le nombre d'instruction.
*/

void generateBinary(FILE *fout)
{
    int i;
	
	fprintf(fout,"%d\n",currentInst); //on écrit dans la première ligne du fichier le nombre d'instruction
	
    for(i=0;i<currentInst;i++) //on parcourt le fichier opcode décodé
    {
		fprintf(fout,"%d : %d\n",i,codeSegment[i]); //on le recopie dans le fichier.bin avec son indice
    }

}


/*! \brief C'est la fonction principale du programme qui va demander l'analyse du fichier.asm
// puis il va demander la résolution des références et enfin la création du fichier.bin
*/

int main()
{
	FILE *fichierasm=fopen("safe.asm","r"); //ouverture du fichier assembleur
	FILE *fichierbin=fopen("safe.bin","w"); //ouverture du fichier bytecode
	
	if(fichierasm!=NULL) //si le fichier .asm n'est pas vide
	{
		currentLabel = 0;
		currentRef = 0;	
		currentInst = 0;
		instructionDico = 0;
		int i =0;
	
	//construction du dictionnaire
	//instruction de type0 : elles ne demandent pas de décodage d'opérandes
		addInstructionName("add", I_ADD, 0, "", 0);
		addInstructionName("sub", I_SUB, 0, "", 0);
		addInstructionName("mult", I_MULT, 0, "", 0);
		//addInstructionName("div", I_DIV, 0, "", 0);
		addInstructionName("neg", I_NEG, 0, "", 0);
		addInstructionName("and", I_AND, 0, "", 0);
		addInstructionName("or", I_OR, 0, "", 0);
		addInstructionName("not", I_NOT, 0, "", 0);
		addInstructionName("eq", I_EQ, 0, "", 0);
		addInstructionName("ls", I_LS, 0, "", 0);
		addInstructionName("gt", I_GT, 0, "", 0);
		addInstructionName("halt", I_HALT, 0, "", 0);
	//instruction de type1 : elles demandent le décodage d'une opérande
		addInstructionName("pushi", I_PUSHI, 1, "	%s	%d", 1); //le %s -> l'instruction et le %d -> l'opérande
		addInstructionName("push", I_PUSH, 1, "%s	%d", 1);
		addInstructionName("pop", I_POP, 1, "%s	%d", 1);
	//instruction de type3 : elles demandent le décodage d'une étiquette
		addInstructionName("jf", I_JF, 3, "%s	%s", 1); //le %s -> l'instruction et le 2ème %s -> l'étiquette
		addInstructionName("j", I_J, 3, "%s	%s", 1);

	/*	for(i=0;i<15;i++){
		    printf("%s\n",tabInstructionNames[i].name);
		    printf("%d\n",tabInstructionNames[i].opcod);
		    printf("%d\n",tabInstructionNames[i].type);
		    printf("%d\n",tabInstructionNames[i].nbops);
		    printf("\n");
		}
	*/

		parseAsm(fichierasm); //on analyse le fichier .asm
		resolveReferences(); //on résoud les références
		generateBinary(fichierbin); //on génère le fichier binaire



		printf("\ntableau references non resolus\n");
		printf("--------------------------------------\n");
		for(i=0;i<currentRef;i++)
		{
		    printf("%s : %d\n",tabReferences[i].label,tabReferences[i].addrInCode);
		}
		printf("--------------------------------------\n");

		printf("\ntableau labels\n");
		printf("--------------------------------------\n");
		for(i=0;i<currentRef;i++)
		{
		    printf("%s : %d\n",tab_labels[i].label,tab_labels[i].addr);
		}
		printf("--------------------------------------\n");

		printf("\nbytecod final\n");
		printf("--------------------------------------\n");
		for(i=0;i<currentInst;i++)
		{
		    printf("%d : %d\n",i,codeSegment[i]);
		}
		printf("--------------------------------------\n");
	}
}


