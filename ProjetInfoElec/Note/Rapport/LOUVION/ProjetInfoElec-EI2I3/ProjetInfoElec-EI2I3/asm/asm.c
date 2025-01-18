
#include "asm.h"


int currentLabel=0;
int currentInst=0;
int currentRef=0;
unsigned int codeSegment[100000000];
int addrCodeSeg =0;
int z = 0;
int x = 0;




void parseAsm(FILE *fin)
{
	printf("rentré fct parseAsm\n");
	
	char line[100];
	
	fgets(line,100,fin);
	
	while(strstr(line,"end") == NULL)
 	{
			if(strchr(line,'#') != NULL)
			{
				
				//printf("on a un commentaire\n");
			}
			else if(strchr(line,':') != NULL)
			{
				printf("on a un caractère aaa :\n");
				addLabel(line,addrCodeSeg);
				
				
			}
			else
			{
				//printf("on a une instruction\n");
				decodeInstruction(line);
				
			}
		
		fgets(line,100,fin);
	}
}

void addLabel(char *line, int addrCodeSeg)
{
	char *label_name;
	label_name = malloc(20);
	sscanf(line,"%[a-zA-Z0-9]s",label_name);
	printf("le label : %s\n",label_name);
	tabLabels[currentLabel].addr = addrCodeSeg;
	tabLabels[currentLabel].label = strdup(label_name);
	currentLabel++;
	printf("label name: %s\n", tabLabels[0].label);
	printf("label addr: %d\n", tabLabels[0].addr);
	printf("label name: %s\n", tabLabels[1].label);
	printf("label addr: %d\n", tabLabels[1].addr);
	printf("label name: %s\n", tabLabels[2].label);
	printf("label addr: %d\n", tabLabels[2].addr);
	printf("label name: %s\n", tabLabels[3].label);
	printf("label addr: %d\n", tabLabels[3].addr);
	printf("current label : %d\n",currentLabel);
	free(label_name);
}

void decodeInstruction(char *line)
{
	int i,j;
	int l = 0;
	int type;
	int entier;
	
	char *insT;
	insT = malloc(20);
	char *lab_ref;
	lab_ref = malloc(20);
	sscanf(line,"%s",insT);
	
	printf("a : %s\n", insT);
	for(i=0;i<z;i++)
	{
		
		if(strcmp(insT,tabInstructionNames[i].name)==0)
		{
			type = tabInstructionNames[i].type;
			//printf("type : %d\n", type);
			switch(type)
			{
				case 0:
				printf("type : %d\n", type);
					codeSegment[addrCodeSeg] = tabInstructionNames[i].opcode;
					printf("codeSegment[%d] = %d\n",addrCodeSeg,codeSegment[addrCodeSeg]);
					addrCodeSeg++;
				break;
				
				case 1:
				printf("type : %d\n", type);
					sscanf(line,"%s%d",insT,&entier);
					codeSegment[addrCodeSeg] = tabInstructionNames[i].opcode;
					printf("codeSegment[%d] = %d\n",addrCodeSeg,codeSegment[addrCodeSeg]);
					addrCodeSeg++;
					codeSegment[addrCodeSeg] = entier;
					printf("codeSegment[%d] = %d\n",addrCodeSeg,codeSegment[addrCodeSeg]);
					addrCodeSeg++;
				break;
				
				case 3:
				printf("type : %d\n", type);
					sscanf(line,"%s%s",insT,lab_ref);
					printf("l'instruction : %s\n",insT);
					printf("la reference %s\n",lab_ref);
					for(j=0;j<currentLabel;j++)
					{
						printf("dans le premier premier if du case 3\n");
						if(strcmp(lab_ref,tabLabels[j].label) == 0) 
						{
						//printf("dans le premier if du case 3\n");
							printf("dans le if case 3\n");
							codeSegment[addrCodeSeg] = tabInstructionNames[i].opcode;
							printf("codeSegment[%d] = %d\n",addrCodeSeg,codeSegment[addrCodeSeg]);
							addrCodeSeg++;
							codeSegment[addrCodeSeg] = tabLabels[j].addr;
							printf("codeSegment[%d] = %d\n",addrCodeSeg,codeSegment[addrCodeSeg]);
							addrCodeSeg++;
							break;
						}
						else  //si le label du jump lu est pas un existant je crée la ref
						{
							printf("dans le else case 3\n");
							codeSegment[addrCodeSeg] = tabInstructionNames[i].opcode;
							printf("codeSegment[%d] = %d\n",addrCodeSeg,codeSegment[addrCodeSeg]);
							addrCodeSeg++; 
							
							codeSegment[addrCodeSeg] = -1;
							
							tabReferences[currentRef].label = lab_ref;
							tabReferences[currentRef].addrInCode = addrCodeSeg;
							
							printf("codeSegment[%d] = %d\n",addrCodeSeg,codeSegment[addrCodeSeg]);
							addrCodeSeg++;
							
							currentRef++;
							printf("tabref name : %s\n",tabReferences[0].label);
							printf("tabref addr : %d\n",tabReferences[0].addrInCode);
							printf("current ref : %d\n",currentRef);
							break;
						}
					}
				break;
				default:
				printf("pas de type définie"); 
				break;
			}
		}
	}
	free(insT);
	free(lab_ref);
}

