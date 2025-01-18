# 000 : but0
# 001 : but0'rise
# 002 : but0'fall
# 003 : but1
# 004 : but1'rise
# 005 : but1'fall
# ...
# 047 : but15'fall
# 048 : led0
# ...
# 050 : led3
# 065 : an0
# 067 : an1
# 069 : an2
# 071 : PWM0_Freq
# 072 : PWM0_Duty
# 074 : PWM1_Freq
# 075 : PWM1_Duty
# 077 : PWM2_Freq
# 078 : PWM2_Duty
# 079 : stable 
# 080 : e0
# 081 : e1
# 082 : e2
# 083 : e3
# 084 : old_e0
# 085 : old_e1
# 086 : old_e2
# 087 : old_e3
# 088 : appel_e0
# 089 : appel_e1
# 090 : appel_e2
# 091 : appel_e3
# 092 : reponse_e0
# 093 : reponse_e1
# 094 : reponse_e2
# 095 : reponse_e3
# INITIALISATION variable stable
		PUSHI 0
		POP 79
# RAZ des variables appel_X et reponse_X
		PUSHI 0
		POP 88
		PUSHI 0
		POP 92
		PUSHI 0
		POP 89
		PUSHI 0
		POP 93
		PUSHI 0
		POP 90
		PUSHI 0
		POP 94
		PUSHI 0
		POP 91
		PUSHI 0
		POP 95
mainloop :
		PUSH 79
		PUSHI 0
		EQ
		JF fin_de_loop
# SAUVEGARDE DES ETATS PRECEDENTS
		PUSH 80
		POP 84
		PUSH 81
		POP 85
		PUSH 82
		POP 86
		PUSH 83
		POP 87
#Transition->name : t0
		PUSH 80
		PUSHI 1
		EQ
		PUSH 1
		PUSHI 1
		POP 64
		PUSH 65
		PUSHI 2048
		EQI
		AND
		AND
		JF Etiquette0
		PUSHI 1
		POP 89
		PUSHI 1
		POP 92
Etiquette0 :
#Transition->name : t1
		PUSH 81
		PUSHI 1
		EQ
		PUSH 1
		PUSHI 1
		POP 64
		PUSH 65
		PUSHI 2048
		EQS
		AND
		AND
		JF Etiquette1
		PUSHI 1
		POP 90
		PUSHI 1
		POP 93
Etiquette1 :
#Transition->name : t2
		PUSH 82
		PUSHI 1
		EQ
		PUSH 1
		PUSHI 1
		POP 64
		PUSH 65
		PUSHI 2048
		EQI
		AND
		AND
		JF Etiquette2
		PUSHI 1
		POP 91
		PUSHI 1
		POP 94
Etiquette2 :
#Transition->name : t3
		PUSH 83
		PUSHI 1
		EQ
		PUSH 1
		AND
		JF Etiquette3
		PUSHI 1
		POP 88
		PUSHI 1
		POP 95
Etiquette3 :
#Mise à jour de la valeur de l'étape e0
		PUSH 80
		PUSH 92
		NOT
		AND
		PUSH 88
		OR
		POP 80
#Mise à jour de la valeur de l'étape e1
		PUSH 81
		PUSH 93
		NOT
		AND
		PUSH 89
		OR
		POP 81
#Mise à jour de la valeur de l'étape e2
		PUSH 82
		PUSH 94
		NOT
		AND
		PUSH 90
		OR
		POP 82
#Mise à jour de la valeur de l'étape e3
		PUSH 83
		PUSH 95
		NOT
		AND
		PUSH 91
		OR
		POP 83
#TEST DE STABILITE
		PUSH 80
		PUSH 84
		EQ
		PUSH 81
		PUSH 85
		EQ
		PUSH 82
		PUSH 86
		EQ
		PUSH 83
		PUSH 87
		EQ
		AND
		AND
		AND
		JF next_loop
		PUSHI 1
		POP 79
next_loop :
		J mainloop
fin_de_loop :
#On affecte maintenant les valeurs aux sorties
		PUSH 80
		PUSHI 1
		EQ
		JF sortie0
		PUSHI 0
		POP 48
sortie0 :
		PUSH 81
		PUSHI 1
		EQ
		JF sortie1
		PUSHI 0
		POP 48
sortie1 :
		PUSH 82
		PUSHI 1
		EQ
		JF sortie2
		PUSHI 0
		POP 48
sortie2 :
		PUSH 83
		PUSHI 1
		EQ
		JF sortie3
		PUSHI 1
		POP 48
sortie3 :
		HALT
		end
