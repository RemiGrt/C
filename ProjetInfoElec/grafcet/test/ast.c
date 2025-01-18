#include "ast.h"
//#include "symboles.h"

// Cette variable globale vaut au depart 0, et est incrementee a chaque fois
int countDigraph;

// Cette variable permet de declarer des etiquettes a la volee
int currentLabel;

listeEtapeElement *le;
listeTransitionElement *lt;
int compteurStep=0;
int compteurTransition=0;

etape *etapeStack[20];
int spEtapeStack=0;

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

void printEtapes()
{
        listeEtapeElement *ee;
	listeTransitionElement *te;
	

        ee=le;
        while (ee!=NULL)
        {
                printf("%s %d (%d)\n",ee->e->nom, ee->e->ident, ee->e->active);
                printf("\tAmont\n");
                te=ee->e->transitionsAmont;
                while (te!=NULL)
                {
                        printf("\t\t%s %d\n",te->t->nom, te->t->ident);
                        te=te->next;
                }
                printf("\tAval\n");
                te=ee->e->transitionsAval;
                while (te!=NULL)
                {
                        printf("\t\t%s %d\n",te->t->nom, te->t->ident);
                        te=te->next;
                }
                printf("\tCode des actions\n");
		generateAsmRec(ee->e->actionNode, stdout);
		
                ee=ee->next;
        }
}

void printTransitions()
{
        listeEtapeElement *ee;
        listeTransitionElement *te;

        te=lt;
        while (te!=NULL)
        {
                printf("%s %d\n",te->t->nom, te->t->ident);
                printf("\tAmont\n");
                ee=te->t->etapesAmont;
                while (ee!=NULL)
                {
                        printf("\t\t%s %d\n",ee->e->nom,ee->e->ident);
                        ee=ee->next;
                }
                printf("\tAval\n");
                ee=te->t->etapesAval;
                while (ee!=NULL)
                {
                        printf("\t\t%s %d\n",ee->e->nom,ee->e->ident);
                        ee=ee->next;
                }
		printf("\tCode de transition\n");
		generateAsmExpression(te->t->receptiviteNode, stdout);
                te=te->next;
        }
}

void emptyStack()
{
	spEtapeStack=0;
}

void pushStack(etape *e)
{
	etapeStack[spEtapeStack++]=e;
}

etape *popStack()
{
	if (spEtapeStack==0)
		return NULL;
	else
		return etapeStack[--spEtapeStack];
}

etape *trouverEtape(char *nom)
{
        listeEtapeElement *ee;

        ee=le;
        while (ee!=NULL)
        {
		if (strcmp(ee->e->nom,nom)==0)
                	return ee->e;
		ee=ee->next;
	}

	return NULL;
}

transition *trouverTransition(char *nom)
{
        listeTransitionElement *te;

        te=lt;
        while (te!=NULL)
        {
		if (strcmp(te->t->nom,nom)==0)
                	return te->t;
		te=te->next;
	}

	return NULL;
}

