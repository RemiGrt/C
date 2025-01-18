/**
* \file 
* 			ast.c
* \author 
* 			Jeanne Baumier & Thomas Broussard
* \date 
* 			12 juin 2017
* \brief 
* 			Ce code permet de générer un fichier asm puis un fichier bin à partir d'un fichier grafcet
*/

#include "ast.h"

/*! compteurLabel permet de compter le nombre de Labels*/
int compteurLabel=0;
/*! compteurEtapes permet de compter le nombre de Labels*/
int compteurEtapes=0;

int num_variable;

/** \fn 
 * 		nodeType *createNumericNode(float v)
 * \brief 
 * 		Permet de creer un noeud de type numerique
 * \param[in] 
 * 		v	Valeur numérique
 * \return 
 *			\b p : une structure nodeType avec un type, et une valeur numérique associés
 */
nodeType *createNumericNode(float v)
{
  nodeType *p;

  if ((p=(nodeType*)malloc(sizeof(nodeType))) == NULL)
    {
      printf("out of memory error\n");
      exit(1);
    }

  p->type=typeNumeric;
  p->t_numeric.valeur=v;
	
  return p;
}

/** \fn 
 * 		nodeType *createOperatorNode(int oper, int nops, ...) 
 * \brief 
 * 		Permet de creer un noeud de type operateur
 * \param[in] 
 * 		oper	operateur
 * \param[in] 
 * 		nops	blabla
 * \return 
 *			\b p : une structure nodeType
 */
nodeType *createOperatorNode(int oper, int nops, ...) 
{
  va_list ap;
  nodeType *p;
  int i;

  /* allocate node */
  if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
    {
      printf("out of memory error\n");
      exit(1);
    }
  if ((p->t_oper.op = (nodeType**)malloc(nops * sizeof(nodeType))) == NULL)
    {
      printf("out of memory error\n");
      exit(1);
    }

  /* copy information */
  p->type = typeOperator;
  p->t_oper.oper = oper;
  p->t_oper.nOperands = nops;
  va_start(ap, nops);
  for (i = 0; i < nops; i++)
    p->t_oper.op[i] = va_arg(ap, nodeType*);
  va_end(ap);
  return p;
}

nodeType *createIdentifierNode(char *id,int flag)
{
  nodeType *p;

  if ((p=malloc(sizeof(nodeType))) == NULL)
    {
      printf("out of memory error\n");
      exit(1);
    }

  p->type=typeIdentifier;
  p->t_identifier.ident=strdup(id);
  p->t_identifier.flag=flag;
  if (strncmp(p->t_identifier.ident,"but",3)==0)
    p->t_identifier.key=KEY_BUTTON;
  else if (strncmp(p->t_identifier.ident,"ana",3)==0)
    p->t_identifier.key=KEY_ANA;
  else if (strncmp(p->t_identifier.ident,"tor",3)==0)
    p->t_identifier.key=KEY_TOR;
  else if (strncmp(p->t_identifier.ident,"pwm",3)==0)
    p->t_identifier.key=KEY_PWM;
  else
    p->t_identifier.key=KEY_IDENT;

  return p;
}

