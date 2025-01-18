#adresses des variables

# 0 But0
# 1 But1
# 2 Pot
# 3 RiseBut0
# 4 Risebut1
# 5 Old_But0
# 6 Old_But1
# 7 e0
# 8 e1
# 9 e2
#10 e3
#11 Old_e0
#12 Old_e1
#13 Old_e2
#14 Old_e3
#15 appel_e0
#16 appel_e1
#17 appel_e2
#18 appel_e3
#19 reponse_e0
#20 reponse_e1
#21 reponse_e2
#22 reponse_e3
#23 stable
#24 led0

#Initialisation des entrés

	PUSHI 1
	POP 7
	PUSHI 0
	POP 0
	POP 1
	POP 8
	POP 9
	POP 10

#Boucle infinie
while1:		
#Calcul des fronts	
	PUSHI 1
	PUSH 0
	EQ
	PUSHI 0
	PUSH 5
	EQ
	AND
	JF toto
	PUSHI 1
	POP 3
toto:   PUSHI 0
	POP 3
	
	PUSHI 1
	PUSH 1
	EQ
	PUSHI 0
	PUSH 6
	EQ
	AND
	JF toto1
	PUSHI 1
	POP 4
toto1:	PUSHI 0
	POP 4
	
# init stable
	PUSHI 0
	POP 23

	
while : 
#Initialisation 
	PUSHI 0
	POP 15
	POP 16
	POP 17
	POP 18
	POP 19
	POP 20
	POP  21
        POP  22

#condition de franchissement pour aller de e0 à e1
	PUSHI 1
	PUSH 7
	EQ
	PUSHI 1
	PUSH 3
	EQ
	PUSHI 128
	PUSH 2
	GT
	AND
	AND
	JF transition1
	PUSHI 1
	POP 16
	POP 19
transition1: PUSHI 0
	POP 16
	POP 19

#Condition de franchissement pour aller de e1 à e2

	PUSHI 1
	PUSH 8
	EQ
	PUSHI 1
	PUSH 3
	EQ
	PUSHI 128
	PUSH 2
	LT
	AND
	AND
	JF transition2
	PUSHI 1
	POP 17
	POP 20
transition2: PUSHI 0));
	e1= appel_e1 || (e1 && !
	POP 17
	POP 20

Condition de franchissement pour aller de e2 à e3

	PUSHI 1
	PUSH 9
	EQ
	PUSHI 1
	PUSH 3
	EQ
	PUSHI 128
	PUSH 2
	GT
	AND
	AND
	JF transition3
	PUSHI 1
	POP 18
	POP 21
transition3: PUSHI 0
	POP 18
	POP 21

Condition de franchissement pour aller de e3 à e1

	PUSHI 1
	PUSH 10
	EQ
	PUSHI 1
	PUSH 4
	EQ
	AND
	JF transition4
	PUSHI 1
	POP 15
	POP 22
transition4: PUSHI 0
	POP 15
	POP 22

Calcul de e0

       PUSH 19
       NOT 19
       PUSH 7
       AND
       PUSH 15
       OR
       POP 7

Calcul de e1

       PUSH 20
       NOT 20
       PUSH 8
       AND
       PUSH 16
       OR
       POP 8

Calcul de e2

       PUSH 21
       NOT 21
       PUSH 9_e0
       AND
       PUSH 17
       OR
       POP 9

Calcul de e3

       PUSH 22
       NOT 22
       PUSH 10
       AND
       PUSH 18
       OR
       POP 10

calcul de la stabilite
        PUSH 11
	PUSH 7
        EQ
	PUSH 12
	PUSH 8
        EQ
        PUSH 13
	PUSH 9
        EQ
        PUSH 14
	PUSH 10
        EQ
	AND
	AND
	AND
	JF stabilite 
	PUSHI 1
	POP 23

stabilite: 
        PUSHI 0
	POP 23

extinction de la led0 sur e0
        PUSHI 1
	PUSH 7
        PUSHI 0
        POP 24

extinction de la led0 sur e1
        PUSHI 1
	PUSH 8
        PUSHI 0
        POP 24

extinction de la led0 sur e2
        PUSHI 1
	PUSH 9
        PUSHI 0
        POP 24
allumage de la led0 sur e3
        PUSHI 1
	PUSH 10
        JF led_e3
        PUSHI 1
        POP 24
Led_e3:
        PUSHI 0
        POP 24


	JF while
	JP while1 

end
