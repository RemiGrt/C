#include "ast.h"

int compteurLabel=0;
int compteurEtapes=0;

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
        fprintf(fout,"\tpushi\t%d\n",n->t_numeric.valeur);
      }
      break;
    case typeIdentifier:
      {
        if (strncmp(n->t_identifier.ident,"but0",4)==0)
          {
            if (n->t_identifier.flag==0)
              fprintf(fout,"\tpush\t0\n");
            else if (n->t_identifier.flag==1)
              fprintf(fout,"\tpush\t1\n");
            else if (n->t_identifier.flag==2)
              fprintf(fout,"\tpush\t2\n");
          }
        else if (strncmp(n->t_identifier.ident,"but1",4)==0)
          {
            if (n->t_identifier.flag==0)
              fprintf(fout,"\tpush\t3\n");
            else if (n->t_identifier.flag==1)
              fprintf(fout,"\tpush\t4\n");
            else if (n->t_identifier.flag==2)
              fprintf(fout,"\tpush\t5\n");
          }
        else if (strncmp(n->t_identifier.ident,"ana0",4)==0)
          {
            fprintf(fout,"\tpush\t6\n");
          }
        else if (strncmp(n->t_identifier.ident,"ana1",4)==0)
          {
            fprintf(fout,"\tpush\t7\n");
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
            fprintf(fout,"\tadd\n");
            break;
          case OPER_SUB:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\tsub\n");
            break;
          case OPER_MULT:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\tmult\n");
            break;
          case OPER_DIV:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\tdiv\n");
            break;
          case OPER_AND:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\tand\n");
            break;
          case OPER_OR:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\tor\n");
            break;
          case OPER_NOT:
            generateAsmExpression(n->t_oper.op[0],fout);
            fprintf(fout,"\tnot\n");
            break;
          case OPER_INF:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\tls\n");
            break;
          case OPER_SUP:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\tgt\n");
            break;
          case OPER_EQ:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\teq\n");
            break;
          case OPER_NE:
            generateAsmExpression(n->t_oper.op[0],fout);
            generateAsmExpression(n->t_oper.op[1],fout);
            fprintf(fout,"\teq\n");
            fprintf(fout,"\tnot\n");
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

  transition=tn;
  while (transition!=NULL)
    {

      // on va parcourir la liste des etapes amont de la transition, qui
      // est construite sous la forme d'une liste de etapeRefNode
      // dont seule la partie name et le pointeur next sont pour l'instant remplis avec
      // des informations

      ern=transition->etapesAmont;
      while (ern!=NULL)
        {
          // on recupere ici le nom de l'etape
          // et on cherche parmi la liste des etapes celle qui
          // correspond au nom

          //ToDO : appel de findEtapeByName, retour stocké dans etape
          etape = findEtapeByName (en, ern->name);

          // si on trouve l'etape, alors cela signifie deux choses
          // 1) que l'on peut
          // affecter le pointeur vers l'etape a l'etapeRefNode en cours
          // 2) que l'on peut ajouter la transition courante a la liste
          // des transitions aval de l'etape que l'on vient d'identifier
          // auquel cas on empile une nouvelle RefTransition dans
          // la liste des transitions aval de l'etape

          if (etape!=NULL)
            {
              ern->etape=etape;
              // ToDo : appel de pushRefTransition 
	      pushRefTransition(&etape->transitionsAval,transition->name);
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
	transition=transition->next;

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
	  trn=trn->next;
        }


      trn=etape->transitionsAval;
      while (trn!=NULL)
        {
 
          // ToDo meme chose que le derner while (3 instructions)
		transition=findTransitionByName(tn,trn->name);

		trn->transition=transition;
		trn=trn->next;
        }

      etape=etape->next;
    }
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
// 13: stable 

// 14: e0...nbEtapes-1.
// 14+nbEtapes: old_e0...
// 14+nbEtapes*2: appel_e0...
// 14+nbEtapes*3: reponse_e0...

void generateCode(etapeNode *en, transitionNode *tn)
{
  transitionNode *transition;
  etapeNode *etape;
  actionNode *an;
  int n,i;

  printf("# 000 : but0\n");
  printf("# 001 : but0'rise\n");
  printf("# 002 : but0'fall\n");
  printf("# 003 : but1\n");
  printf("# 004 : but1'rise\n");
  printf("# 005 : but1'fall\n");
  printf("# 006 : an0\n");
  printf("# 007 : an1\n");
  printf("# 008 : led0\n");
  printf("# 009 : led1\n");
  printf("# 010 : led2\n");
  printf("# 011 : led3\n");
  printf("# 013 : stable \n");

  n=nbEtapes(en);
  etape=en;
  while (etape!=NULL)
    {
      printf("# %3.3d : %s\n",14+etape->id,etape->name);
      etape=etape->next;
    }

  etape=en;
  while (etape!=NULL)
    {
      printf("# %3.3d : old_%s\n",14+n+etape->id,etape->name);
      etape=etape->next;
    }

  etape=en;
  while (etape!=NULL)
    {
      printf("# %3.3d : appel_%s\n",14+2*n+etape->id,etape->name);
      etape=etape->next;
    }

  etape=en;
  while (etape!=NULL)
    {
      printf("# %3.3d : reponse_%s\n",14+3*n+etape->id,etape->name);
      etape=etape->next;
    }

  printf("\tpushi\t0\n");
  //printf("#\tpop dans stable\n");
  printf("\tpop\t13\n");

  etape=en;
  while (etape!=NULL)
    {
      printf("\tpushi\t0\n");
      //printf("#\tpop\tappel_%s\n",etape->name);
      printf("\tpop\t%d\n",14+2*n+etape->id);
      printf("\tpushi\t0\n");
      //printf("#\tpop\treponse_%s\n",etape->name);
      printf("\tpop\t%d\n",14+3*n+etape->id);
		
      etape=etape->next;
    }

  printf("mainloop:\n");
  printf("\tpush\t13\n");
  printf("\tpushi\t0\n");
  printf("\teq\n");
  printf("\tjf\tfinloop\n");

  etape=en;

  /* A completer */

	while (etape!=NULL)
	{
		printf("\tpush\t%d\n",14+etape->id);
		printf("\tpop\t%d\n",14+n+etape->id);
		
		etape=etape->next;
	}

	transition=tn;
	while (transition!=NULL)
	{
		printf ("#test de franchissement de la transition %s\n", transition->name);
		etapeRefNode *ernamont,*ernaval;

		ernamont=transition->etapesAmont;
		while (ernamont!=NULL)
		{
			etape=ernamont->etape;
			printf("\tpush\t%d\n",14+etape->id);
			printf("\tpushi\t1\n");
			printf("\teq\n");
			ernamont=ernamont->next;
		}
		generateAsmExpression(transition->receptivite,stdout);
		printf("\tand\n");
		printf("\tjf\tnext%4.4d\n",compteurLabel);

		ernaval=transition->etapesAval;
		while (ernaval!=NULL)
		{
			etape=ernaval->etape;
			printf("\tpushi\t1\n");
			printf("\tpop\t%d\n",14+2*n+etape->id);
			ernaval=ernaval->next;
		}
			
		ernamont=transition->etapesAmont;
		while (ernamont!=NULL)
		{
			etape=ernamont->etape;
			printf("\tpushi\t1\n");
			printf("\tpop\t%d\n",14+3*n+etape->id);
			ernamont=ernamont->next;
		}
		printf("next%4.4d:\n",compteurLabel);
		compteurLabel++;


		transition=transition->next;
	}

	etape=en;
	while (etape!=NULL)
	{
		printf ("#calcul de la nouvelle valeur de %s\n", etape->name);
		
		printf("\tpush\t%d\n",14+etape->id);

		printf("\tpush\t%d\n",14+3*n+etape->id);
		printf("\tnot\n");
		printf("\tand\n");

		printf("\tpush\t%d\n",14+2*n+etape->id);
		printf("\tor\n");

		printf("\tpop\t%d\n",14+etape->id);
		
		etape=etape->next;
	}

	printf ("#test de stabilite\n");
	etape=en;
	while (etape!=NULL)
	{
		printf("\tpush\t%d\n",14+etape->id);
		printf("\tpush\t%d\n",14+n+etape->id);
		printf("\teq\n");
		
		etape=etape->next;
	}
	n=nbEtapes(en);
	for (i=0;i<n-1;i++)
		printf("\tand\n");
	printf("\tjf\tsuiteloop\n");

	printf("\tpushi\t1\n");
	//printf("#\tpop\tstable\n");
	printf("\tpop\t13\n");

	printf("suiteloop:\n");
	printf("\tj\tmainloop\n");

	printf("finloop:\n");

	printf ("#affectation des sorties\n");
	etape=en;
	while (etape!=NULL)
	{
		printf("\tpush\t%d\n",14+etape->id);
		printf("\tpushi\t1\n");
		printf("\teq\n");
		printf("\tjf\toutput%4.4d\n",compteurEtapes);

		an=etape->actions;
		while (an!=NULL)
		{
			generateAsmExpression(an->expr,stdout);
			if (strncmp(an->name,"led0",4)==0)
			{
				printf("\tpop\t8\n");
			}
			else if (strncmp(an->name,"led1",4)==0)
			{
				printf("\tpop\t9\n");
			}
			else if (strncmp(an->name,"led2",4)==0)
			{
				printf("\tpop\t10\n");
			}
			else if (strncmp(an->name,"led3",4)==0)
			{
				printf("\tpop\t11\n");
			}
			an=an->next;
		}

		printf("output%4.4d:\n",compteurEtapes);

		compteurEtapes++;
		etape=etape->next;
	}
	printf("\thalt\n");
	printf("\tend\n");
 
}