void generateAsmExpression(nodeType *n, FILE *fout)
{
  if (n==NULL)
    return;
    
  switch (n->type)
    {
    case typeNumeric:
      {
		 //fprintf(nvledest, "\t\tPUSHI %d\n", codeSegment[p+1]);
        fprintf(fout,"\t\tPUSHI %d\n",n->t_numeric.valeur);
      }
      break;
    case typeIdentifier:
      {
			num_variable = Extract_Num(n->t_identifier.ident);
        if (strncmp(n->t_identifier.ident,"but",3)==0)
          {
			num_variable = num_variable * 3;
            if (n->t_identifier.flag==0)
              fprintf(fout,"\t\tPUSH %d\n", num_variable);
            else if (n->t_identifier.flag==1)
              fprintf(fout,"\t\tPUSH %d\n", num_variable+1);
            else if (n->t_identifier.flag==2)
              fprintf(fout,"\t\tPUSH %d\n", num_variable+2);
          }
        else if (strncmp(n->t_identifier.ident,"ana",3)==0)
          {
				fprintf(fout,"\t\tPUSHI 1\n");
				fprintf(fout,"\t\tPOP %d\n", num_variable*2 + 64);
				fprintf(fout,"\t\tPUSH %d\n", num_variable*2 + 65);
          }
      }
      break;
    case typeOperator:
      {
        switch (n->t_oper.oper)
          {
          case OPER_ADD:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\t\tADD\n");
            break;
          case OPER_SUB:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\t\tSUB\n");
            break;
          case OPER_MULT:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\t\tMULT\n");
            break;
          case OPER_DIV:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\t\tDIV\n");
            break;
          case OPER_AND:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\t\tAND\n");
            break;
          case OPER_OR:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\t\tOR\n");
            break;
          case OPER_NOT:
            generateAsmExpression(n->t_oper.op[0],fout);
            fprintf(fout,"\t\tNOT\n");
            break;
          case OPER_INF:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\t\tEQI\n");
            break;
          case OPER_SUP:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\t\tEQS\n");
            break;
          case OPER_EQ:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\t\tEQ\n");
            break;
          case OPER_NE:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\t\tEQ\n");
            fprintf(fout,"\t\tNOT\n");
            break;
          case OPER_SEQUENCE:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            break;
          default:
            break;
          }
      }
      break;
    }
}


void pushRefEtape(etapeRefNode **head, char *n)
{
  if (*head!=NULL)
    {
      etapeRefNode *current=*head;

      while (current->next != NULL)
        current=current->next;

      current->next=(etapeRefNode*)malloc(sizeof(etapeRefNode));
      current->next->name=n;
      current->next->etape=NULL;
      current->next->next=NULL;
    }
  else
    {
      etapeRefNode *current=(etapeRefNode*)malloc(sizeof(etapeRefNode));
      current->name=n;
      current->next=NULL;
      *head=current;
    }
}

void pushRefTransition(transitionRefNode **head, char *n)
{
  if (*head!=NULL)
    {
      transitionRefNode *current=*head;

      while (current->next != NULL)
        current=current->next;

      current->next=(transitionRefNode*)malloc(sizeof(transitionRefNode));
      current->next->name=n;
      current->next->transition=NULL;
      current->next->next=NULL;
    }
  else
    {
      transitionRefNode *current=(transitionRefNode*)malloc(sizeof(transitionRefNode));
      current->name=n;
      current->next=NULL;
      *head=current;
    }
}

void pushAction(actionNode **head, actionNode *n)
{
  if (*head!=NULL)
    {
      actionNode *current=*head;

      while (current->next != NULL)
        current=current->next;

      current->next=n;
    }
  else
    {
      *head=n;
    }
}

void pushEtape(etapeNode **head, etapeNode *n)
{
  if (*head!=NULL)
    {
      etapeNode *current=*head;

      while (current->next != NULL)
        current=current->next;

      current->next=n;
    }
  else
    {
      *head=n;
    }
}

void pushTransition(transitionNode **head, transitionNode *n)
{
  if (*head!=NULL)
    {
      transitionNode *current=*head;

      while (current->next != NULL)
        current=current->next;

      current->next=n;
    }
  else
    {
      *head=n;
    }
}

void printRefEtapes(etapeRefNode *head)
{
  etapeRefNode *current;

  current=head;
  while (current!=NULL)
    {
      printf("--> %s\n",current->name);
      current=current->next;
    }
}

void printRefTransitions(transitionRefNode *head)
{
  transitionRefNode *current;

  current=head;
  while (current!=NULL)
    {
      printf("Nom\n");
      printf("--> %s\n",current->name);
      printf("Etapes Amont\n");
      //printRefEtapes(current->etapesAmont);
      printf("Etapes Aval\n");
      //printRefEtapes(current->etapesAval);
      printf("Receptivitel\n");
      //generateAsmExpression(current->receptivite,stdout);
		
      current=current->next;
    }
}

int nbEtapes(etapeNode *head)
{
  etapeNode *current=head;
  int lg=0;

  while (current!=NULL)
    {
      lg++;
      current=current->next;
    }
  return lg;
}

