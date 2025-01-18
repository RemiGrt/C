#/********************************************************************************
#|   Nom fichier : assembleur.asm
#|   auteurs: BIDANEL Matthieu FRIAA Chiheb
#|   
#|   Descriptions : Grafcet du coffre fort réalisé avec langage de la VM
#|   
#|   Commentaires : 
#|
#********************************************************************************/

stable => var[0]
X0 => var[1]
Old_X0 => var[2]
Appel_X0 => var[3]
Reponse_X0 => var[4]
X1 => var[5]
Old_X1 => var[6]
Appel_X1 => var[27]
Reponse_X1 => var[7]
X2 => var[8]
Old_X2 => var[9]
Appel_X2 => var[10]
Reponse_X2 => var[11]
X3 => var[12]
Old_X3 => var[13]
Appel_X3 => var[14]
Reponse_X3 => var[15]
an0 => var[16]
but0 => var[17]
but1 => var[18]
old_but0 => var[19]
old_but1 => var[20]
rise_but0 => var[21]
rise_but1 => var[22]
T0 => var[23]
T1 => var[24]
T2 => var[25]
T3 => var[26]
#Appel_X1 => var[27] voir ligne 8



While1:
#Boucle while(1)

	PUSH 17
	POP 19
	PUSH 18
	POP 20
	#old_butX = butX

	PUSH 19
	PUSHI 0
	EQ
	PUSH 17
	PUSHI 1if((X0 == Old_X0) && (X1 == Old_X1) && (X2 == Old_X2) && (X3 == Old_X3)){
				stable = 1;
			}
	EQ
	AND
	JF jf1
	PUSHI 1
	POP 21
	J j1
jf1: 
	PUSHI 0
	POP 21
j1:
	PUSH 20
	PUSHI 0
	EQ
	PUSH 18
	PUSHI 1
	EQ
	AND
	JF jf2
	PUSHI 1
	POP 22
	J j2
jf2:
	PUSHI 0
	POP 22
j2: 
	PUSHI 0
	POP 0
	PUSHI 0
	PUSH 0
	EQ
	#rise_butX = 0 ou 1
	
	JF NoWhile
WhileInstable: 
#Boucle while(stable == 0)

	PUSHI 0
	POP 3
	PUSHI 0
	POP 4

	PUSHI 0
	POP 27
	PUSHI 0
	POP 7
	PUSHI 0
	POP 10
	PUSHI 0
	POP 11
	PUSHI 0
	POP 14
	PUSHI 0
	POP 15
	#Appel_XX = 0
	#Reponse_XX = 0

	PUSH 21
	PUSHI 1
	EQ
	PUSH 16
	PUSHI 128
	LS
	AND
	POP 23

	PUSH 21
	PUSHI 1
	EQ
	PUSH 16
	PUSHI 128
	GT
	AND
	POP 24

	PUSH 21
	PUSHI 1
	EQ
	PUSH 16
	PUSHI 128
	LS
	AND
	POP 25

	PUSH 22
	PUSHI 1
	EQ
	POP 26
	#TX = (rise_butX == 1 && ...

	PUSH 1
	POP 2
	PUSH 5
	POP 6
	PUSH 8
	POP 9
	PUSH 12
	POP 13
	#Old_XX = XX

	PUSH 1
	PUSHI 1
	EQ
	PUSH 23
	PUSHI 1
	EQ
	AND
	JF j3
	PUSHI 1
	POP 27
	PUSHI 1
	POP 4
j3:
	PUSH 5
	PUSHI 1
	EQ
	PUSH 24
	PUSHI 1
	EQ
	AND
	JF j4
	PUSHI 1
	POP 10
	PUSHI 1
	POP 7
j4:
	PUSH 8
	PUSHI 1
	EQ
	PUSH 25
	PUSHI 1
	EQ
	AND
	JF j5
	PUSHI 1
	POP 14
	PUSHI 1
	POP 11
j5:
	PUSH 12
	PUSHI 1
	EQ
	PUSH 26
	PUSHI 1
	EQ
	AND
	JF j6
	PUSHI 1
	POP 3
	PUSHI 1
	POP 15
	#if(XX == 1 && TW = 1) Appel_XX = 1 Reponse_XX-1 = 0

j6:
	PUSH 4
	NOT
	PUSH 1
	AND
	PUSH 3
	OR
	POP 1

	PUSH 7
	NOT
	PUSH 5
	AND
	PUSH 27
	OR
	POP 5

	PUSH 11
	NOT
	PUSH 8
	AND
	PUSH 10
	OR
	POP 8

	PUSH 15
	NOT
	PUSH 12
	AND
	PUSH 14
	OR
	POP 12
	#XX = Appel_XX || (XX && !(Reponse_XX))

	PUSH 1
	PUSH 2
	EQ
	PUSH 5
	PUSH 6
	EQ
	PUSH 8
	PUSH 9
	EQ
	PUSH 12
	PUSH 13
	AND
	AND
	AND
	JF jf7
	PUSHI 1
	POP 0
	#if((X0 == Old_X0) && (X1 == Old_X1) && (X2 == Old_X2) && (X3 == Old_X3)) stable = 1

jf7:
	PUSHI 0
	PUSH 0
	EQ
	NOT
	JF WhileInstable
	#Fin while(stable == 0)

NoWhile:
	J While1
	#Fin while(1)

	HALT
	END