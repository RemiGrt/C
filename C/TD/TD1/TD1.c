
  // déclaration d'un octet MASK et initialisation en binaire
  byte MASK = B01000001;
  // déclaration d'un octet B et initialisation en binaire
  byte B = B01010101;
  // déclaration d'un octet RESULT et initialisation
  // avec un ET logique (bit á bit) entre B et MASK 
  byte RESULT = B & MASK;
  // A ne pas confondre avec && (ET logique seulement sur LSB) 
  byte RESULTBIT = B && MASK;
  // Affichage de la valeure binaire en console
  Serial.print("AND: RESULT BIT WISE: "),Serial.println(RESULT, BIN);
  Serial.print("AND: RESULT LSB: "),Serial.println(RESULTBIT, BIN);
   
 
  // déclaration d'un octet activeMSB et initialisation en binaire
  byte activeMSB = B10000000;
  // OU logique bit à bit
  RESULT = RESULT | activeMSB;
  Serial.print("OR: RESULT BIT WISE: "),Serial.println(RESULT, BIN);
  // Equivalent à
  RESULT |= activeMSB;
  Serial.print("OR: RESULT BIT WISE: "),Serial.println(RESULT, BIN);
  // A ne pas confondre avec || (OU logique seulement sur LSB) 
  RESULT = B01010100 || B01010101;
  Serial.print("OR: RESULT LSB: "),Serial.println(RESULT, BIN);
  
  byte C8 = B10010001;
  byte D8 = B10001000;
  // XOR bit à bit
  byte RESULT8 = C8 ^ D8;
  // Affichage de la valeure binaire en console
  Serial.print("XOR: RESULT8: "), Serial.println(RESULT8, BIN);
  
  
  byte I = B1000;
  // complément à 1 de I (inversion bit à bit)
  byte BitWiseNotI = ~I;
  // à ne pas confondre avec l'opérateur !, qui inverse juste le LSB
  byte LSBNotI = !I;
  // Affichage de la valeure binaire en console
  Serial.print("NOT: BitWise notI : "),Serial.println(BitWiseNotI, BIN);
  Serial.print("NOT: LSB notI: "),Serial.println(LSBNotI, BIN);
  
  
  RESULT = B00000001;
  Serial.print("INIT RESULT: "),Serial.println(RESULT, BIN);
  for(int i=0; i<8; i++){
    RESULT = RESULT << 1;
    Serial.print("LEFT SHIFT: "),Serial.println(RESULT, BIN);
  }
  
  RESULT = B10000000;
  Serial.print("INIT RESULT: "),Serial.println(RESULT, BIN);
  for(int i=0; i<8; i++){
    RESULT = RESULT >> 1;
    Serial.print("RIGHT SHIFT: "),Serial.println(RESULT, BIN);
  }

Serial.println(PIND,BIN);

Ex1:

int i = 5, j,k,l,m;  	i=5, j=U, k=U, l=U, m=U 
j = i++; 		i=6, j=5, k=U, l=U, m=U
k = ++i; 		i=7, j=5, k=7, l=U, m=U
l = i--; 		i=6, j=5, k=7, l=7, m=U
m = --i + l++; 		i=5, j=5, k=7, l=8, m=12



Ex2:
int a=2,b=3,c=5; 
int x = ((c++ >= a) < (b % c)) + (c>a);
            (1        <    3)  + 1
x=2


Ex3:
• Diviser (en entier) x par 256
x >> 8 
• Trouver la valeur du bit no i de x 
(x >> i) & 1
• Mettre `a 0 les bits{1,4,5}de x et mettre `a 1 ses bits{0,2}
x = x & 001101 => x &= 0xCD
x = x | 000101 => x |= 0x05
• Mettre `a 1 le bit no i de x
x | 2powi
x |= 1 << i
• Mettre `a 0 le bit no i de x
x &= ~(1 << i) 
• Indiquer si les bits 4 et 6 de x et de y sont ´egaux
 x & 0x50 == y & 0x50 
• Indiquer si au moins un des bits 1, 4 et 6 de x et de y sont ´egaux
(x ^ y) & 0x52 


Ex4:
Max (a>b)?a:b
Min (a<b)?a:b) 
Abs (a>0)?a:-a)

Ex5:
int a=1; 	a=1
a *= a++; 	a=2 
a <<= 2;  	a=8
a |= 36; 	a= 001000 | 100100 = 101100 = 44
a %= a++ - 8; 	a%=(44-8)++ => a=(44%36)++ => 8++ => 9

int a=2; 	a=2
a *= a++; 	a=5 
a <<= 2;  	a=20
a |= 36; 	a=010100 | 100100 = 110100=52
a %= a++ - 8; 	a%=(52-8)++ => a%=(44)++ => 8++ => 9

Ex6:
if x==12 y=1
else if x==4 y=2
else if x==5 y=3
else if x==42 y=4
else if x==8 y=5
else y=0

switch (x){
	case 12: y=1; break;
	case 4: y=2; break;
	case 42: y=3; break;
	default: y=0;


switch (x){
	case 12: y=1; break;
	case 4: y=2; break;
	case 42: y=3; break;
	default: y=0;