int nbTransitions(transitionNode *head)
{
  transitionNode *current=head;
  int lg=0;

  while (current!=NULL)
    {
      lg++;
      current=current->next;
    }
  return lg;
}

etapeNode *findEtapeByName(etapeNode *head, char *n)
{
  etapeNode *current=head;

  while (current!=NULL)
    {
      if (strcmp(current->name,n)==0)
        return current;

      current=current->next;
    }
  return NULL;
}

transitionNode *findTransitionByName(transitionNode *head, char *n)
{
  transitionNode *current=head;

  while (current!=NULL)
    {
      if (strcmp(current->name,n)==0)
        return current;

      current=current->next;
    }
  return NULL;
}

void printEtapes(etapeNode *en)
{
  etapeNode *current;

  current=en;
  while (current!=NULL)
    {
      printf("Nom\n");
      printf("--> %s %d %d\n",current->name,current->active,current->id);
      

      printf("Actions\n");

      actionNode *currentAction=current->actions;
      while (currentAction!=NULL)
        {
          printf("	action var=%s\n",currentAction->name);
          generateAsmExpression(currentAction->expr,stdout);
          currentAction=currentAction->next;
        }

      current=current->next;
    }
	
}

void printTransitions(transitionNode *tn)
{
  transitionNode *current;

  current=tn;
  while (current!=NULL)
    {
      printf("Nom\n");
      printf("--> %s\n",current->name);

      printf("Etapes Amont\n");
      printRefEtapes(current->etapesAmont);
      printf("Etapes Aval\n");
      printRefEtapes(current->etapesAval);

      current=current->next;
    }
	
}

void makeDual(etapeNode *en, transitionNode *tn)
{
  transitionNode *transition;
  etapeRefNode *ern;
  transitionRefNode *trn;
  etapeNode *etape;

  transition=tn; // l'argument 2
  while (transition!=NULL)
    {
		//printf("Nom de la transition : %s\n",transition->name);
      // on va parcourir la liste des etapes amont de la transition, qui
      // est construite sous la forme d'une liste de etapeRefNode
      // dont seule la partie name et le pointeur next sont pour l'instant remplis avec
      // des informations
	
      ern=transition->etapesAmont; //etapesAmont est de type etapeRefNode, comme ern
      while (ern!=NULL)
        {
          // on recupere ici le nom de l'etape
          // et on cherche parmi la liste des etapes celle qui
          // correspond au nom
	
          //ToDO : appel de findEtapeByName, retour stocké dans etape
				//Verifier "n" : nom . 
          etape=findEtapeByName(en,ern->name);
		  //printf("##en->name : %s\n", ern->name);

          // si on trouve l'etape, alors cela signifie deux choses
          // 1) que l'on peut
          // affecter le pointeur vers l'etape a l'etapeRefNode en cours
          // 2) que l'on peut ajouter la transition courante a la liste
          // des transitions aval de l'etape que l'on vient d'identifier
          // auquel cas on empile une nouvelle RefTransition dans
          // la liste des transitions aval de l'etape

		  
          if (etape!=NULL) // = si findEtapeByName nous renvoie qqch
            {
              ern->etape=etape;
              // ToDo : appel de pushRefTransition
				//Verifier "n" : nom .  
			  pushRefTransition(&etape->transitionsAval,transition->name);
			  //ou
			  //pushRefTransition(&tn,tn->name);
			  
            }
          else
            {
              printf(" non trouvee dans les etapes amont de la transition %s.\n", transition->name);
              exit(1);
            }
          ern=ern->next;
        }

      // on va parcourir la liste des etapes aval de la transition, qui
      // est construite sous la forme d'une liste de etapeRefNode
      // dont seule la partie name et le pointeur next sont pour l'instant remplis avec
      // des informations


      ern=transition->etapesAval;
      while (ern!=NULL)
        {
          // on recupere ici le nom de l'etape
          //printf("	%s..",ern->name);
          // et on cherche parmi la liste des etapes celle qui
          // correspond au nom

          //ToDO : appel de findEtapeByName, retour stocké dans etape
				//Verifier "n" : nom . 
          etape=findEtapeByName(en,ern->name);


          // si on trouve l'etape, alors cela signifie deux choses
          // 1) que l'on peut
          // affecter le pointeur vers l'etape a l'etapeRefNode en cours
          // 2) que l'on peut ajouter la transition courante a la liste
          // des transitions amont de l'etape que l'on vient d'identifier
          // auquel cas on empile une nouvelle RefTransition dans
          // la liste des transitions amont de l'etape

          if (etape!=NULL)
            {

              ern->etape=etape;
              // ToDo : appel de pushRefTransition 
				//Verifier "n" : nom .  
			  pushRefTransition(&etape->transitionsAmont,transition->name);
            }
          else
            {
              printf(" non trouvee dans les etapes aval de la transition %s.\n",
                     transition->name);
              exit(1);
            }
          ern=ern->next;
        }

      // ToDo : Mise à jour de transition avec la transition suivante
	transition = transition->next;
    }

  // derniere passe, on parcourt les etapes, et en particulier leurs listes
  // de transitions amont et aval, de maniere a modifier le champs transition
  // des elements transitionRefNode pour mettre la structure de donnees d'equerre

  etape=en;
  while (etape!=NULL)
    {

      trn=etape->transitionsAmont;
      while (trn!=NULL)
        {
			transition=findTransitionByName(tn,trn->name);

			trn->transition=transition;
			
			// ToDo  Mise à jour de trn avec trn suivant
			trn = trn->next;		

        }
        
		trn=etape->transitionsAval;
		while (trn!=NULL)
        {
 
          // ToDo meme chose que le derner while (3 instructions)
          transition=findTransitionByName(tn,trn->name);

          trn->transition=transition;
          
          // ToDo  Mise à jour de trn avec trn suivant
		  trn = trn->next;
        }

      etape=etape->next;
    }
}


