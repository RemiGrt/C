#stable => var[0]
#E1 => var[1]
#Old_E1 => var[2]
#Appel_E1 => var[3]
#Reponse_EI => var[4]
#E2 => var[5]
#Old_E2 => var[6]
#Appel_E2 => var[27]
#Reponse_E2 => var[7]
#E3 => var[8]
#Old_E3 => var[9]
#Appel_E3 => var[10]
#Reponse_E3 => var[11]
#E4 => var[12]
#Old_E4 => var[13]
#Appel_E4 => var[14]
#Reponse_E4 => var[15]
#pot => var[16]
#but1 => var[17]
#but2 => var[18]
#old_but1 => var[19]
#old_but2 => var[20]
#rise_but1 => var[21]
#rise_but2 => var[22]
#T1 => var[23]
#T2 => var[24]
#T3 => var[25]
#T4 => var[26]
#LED0 => var[28]
#LED1 => var[29]
#LED2 => var[30]
#LED3 => var[31]


while1:
	PUSH 19
	PUSHI 0
	EQ
	PUSH 17
	PUSHI 1
	EQ
	AND
	JF f1
	PUSHI 1
	POP 21
	J j1
	f1 : PUSHI 0
	POP 21 


	j1 : PUSH 20
	PUSHI 0
	EQ
	PUSH 18
	PUSHI 1
	EQ
	AND
	JF f2
	PUSHI 1
	POP 22
	J j2
	f2 : PUSHI 0
	POP 22

	#Lecture des donnée
	#T1
	PUSH 21
	PUSH 16
	PUSHI 128
	LS
	AND
	POP 23

	#T2
	PUSH 21
	PUSH 16
	PUSHI 128
	GT
	AND
	POP 24

	#T3
	PUSH 21
	PUSH 16
	PUSHI 128
	LS
	AND
	POP 25

	#T4
	PUSH 22
	POP 26

	#appel

	PUSHI 0
	POP 3
	PUSHI 0
	POP 27
	PUSHI 0
	POP 10
	PUSHI 0
	POP 14

	#reponse

	PUSHI 0
	POP 4
	PUSHI 0
	POP 7
	PUSHI 0
	POP 11
	PUSHI 0
	POP 15

	# stable
	PUSHI 0
	POP 0

	#while stable ==0

whilestable:
	PUSHI 0
	POP 0
	
	PUSH 1
	POP 2
	
	PUSH 5
	POP 6
	
	PUSH 8
	POP 9
	
	PUSH 12
	POP 13
	
	
	PUSH 1
	PUSHI 1
	EQ
	PUSH 23
	AND
	JF : polo 
	PUSHI 1
	POP 27
	PUSHI 1
	POP 4
#calcul transition T2 
polo: 	
	PUSH 5
	PUSHI 1
	EQ
	PUSH 24
	AND
	JF: golf
	PUSHI 1
	POP 10
	PUSHI 1
	POP 7
golf:
	
	PUSH 8	
	PUSHI 1
	EQ
	PUSH 25
	AND
	JF : passat
	PUSHI 1
	POP 14
	PUSHI 1
	POP 11
passat : 
	PUSH 12
	PUSHI 1
	EQ
	PUSH
	26
	JF: eos 
	PUSHI 1
	POP 3
	PUSHI 1
	POP 15
eos : 
	
	#calcul des etat ex
	
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
	
	#calcul de la stabilité
	
	PUSH 2
	PUSH 1
	EQ
	PUSH 6
	PUSH 5
	EQ
	AND
	PUSH 9
	PUSH 8
	EQ
	PUSH 13
	PUSH 12
	EQ
	AND
	AND 
	PUSHI 1
	POP 0	
	
	JF: whilestable
	
	PUSH 1		
	PUSHI 1
	EQ
	JF : clio
	PUSHI 1
	POP 28	# LED0
clio : 
	PUSH 5
	PUSHI 1
	EQ
	JF : twingo
	PUSHI 1
	POP 29 #LEd1
twingo : 
	PUSH 8
	PUSHI 1
	EQ
	JF: megane 
	PUSHI 1	
	POP 30 # LEd 2 
megane : 
	PUSH 12
	PUSHI 1
	EQ
	JF: espace 
	PUSHI 1 
	POP 31 #LED 3
espace :
	

	
	JP while1
	HALT
	END
