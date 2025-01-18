void addCode(int v);
void addInstuctionName(char*instname, int opcod, int type,char*format,int nbops);
int findLabel(char*labelname);
void addLabel(char *labelname,int addr);
void addReference(char*labelname,int addrInCode);
void resolveReferences();
void decodeInstruction(char*line);
int parseAsm(FILE*fin);
void printLabels();
void dumpBinaryCode();
void generateBinary(FILE*fout);