/** \fn 
 * 		 int Extract_Num(char *str)
 * \brief 
 * 		Permet d'extraire un chiffre d'une chaine de caractere
 * \param[in] 
 * 		*str	Chaine de caractere
 * \return 
 *			\b Num : une structure nodeType avec un type, et une valeur numérique associés
 */
 int Extract_Num(char *str)
{
	char Vide1[100];
	Vide1[0] = '\0';
	char Vide2[100];
	Vide2[0] = '\0';
	int Num=0;
	sscanf(str, "%s%d%s",Vide1,&Num,Vide2);
	return Num;
}


// 0 : but0
// 1 : but0'rise
// 2 : but0'fall
// 3 : but1
// 4 : but1'rise
// 5 : but1'fall
// 6 : an0
// 7 : an1
// 8 : led0
// 9 : led1
// 10: led2
// 11: led3
// 13: stable 79

// 80: e0...nbEtapes-1.
// 80+nbEtapes: old_e0...
// 80+nbEtapes*2: appel_e0...
// 80+nbEtapes*3: reponse_e0...

void generateCode(etapeNode *en, transitionNode *tn)
{
  transitionNode *transition;
  etapeNode *etape;
  actionNode *an;
  int n,i;
  /*********************************************
   * Affichage du Mapping 
   * 		Entrées/Sorties précédées d'un # pour le mettre en commentaire 
   *********************************************/
	//Mapping des entrées
  printf("# 000 : but0\n");
  printf("# 001 : but0'rise\n");
  printf("# 002 : but0'fall\n");
  printf("# 003 : but1\n");
  printf("# 004 : but1'rise\n");
  printf("# 005 : but1'fall\n");
  printf("# ...\n");
  printf("# 047 : but15'fall\n");
  
	//Mapping des sorties
  printf("# 048 : led0\n");
  printf("# ...\n");
  printf("# 050 : led3\n");
    
    //Mapping des ADC
  printf("# 065 : an0\n");
  printf("# 067 : an1\n");
  printf("# 069 : an2\n");
  
	//Mapping du PWM
  printf("# 071 : PWM0_Freq\n");
  printf("# 072 : PWM0_Duty\n");
  printf("# 074 : PWM1_Freq\n");
  printf("# 075 : PWM1_Duty\n");
  printf("# 077 : PWM2_Freq\n");
  printf("# 078 : PWM2_Duty\n");
  
  printf("# 079 : stable \n");

  n=nbEtapes(en);
  etape=en;
  
  
// 80: e0...nbEtapes-1.
// 80+nbEtapes: old_e0...
// 80+nbEtapes*2: appel_e0...
// 80+nbEtapes*3: reponse_e0...

  /*********************************************
   * Affichage du Mapping 
   * 		Affichage des étapes actuelles
   * 		Etapes précédées d'un # pour le mettre en commentaire 
   *********************************************/
   
  while (etape!=NULL)
    {
      printf("# %3.3d : %s\n",80+etape->id,etape->name);
      etape=etape->next;
    }

  etape=en;
  /*********************************************
   * Affichage du Mapping 
   * 		Affichage des étapes précédentes
   * 		Etapes précédées d'un # pour le mettre en commentaire 
   *********************************************/
  while (etape!=NULL)
    {
      printf("# %3.3d : old_%s\n",80+n+etape->id,etape->name);
      etape=etape->next;
    }

  etape=en;
  /*********************************************
   * Affichage du Mapping 
   *		Affichage des appels d'étapes
   * 		Etapes précédées d'un # pour le mettre en commentaire 
   *********************************************/
  while (etape!=NULL)
    {
      printf("# %3.3d : appel_%s\n",80+2*n+etape->id,etape->name);
      etape=etape->next;
    }

  etape=en;
  /*********************************************
   * Affichage du Mapping 
   *		Affichage des réponses d'étapes
   * 		Etapes précédées d'un # pour le mettre en commentaire 
   *********************************************/
  while (etape!=NULL)
    {
      printf("# %3.3d : reponse_%s\n",80+3*n+etape->id,etape->name);
      etape=etape->next;
    }
	
  /*********************************************
   * Initialisation de :
   * 		- stable
   * 		- appel_eX
   * 		- reponse_eX
   *********************************************/
  printf("# INITIALISATION variable stable\n");
  printf("\t\tPUSHI 0\n");
  printf("\t\tPOP 79\n");
  etape=en;
  
	printf("# RAZ des variables appel_X et reponse_X\n"); 
  while (etape!=NULL)
    {
      printf("\t\tPUSHI 0\n");
      //printf("#\t\tPOP appel_%s\n",etape->name);
      printf("\t\tPOP %d\n",80+2*n+etape->id);
      printf("\t\tPUSHI 0\n");
      //printf("#\t\tPOP reponse_%s\n",etape->name);
      printf("\t\tPOP %d\n",80+3*n+etape->id);
		
      etape=etape->next;
    }

  /*********************************************
   * étiquette mainloop de notre code asm
   *********************************************/
   
  printf("mainloop :\n");
  /*printf("# INITIALISATION step e0 : active\n");
  printf("\t\tPUSHI 1\n");
  printf("\t\tPOP 80\n");*/
  
  
  /*********************************************
   * actions contenues dans le mainloop de notre code asm
   *********************************************/
   
  printf("\t\tPUSH 79\n");
  printf("\t\tPUSHI 0\n");
  printf("\t\tEQ\n");
  printf("\t\tJF fin_de_loop\n");


  etape=en;
  
  /*********************************************
   * Sauvegarde des états précédents
   *********************************************/
   
  printf("# SAUVEGARDE DES ETATS PRECEDENTS\n");
  while (etape!=NULL)
	{
		printf("\t\tPUSH %d\n",80+etape->id);
		printf("\t\tPOP %d\n",80+n+etape->id);
		etape=etape->next;
	}
	
   /*printf("# INITIALISATION step e0 : active\n");
  printf("\t\tPUSHI 1\n");
  printf("\t\tPOP 80\n");*/
  /*********************************************
   * On franchit les transitions (transition 0, puis 1, puis 2, puis 3)
   *********************************************/
   
	transition=tn;
	while (transition!=NULL)
	{
		printf ("#Transition->name : %s\n", transition->name);
		
		/*********************************************
		* On crée deux variables de type etapeRefNode :
		* 	- une pour l'étape amont
		* 	- une pour l'étape aval
		*********************************************/
		
		etapeRefNode *amont,*aval;
		amont=transition->etapesAmont;
		
		/*********************************************
		* Tant qu'on a des étapes amont, on teste les transitions
		* 1/ Est ce qu'on est dans l'étape EX
		* 2/ Est ce qu'on vérifie les conditions de la transition/réciptivité ou non ?
		*********************************************/
		
		while(amont!=NULL)
		{
			etape = amont->etape;
			
			/*********************************************
			* On récupère la valeur de la variable E0
			*********************************************/
			printf("\t\tPUSH %d\n",80+etape->id);
			/*********************************************
			* On met "1" sur la pile
			*********************************************/
			printf("\t\tPUSHI 1\n");
			/*********************************************
			* On teste l'égalité
			*********************************************/
			printf("\t\tEQ\n");
			amont=amont->next;
		}
		/*********************************************
		* On génère l'asm pour la réceptivité, et on stocke dans stdout comme ligne 348 :
		* fct generateAsmExpression : 
		* 	va différer selon les infos contenues dans la variable transition : 
		* 			cela peut faire appel à des push de différentes variables, tout dépend du grafcet du coffre fort
		*********************************************/
		generateAsmExpression(transition->receptivite,stdout);
		printf("\t\tAND\n");
		/*********************************************
		* Si la transition n'est pas vérifiée, on go sur une autre étiquette
		*********************************************/
		printf("\t\tJF Etiquette%d\n",compteurLabel);
		
		aval=transition->etapesAval;
		/*********************************************
		* Tant qu'on a des étapes aval, on teste les transitions
		* 		On met 1 dans les cases des variables 80+2*n+etape->id
		* 
		* Il s'agit des instructions à réaliser dans le cas où un franchissement de transition est validé.
		* Si c'est le cas, on passe les variables Appel et Réponse de la transition concerné à 1.
		*********************************************/
		while (aval!=NULL)
		{
			etape=aval->etape;
			printf("\t\tPUSHI 1\n");
			//printf("#\t\tPOP appel_%s\n",etape->name);
			printf("\t\tPOP %d\n",80+2*n+etape->id);
			aval=aval->next;
		}
			
		amont=transition->etapesAmont;
		/*********************************************
		* Tant qu'on a des étapes aval, on teste les transitions
		* 		On met 1 dans les cases des variables 80+3*n+etape->id)
		* 
		* Il s'agit des instructions à réaliser dans le cas où un franchissement de transition est validé.
		* Si c'est le cas, on passe les variables Appel et Réponse de la transition concerné à 1.
		*********************************************/
		while (amont!=NULL)
		{
			etape=amont->etape;
			printf("\t\tPUSHI 1\n");
			//printf("#\t\tPUSH reponse_%s\n",etape->name);
			printf("\t\tPOP %d\n",80+3*n+etape->id);
			amont=amont->next;
		}
		printf("Etiquette%d :\n",compteurLabel);
		compteurLabel++;

		
		/*********************************************
		* On passe à la transition suivante
		*********************************************/
		transition=transition->next;
	}
  
  
etape=en;
	while (etape!=NULL)
	{
		printf ("#Mise à jour de la valeur de l'étape %s\n", etape->name);
		//printf("#\t\tPUSH %s\n",etape->name);
		/*********************************************
		* On récupère les valeurs des cases
		* 		- eX (étape actuelle)
		* 		- reponse_eX (réponse étape actuelle)
		*********************************************/
		printf("\t\tPUSH %d\n",80+etape->id);
		//printf("#\t\tPUSH reponse_%s\n",etape->name);
		printf("\t\tPUSH %d\n",80+3*n+etape->id);
		printf("\t\tNOT\n");
		printf("\t\tAND\n");
		//printf("#\t\tPUSH appel_%s\n",etape->name);
		/*********************************************
		* On récupère la valeur de la case
		* 		- appel_eX 
		*********************************************/
		printf("\t\tPUSH %d\n",80+2*n+etape->id);
		printf("\t\tOR\n");
		//printf("#\t\tPOP %s\n",etape->name);
		/*********************************************
		* On enregistre la valeur dans la case
		* 		eX (etape actuelle)
		*********************************************/
		printf("\t\tPOP %d\n",80+etape->id);
		
		
		/*********************************************
		* On répète cela pour toutes les étapes
		*********************************************/
		etape=etape->next;
	}

		/*********************************************
		* On teste maintenant la stabilité
		*********************************************/
	printf ("#TEST DE STABILITE\n");
	etape=en;
	while (etape!=NULL)
	{
		//printf("#\t\tPUSH %s\n",etape->name);
		/*********************************************
		* On prend la valeur de la variable eX (etape souhaitée)
		* On prend la valeur de la variable old_eX (etape souhaitée)
		* On teste la stabilité par l'opérateur EQ 
		*********************************************/
		printf("\t\tPUSH %d\n",80+etape->id);
		//printf("#\t\tPUSH old_%s\n",etape->name);
		printf("\t\tPUSH %d\n",80+n+etape->id);
		printf("\t\tEQ\n");
		
		/*********************************************
		* On répète cela pour toutes les étapes
		*********************************************/
		etape=etape->next;
	}
	n=nbEtapes(en);
		/*********************************************
		* On vide la pile
		* 		On utilise l'opérateur AND pour vider la pile et ne laisser qu'une ligne
		* 		Selon la valeur de cette unique case de la pile, nous effectuons ou non la suite du programme (sinon on go à une autre partie du code asm)
		*********************************************/
	for (i=0;i<n-1;i++)
		printf("\t\tAND\n");
		
	/*********************************************
	* Si c'est faux (valeur 0), on go à la balise next_loop
	*********************************************/		
	printf("\t\tJF next_loop\n");
	
	/*********************************************
	* Si c'est vrai (valeur 1)
	* 		Il faut mettre 1 dans la variable "stable" 
	*********************************************/	
	printf("\t\tPUSHI 1\n");
	//printf("#\t\tPOP stable\n");
	printf("\t\tPOP 79\n");

	/*********************************************
	* balise next_loop :  ne contient uniquement un jump vers la mainloop
	*********************************************/		
	printf("next_loop :\n");
	printf("\t\tJ mainloop\n");

	/*********************************************
	* balise fin_de_loop :  ne contient uniquement un jump vers la mainloop
	*********************************************/		
	printf("fin_de_loop :\n");

	/*********************************************
	* Affectation des valeurs aux sorties
	*********************************************/		
	printf ("#On affecte maintenant les valeurs aux sorties\n");
	etape=en;
	while (etape!=NULL)
	{
		//printf("#\t\tPUSH %s\n",etape->name);
	/*********************************************
	* pour chacune des étapes 
	* 	on teste l'égalité avec 1 pour savoir si on est dans la bonne étape
	* 			si oui : on met la valeur 0 dans la sortie correspondante à l'étape
	* 			si non : on saute sur une autre étiquette 
	*********************************************/	
		printf("\t\tPUSH %d\n",80+etape->id);
		printf("\t\tPUSHI 1\n");
		printf("\t\tEQ\n");
		printf("\t\tJF sortie%d\n",compteurEtapes);

	/*********************************************
	* tant qu'on a des actions à faire
	* 			on utilise la fonction generateAsmExpression
	* 	on compare simplement le nom de l'étape d'action an avec les noms des sorties.
	* Si un des noms correspond, alors on effectue un pop sur la sortie concernée
	*********************************************/	
		an=etape->actions;
		while (an!=NULL)
		{
			generateAsmExpression(an->expr,stdout);
			//printf("%s\n",an->name);
			num_variable = Extract_Num(an->name);
			printf("\t\tPOP %d\n", num_variable+48);
			an=an->next;
		}

		printf("sortie%d :\n",compteurEtapes);

		compteurEtapes++;
		etape=etape->next;
	}
	printf("\t\tHALT\n");
	printf("\t\tend\n");
}

