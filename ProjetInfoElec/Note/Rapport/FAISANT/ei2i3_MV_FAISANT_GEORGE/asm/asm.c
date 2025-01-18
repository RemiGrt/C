
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asm.h"



#define out_add() out[pOUT] = malloc(100) //allocation de la case
#define MAX_INSTRUCTION (1000)

int codeCommande(char *mnem);
/*!
*
*/
int main(int argc, char *argv[])
{
    FILE *fid,*fid2;
    //Fichiers
    if (argc < 2)
    {
        return -1;
    }
    else
    {
        fid = fopen(argv[2], "w");
        fid2 = fopen(argv[1], "r");
    }
    char nasm[100] = {0}, s[100] = {0};
    int nLine = 0;
    int n;          //Argument commande
    char argJ[100]; //Argument Jump ou JumpFalse
    char c;
    char *line;
    /**
* label
*/
    char *label[100];
    int lineLabel[100] = {0};
    int pLabel = 0;
    char mnemonic[100];
    char *out[MAX_INSTRUCTION];
    int pOUT = 0;
    int i, j; // Incrément pour la boucle d'écriture dans le fichier fid3
    //fscanf(fid2,"%s",nasm);
    while (1)
    {
        c = getc(fid2);
        if (c == EOF)
            break;
        if (c == '\t')
        {
            fscanf(fid2, "%s", mnemonic);

            if (nArg(mnemonic) > 0)
            {
                //Jump ou JumpFalse : l'argument est un char
                if (nArg(mnemonic) == 2)
                {
                    fscanf(fid2, "%s", argJ);
                    out_add();
                    sprintf(out[pOUT++], "%d:%d\n", nLine, codeCommande(mnemonic));
                    out_add();
                    sprintf(out[pOUT++], "%d:%s:\n", ++nLine, argJ); //add : -> end label
                }
                //Autres instructions : l'argument est un int
                else
                {
                    fscanf(fid2, "%d", &n);
                    out_add();
                    sprintf(out[pOUT++], "%d:%d\n", nLine, codeCommande(mnemonic));
                    out_add();
                    sprintf(out[pOUT++], "%d:%d\n", ++nLine, n);
                }
            }
            else if (nArg(mnemonic) == 0)
            {
                out_add();
                sprintf(out[pOUT++], "%d:%d\n", nLine, codeCommande(mnemonic));
            }
            else if (nArg(mnemonic) == -2)
            {
                out_add();
                sprintf(out[pOUT++], "fin\n");
            }
            else
            {
                out_add();
                sprintf(out[pOUT++], "commande introuvable\n");
            }
            getc(fid2);
            nLine++;
        }
        else if (c == '#')
        {
            while (getc(fid2) != '\n')
                ;
        }
        else if (!c == 0)
        {
            label[pLabel] = malloc(100);
            label[pLabel][0] = c;
            fscanf(fid2, "%s", (label[pLabel] + 1));
            lineLabel[pLabel] = nLine;
            pLabel++;
            getc(fid2);
        }
    }
    //fprintf(fid,"%d\n%s",n,out);
    fclose(fid);
    fclose(fid2);

    FILE *fid3 = fopen(argv[2], "w");
    if (fid3 == NULL)
    {
        printf("erreur fid\n");
        return 0;
    }
    char addr[100] = {0};
    for (j = 0; j < pLabel; j++)
    {
        for (i = 0; i < nLine; i++)
        {
            if (strstr(out[i], label[j]))
            {
                sprintf(addr, "%d\n", lineLabel[j]);
                strcpy(strchr(out[i], ':') + 1, addr);
                break;
            }
        }
    }
    fprintf(fid3, "%d\n", nLine);
    for (i = 0; i < nLine; i++)
    {
        fprintf(fid3, "%s", out[i]);
    }
    //fprintf(fid,"%d\n%s",n,out);
    fclose(fid3);

    return 0;
}

int nArg(char *mnem)
{
    int i;
    for (i = 0; i < NUM_CMD; i++)
    {
        if (!strcmp(mnem, commande[i]))
            return argument[i];
    }
    return -1;
}

int codeCommande(char *mnem)
{
    int i;
    for (i = 0; i < NUM_CMD; i++)
    {
        if (!strcmp(mnem, commande[i]))
            return numCommande[i];
    }
    return -1;
}