void generateAsmRec(nodeType *n, FILE *fout)
{
	int label1, label2;

	if (n==NULL)
		return;

	switch (n->type)
	{
		case typeOperator:
			{
				switch (n->t_oper.oper)
				{
					case OPER_ASSIGN:
                                                {
                                                        nodeType *n0=n->t_oper.op[0];
                                                        int index;
                                                       	generateAsmExpression(n->t_oper.op[1],fout);
                                                        fprintf(fout,"\tpop\t%s (%d)\n",n0->t_identifier.ident, n0->t_identifier.key);
                                                }
						break;
					case OPER_SEQUENCE:
						generateAsmRec(n->t_oper.op[0],fout);
						generateAsmRec(n->t_oper.op[1],fout);
						break;
					case OPER_STEP:
						{
						// Creer une etape
						etape *pe=(etape*)malloc(sizeof(etape));
						pe->nom=n->t_oper.op[0]->t_identifier.ident;
						pe->active=n->t_oper.op[2]->t_numeric.valeur;
						pe->actionNode=n->t_oper.op[1];
						pe->transitionsAmont=NULL;
						pe->transitionsAval=NULL;
						pe->ident=compteurStep++;

						// Ajouter l'etape a la liste des etapes
        					listeEtapeElement *ee=(listeEtapeElement*)malloc(sizeof(listeEtapeElement));
        					ee->e=pe;
        					ee->next=le;
        					le=ee;

						//fprintf(fout,"step_%s:\n",n->t_oper.op[0]->t_identifier.ident);
						//generateAsmRec(n->t_oper.op[1],fout);
						//fprintf(fout,"\thalt\n");
						}
						break;
					case OPER_TRANSITION:
						{
						// Creer une transition
        					transition *pt=(transition*)malloc(sizeof(transition));
        					pt->nom=n->t_oper.op[0]->t_identifier.ident;
        					pt->active=0;
						pt->receptiviteNode=n->t_oper.op[3];
        					pt->etapesAmont=NULL;
        					pt->etapesAval=NULL;
						pt->ident=compteurTransition++;

						// Ajouter la transition a la liste des transitions
        					listeTransitionElement *te=(listeTransitionElement*)malloc(sizeof(listeTransitionElement));
        					te->t=pt;
        					te->next=lt;
        					lt=te;

						// Construit la liste des etapes Amont a ajouter a la transition
						// Des qu'on a trouve une des etapes Amont d'une transition
						// on ajoute la transition dans les transitions Aval de cette etape
						//fprintf(fout,"transition %s:\n",n->t_oper.op[0]->t_identifier.ident);
						//fprintf(fout,"transition etapes amont\n");
						emptyStack();
						generateAsmRec(n->t_oper.op[1],fout);
						//printf("-- Amont ----\n");
						etape *pe=popStack();
						while (pe!=NULL)
						{
							//printf("--> %s\n",pe->nom);

        						listeEtapeElement *ee=(listeEtapeElement*)malloc(sizeof(listeEtapeElement));
        						ee->e=pe;
        						ee->next=pt->etapesAmont;
        						pt->etapesAmont=ee;

							listeTransitionElement *te=(listeTransitionElement*)malloc(sizeof(listeTransitionElement));
							te->t=pt;
							te->next=ee->e->transitionsAval;
							ee->e->transitionsAval=te;

							pe=popStack();
						}

						// Construit la liste des etapes Aval a ajouter a la transition
						// Des qu'on a trouve une des etapes Aval d'une transition
						// on ajoute la transition dans les transitions Amont de cette etape
						//fprintf(fout,"transition etapes aval\n");
						emptyStack();
						generateAsmRec(n->t_oper.op[2],fout);
						//printf("-- Aval -----\n");
						pe=popStack();
						while (pe!=NULL)
						{
							//printf("--> %s\n",pe->nom);

        						listeEtapeElement *ee=(listeEtapeElement*)malloc(sizeof(listeEtapeElement));
        						ee->e=pe;
        						ee->next=pt->etapesAval;
        						pt->etapesAval=ee;

							listeTransitionElement *te=(listeTransitionElement*)malloc(sizeof(listeTransitionElement));
							te->t=pt;
							te->next=ee->e->transitionsAmont;
							ee->e->transitionsAmont=te;

							pe=popStack();
						}

						//fprintf(fout,"transition receptivite\n");
						//generateAsmExpression(n->t_oper.op[3],fout);
						}
						break;
					default:
						break;
				}
			}
			break;
		case typeNumeric:
			break;
		case typeIdentifier:
			pushStack(trouverEtape(n->t_identifier.ident));
			break;
	}
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
				fprintf(fout,"\tpush\t%s (%d,%d)\n",n->t_identifier.ident, n->t_identifier.key,n->t_identifier.flag);
/*
                                int index;
                                int result=est_symbole(n->t_identifier.ident,&index);

				switch(table_symb[index].genre)
				{
					case GENRE_VARIABLE_GLOBALE:
                                		fprintf(fout,"\tpush\t%d\n", table_symb[index].t_variable.adrv);
                                		fprintf(fout,"\tcopy\t1\n");
						break;
					case GENRE_VARIABLE_LOCALE:
                                		fprintf(fout,"\tlibp\t%d\n", table_symb[index].t_variable.adrv);
                                		fprintf(fout,"\tcopy\t1\n");
						break;
					case GENRE_PARAMETRE:
						{
						int indfonc=table_symb[index].t_param.fonc;
						printf ("nbFormels=%d nbLocales=%d\n",table_symb[indfonc].t_fonction.nbFormels,table_symb[indfonc].t_fonction.nbLocales) ;
                                		fprintf(fout,"\tlibp\t%d\n", table_symb[index].t_param.adrp-1-table_symb[indfonc].t_fonction.nbFormels);
                                		fprintf(fout,"\tcopy\t1\n");
						}
						break;
				}
*/
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

void generateAsm(nodeType *n, char *filename)
{
	FILE *fout;

	currentLabel=0;
	fout=fopen(filename,"w");
	generateAsmRec(n,fout);
	fprintf(fout,"\thalt\n");
	fprintf(fout,"\tend\n");
	fclose(fout);	
}

void generateDigraphNameNode(nodeType *n,FILE *fout)
{
/*
        if (n==NULL)
                return;

        switch (n->type)
        {
                case typeNumeric:
                        {
				n->digraphNode=countDigraph++;
                                fprintf(fout,"\tA%3.3d [label=\"%f\"]\n",n->digraphNode,n->t_numeric.valeur);
                        }
                        break;
                case typeIdentifier:
                        {
				n->digraphNode=countDigraph++;
                                fprintf(fout,"\tA%3.3d [label=\"%s\"]\n",n->digraphNode,n->t_identifier.ident);
                        }
                        break;
                case typeOperator:
                        {
                                switch (n->t_oper.oper)
                                {
                                        case OPER_APPEL_FONCTION:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tA%3.3d [label=\"appel fonc\"]\n",n->digraphNode);
                                                break;
                                        case OPER_ADD:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tA%3.3d [label=\"+\"]\n",n->digraphNode);
                                                break;
                                        case OPER_SUB:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tA%3.3d [label=\"-\"]\n",n->digraphNode);
                                                break;
                                        case OPER_MULT:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tA%3.3d [label=\"*\"]\n",n->digraphNode);
                                                break;
                                        case OPER_DIV:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tA%3.3d [label=\"/\"]\n",n->digraphNode);
                                                break;
                                        case OPER_INF:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tA%3.3d [label=\"<\"]\n",n->digraphNode);
                                                break;
                                        case OPER_SUP:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tA%3.3d [label=\">\"]\n",n->digraphNode);
                                                break;
                                        case OPER_EQ:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tA%3.3d [label=\"==\"]\n",n->digraphNode);
                                                break;
                                        case OPER_NE:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tA%3.3d [label=\"!=\"]\n",n->digraphNode);
                                                break;
                                        case OPER_NOT:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tA%3.3d [label=\"not\"]\n",n->digraphNode);
                                                break;
                                        case OPER_SKIP:
						n->digraphNode=countDigraph++;
                                		fprintf(fout,"\tA%3.3d [label=\"skip\"]\n",n->digraphNode);
                                                break;
                                        case OPER_RETURN:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
						n->digraphNode=countDigraph++;
                                		fprintf(fout,"\tA%3.3d [label=\"return\"]\n",n->digraphNode);
                                                break;
                                        case OPER_WRITE:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
						n->digraphNode=countDigraph++;
                                		fprintf(fout,"\tA%3.3d [label=\"write\"]\n",n->digraphNode);
                                                break;
                                        case OPER_DEF_FONCTION:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
						n->digraphNode=countDigraph++;
                                		fprintf(fout,"\tA%3.3d [label=\"def_fonction\"]\n",n->digraphNode);
                                                break;
                                        case OPER_ASSIGN:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
						n->digraphNode=countDigraph++;
                                		fprintf(fout,"\tA%3.3d [label=\"=\"]\n",n->digraphNode);
                                                break;
                                        case OPER_WHILE:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
						n->digraphNode=countDigraph++;
                                		fprintf(fout,"\tA%3.3d [label=\"while\"]\n",n->digraphNode);
                                                break;
                                        case OPER_IF:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
						if (n->t_oper.nOperands==3)
                                                	generateDigraphNameNode(n->t_oper.op[2],fout);
						n->digraphNode=countDigraph++;
                                		fprintf(fout,"\tA%3.3d [label=\"if\"]\n",n->digraphNode);
                                                break;
                                        case OPER_SEQUENCE:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
						n->digraphNode=countDigraph++;
                                		fprintf(fout,"\tA%3.3d [label=\";\"]\n",n->digraphNode);
                                                break;
                                        case OPER_RESERVE_SPACE:
						n->digraphNode=countDigraph++;
                                		fprintf(fout,"\tA%3.3d [label=\"reserve_space\"]\n",n->digraphNode);
                                                break;
                                        case OPER_MAIN:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
						n->digraphNode=countDigraph++;
                                		fprintf(fout,"\tA%3.3d [label=\"main\"]\n",n->digraphNode);
                                                break;
                                        default:
                                                break;
                                }
                        }
                        break;
        }
*/
}

void generateDigraphEdges(nodeType *n,FILE *fout)
{
/*
        if (n==NULL)
                return;

        switch (n->type)
        {
                case typeNumeric:
                case typeIdentifier:
                        break;
                case typeOperator:
                        {
				//printf("oper=%d\n",n->t_oper.oper);
                                switch (n->t_oper.oper)
                                {
                                        case OPER_ADD:
                                        case OPER_SUB:
                                        case OPER_MULT:
                                        case OPER_DIV:
                                        case OPER_INF:
                                        case OPER_SUP:
                                        case OPER_EQ:
                                        case OPER_NE:
                                        case OPER_WHILE:
                                        case OPER_APPEL_FONCTION:
                                        case OPER_DEF_FONCTION:
                                        case OPER_ASSIGN:
                                        case OPER_SEQUENCE:
                                        case OPER_RETURN:
                                                fprintf(fout,"\tA%3.3d -> A%3.3d\n", n->digraphNode,n->t_oper.op[0]->digraphNode);
                                                fprintf(fout,"\tA%3.3d -> A%3.3d\n", n->digraphNode,n->t_oper.op[1]->digraphNode);
                                                generateDigraphEdges(n->t_oper.op[0],fout);
                                                generateDigraphEdges(n->t_oper.op[1],fout);
                                                break;
                                        case OPER_IF:
                                                fprintf(fout,"\tA%3.3d -> A%3.3d\n", n->digraphNode,n->t_oper.op[0]->digraphNode);
                                                fprintf(fout,"\tA%3.3d -> A%3.3d\n", n->digraphNode,n->t_oper.op[1]->digraphNode);
						if (n->t_oper.nOperands==3)
                                                	fprintf(fout,"\tA%3.3d -> A%3.3d\n", n->digraphNode,n->t_oper.op[2]->digraphNode);
                                                generateDigraphEdges(n->t_oper.op[0],fout);
                                                generateDigraphEdges(n->t_oper.op[1],fout);
						if (n->t_oper.nOperands==3)
                                                	generateDigraphEdges(n->t_oper.op[2],fout);
                                                break;
                                        case OPER_WRITE:
                                        case OPER_NOT:
					case OPER_MAIN:
                                                fprintf(fout,"\tA%3.3d -> A%3.3d\n", n->digraphNode,n->t_oper.op[0]->digraphNode);
                                                generateDigraphEdges(n->t_oper.op[0],fout);
                                                break;
					case OPER_SKIP:
					case OPER_RESERVE_SPACE:
						break;
                                        default:
                                                break;
                                }
                        }
                        break;
        }
*/
}

void generateDigraph(nodeType *n)
{
	FILE *fout;

	fout=fopen("res.dot","w");
	countDigraph=0;
	fprintf(fout,"digraph {\n");
	printf("generateDigraphNameNode\n");
	generateDigraphNameNode(n,fout);
	printf("generateDigraphEdges\n");
	generateDigraphEdges(n,fout);
	fprintf(fout,"}\n");
	fclose(fout);
	system("dot -Tpng res.dot -o res.png");
}

int findIdent(char *s)
{
	return 0;
}

int addEtape(char *s)
{
	return 0;
}

void grafcet_interpreter()
{
	char buf[256];
	int but0,but1,an0,an1,oldbut0,oldbut1,risebut0,risebut1,fallbut0,fallbut1;
	oldbut0=0;
	oldbut1=0;

	while (1)
	{
		readSerial(buf,0);
		sscanf(buf,"%d:%d:%d:%d",&but0,&but1,&an0,&an1);
		if ((oldbut0==0) && (but0==1))
			risebut0=1;
		else
			risebut0=0;
		if ((oldbut1==0) && (but1==1))
			risebut1=1;
		else
			risebut1=0;

		if ((oldbut0==1) && (but0==0))
			fallbut0=1;
		else
			fallbut0=0;
		if ((oldbut1==1) && (but1==0))
			fallbut1=1;
		else
			fallbut1=0;

		//printf("but0=%d but1=%d an0=%d an1=%d\n",but0,but1,an0,an1);
		if (risebut0)
			printf("risebut0\n");
		if (risebut1)
			printf("risebut1\n");
		if (fallbut0)
			printf("fallbut0\n");
		if (fallbut1)
			printf("fallbut1\n");
		oldbut0=but0;
		oldbut1=but1;
	}
}