void resolveReference()
{
	int w,s;
	
	for(w=0;w<currentRef;w++)
	{
		printf("on rentre premier for resolveref\n");
		for(s=0;s<currentLabel;s++)
		{
		printf("on rentre deuxième for resolveref\n");	
			if(strcmp(tabReferences[w].label,tabLabels[s].label) == 0)
			{
				printf("on rentre dans le if resolveRef");
				codeSegment[tabReferences[w].addrInCode] = tabLabels[s].addr;
				printf("on a resolu une ref\n");
			}
		}
	}
}

void generateBinary(FILE *fout)
{
	
	int t;
	printf("nb instru %d\n",addrCodeSeg);
	fprintf(fout,"%d\n",addrCodeSeg);
	for(t=0;t<addrCodeSeg;t++)
	{
		fprintf(fout,"%d:%d\n",t,codeSegment[t]);
	}
}

void addInstructionName(char *name, int opcode, int type, char *format, int nbops)
{
	tabInstructionNames[z].name = name;
	tabInstructionNames[z].opcode = opcode;
	tabInstructionNames[z].type = type;
	tabInstructionNames[z].format = format;
	tabInstructionNames[z].nbops = nbops;
	z++;
} 

int main(int argc, char **argv)
{
	addInstructionName("add", I_ADD, 0, "", 0);
	//addInstructionName("sub", I_SUB, 0, "", 0);
	addInstructionName("mult", I_MULT, 0, "", 0);
	addInstructionName("div", I_DIV, 0, "", 0);
	addInstructionName("neg", I_NEG, 0, "", 0);
	addInstructionName("and", I_AND, 0, "", 0);
	addInstructionName("or", I_OR, 0, "", 0);
	addInstructionName("not", I_NOT, 0, "", 0);
	addInstructionName("eq", I_EQ, 0, "", 0);
	addInstructionName("ls", I_LS, 0, "", 0);
	addInstructionName("gt", I_GT, 0, "", 0);
	addInstructionName("halt", I_HALT, 0, "", 0);
	
	addInstructionName("push", I_PUSH, 1, "%s %d", 1);
	addInstructionName("pop", I_POP, 1, "%s %d", 1);
	addInstructionName("pushi", I_PUSHI, 1, "%s %d", 1);
	
	addInstructionName("j", I_J, 3, "%s %s", 1);
	addInstructionName("jf", I_JF, 3, "%s %s", 1);


	FILE *fichier;
	fichier = fopen(argv[1],"r");
	parseAsm(fichier);
	
	/*printf("addr : %d\n", tabLabels[0].addr);
	printf("label : %s\n", tabLabels[0].label);
	
	printf("name : %s\n", tabInstructionNames[4].name);
	printf("opcode : %d\n", tabInstructionNames[4].opcode);
	printf("type : %d\n", tabInstructionNames[4].type);
	printf("format : %s\n", tabInstructionNames[4].format);
	printf("nbops : %d\n", tabInstructionNames[4].nbops);*/
	
	
	int g;
	
	for(g=0;g<addrCodeSeg;g++)
	{
		printf("codeSegment[%d] : %d\n",g,codeSegment[g]);
	}
	
	printf("resolve ref\n");
	resolveReference();
	
	int v;
	
	for(v=0;v<addrCodeSeg;v++)
	{
		printf("codeSegment[%d] : %d\n",v,codeSegment[v]);
	}
	
	int q;
	
	for(q=0;q<currentLabel;q++)
	{
		printf("label : %s\n",tabLabels[q].label);
		printf("addr : %d\n",tabLabels[q].addr);
	}
	
	int n;
	
	for(n=0;n<currentRef;n++)
	{
		printf("ref : %s\n",tabReferences[n].label);
		printf("addr : %d\n",tabReferences[n].addrInCode);
	}
	
	
	
	FILE *fout=fopen(argv[2],"w");
	if (fout==NULL)
		printf("Error opening write file %s\n",argv[2]);
	generateBinary(fout);
	fclose(fout);
	
	
}
