#include "ast.h"

// Cette variable permet de declarer des etiquettes a la volee

nodeType *createNumericNode(int v)
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

nodeType *createIdentifierNode(char *id)
{
        nodeType *p;

        if ((p=malloc(sizeof(nodeType))) == NULL)
        {
                printf("out of memory error\n");
                exit(1);
        }

        p->type=typeIdentifier;
        p->t_identifier.ident=strdup(id);
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
				fprintf(fout,"\tpush\t%s\n",n->t_identifier.ident);
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

	fout=fopen(filename,"w");
	generateAsmExpression(n,fout);
	fprintf(fout,"\thalt\n");
	fprintf(fout,"\tend\n");
	fclose(fout);	
}
