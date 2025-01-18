
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "asm.h"



int currentInst;
int cuerrentInstructionName;

int main(int argc, char **argv)
{
    //Ouverture du fichier
    //Construction du dictionnaire d'instruction
    //addInstructionName();
    // Parseur phase 1
    printf("bonjour");
    parseAsm("assembleur.txt");
    // Parseur phase 2
   // resolveReferences();
    //Génération du code
    //generateBinary(fout);
    return 0;
}

void parseAsm(char* fichier)
{
	
	int currentLabel=0;
	int i;
	int Type;
	char line[300];

	FILE* f=fopen(fichier,"r");
	char* end = "I_END";
				
				for (i=0;i<300;i++)
				{
					fgets(line,100,f);
					if (strstr(line, end))
					{
						printf (" %d **** %s \n",Type,line);
						for( i=0; i<currentLabel; i++)
						{
							printf("%s 	%d\n",tabLabels[i].label,tabLabels[i].addr);
						}
						return;
					}	
					else if (strstr( line,"#"))
					{
						Type=commentaire;  //0
					}
					else if(strstr( line,":"))
					{
						Type=etiquette; //2
						currentLabel++;	
						addLabel(line,i+1);
					}
					else
					{
						Type=instruction; //1
					}
					printf (" %d **** %s \n",Type,line);							
				}	
	
}


int findLabel(char *labelname)
{
    int i;
   
    for(i=0 ; i < currentLabel ; i++)
    {
        if(strcmp(labelname,tabLabels[i].label)==0)
        {
            return i;
        }
    }
        return 0;
}    




void addLabel(char *labelname, int addr)
{
	int i=0;
	char newNomLabel[strlen(labelname)];
	while(labelname[i] != ':')
	{
		newNomLabel[i]=labelname[i];
		i++;	
	}
	
    tabLabels[currentLabel].label=strdup(newNomLabel);
    tabLabels[currentLabel].addr=addr;
    currentLabel++;
}



/*void decodeInstruction(char *line)
{
	fgets(line,100,fin);
	strstr(line,"end");
} */   
