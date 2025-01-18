#	Fichier assembleur correspondant au code du grafcet du coffre fort ecrit manuellement
#	Il contient 4 etats et 4 transitions et la gestion de la stabile du grafcet (obligatoire et du au passage du langage grafcet au langage C)
#	ce fichier est ensuite donne a l'assembleur qui fournit un fichier binaire
#	Les variables ci-dessous, ont chacune un numero qui correspond a l'indice de leur position dans le tableau variable de la machine virtuelle 
#	les etats de ces variables sont tres importants pour le bon fonctionnement du grafcet et leur position dans le tableau de variable doit etre fixe prealablement
#
# toutes les variables utilisées
# BOUTON0 0
# AM 1
# BOUTON1 2
# X0 3
# OLD_X0 4
# APPEL_X0 5
# REPONSE_X0 6
# X1 7
# OLD_X1 8
# APPEL_X1 9
# REPONSE_X1 10
# X2 11
# OLD_X2 12
# APPEL_X2 13
# REPONSE_X2 14
# X3 15
# OLD_X3 16
# APPEL_X3 18
# REPONSE_X3 19
# STABLE 20
# OLD_BOUTON0 21
# OLD_BOUTON1 22
#initialisation
	I_PUSHI 1
	I_POP 3
	I_PUSHI 0
	I_POP 7
	I_PUSHI 0
	I_POP 11
	I_PUSHI 0
	I_POP 15
#debut de la boucle while(1)
boucleWhile: 				
	I_PUSHI 0	
	I_POP 20
	I_PUSHI 0
	I_POP 0
	I_PUSHI 0
	I_POP 2
	I_PUSH 0
	I_POP 21
	I_PUSH 2
	I_POP 22
	I_PUSHI 0
	I_PUSH 1
# Saut de tous les scanfs à prendre en compte plus tard
# debut de la boucle stable
debutBoucleStable:
	I_PUSHI 0
	I_PUSH 20
	I_EQ
	I_JF finBoucleStable1
	I_PUSH 3
	I_POP 4
	I_PUSH 7
	I_POP 8
	I_PUSH 11
	I_POP 12
	I_PUSH 15
	I_POP 16
	I_PUSHI 0
	I_POP APPEL_XO
	I_PUSHI 0
	I_POP 9
	I_PUSHI 0
	I_POP 13
	I_PUSHI 0
	I_POP 18
	I_PUSHI 0
	I_POP REPONSE_XO
	I_PUSHI 0
	I_POP 10
	I_PUSHI 0
	I_POP 14
	I_PUSHI 0
	I_POP 19
#les if pour savoir l'état courrent (les printfs ne sont pas codés en assemlbeur)
	I_PUSH 3
	I_PUSHI 1
	I_EQ
	I_JF etat1
#printf je suis dans l'état X0	
etat1: 
	I_PUSH 7
	I_PUSHI 1
	I_EQ
	I_JF etat2
	#printf je suis dans l'état X1
etat2:
	I_PUSH 11
	I_PUSHI 1
	I_EQ
	I_JF etat3
	#printf je suis dans l'état X2
etat3:
	I_PUSH 15
	I_PUSHI 1
	I_EQ
	I_JF conditionPassageEtat1
#printf je suis dans l'état X3
# test pour passer aux états suivants
# Pour passer à 7
conditionPassageEtat1: 
	I_PUSH 3
	I_PUSHI 1
	I_EQ
	I_PUSH 21
	I_PUSHI 0
	I_EQ
	I_AND
	I_PUSH 0
	I_PUSHI 1
	I_EQ
	I_AND
	I_PUSH 1
	I_PUSHI 128
	I_LS				
	I_AND
	I_JF conditionPassageEtat2
	# le grafcet passe a l'etat 1
	I_PUSHI 1
	I_POP 9
	I_PUSHI 1
	I_POP 6
# Pour passer à X2
conditionPassageEtat2:
	I_PUSH 7
	I_PUSHI 1
	I_EQ
	I_PUSH 21
	I_PUSHI 0
	I_EQ
	I_AND
	I_PUSH 0
	I_PUSHI 1
	I_EQ
	I_AND
	I_PUSH 1
	I_PUSHI 128
	I_GT				
	I_AND
	I_JF conditionPassageEtat3
	# le grafcet passe a l'etat 2	
	I_PUSHI 1
	I_POP 13
	I_PUSHI 1
	I_POP 10
#Pour passer à X3
conditionPassageEtat3:
	I_PUSH 11
	I_PUSHI 1
	I_EQ
	I_PUSH 21
	I_PUSHI 0
	I_EQ
	I_AND
	I_PUSH 0
	I_PUSHI 1
	I_EQ
	I_AND
	I_PUSH 1
	I_PUSHI 128
	I_GT				
	I_AND
	I_JF conditionPassageEtat0
	# le grafcet passe a l'etat 3
	I_PUSHI 1
	I_POP 13
	I_PUSHI 1
	I_POP 10
# Pour passer X0
conditionPassageEtat0:
	I_PUSH 15
	I_PUSHI 1
	I_EQ
	I_PUSH 22
	I_PUSHI 0
	I_EQ
	I_AND
	I_PUSH 0
	I_PUSHI 1
	I_EQ			
	I_AND
	I_JF calculEtat	
	# le grafcet passe a l'etat 0
	I_PUSHI 1
	I_POP 13
	I_PUSHI 1
	I_POP 10
#Calcule des etats : variable[X0] = variable[APPEL_X0] || (variable[X0] && !(variable[REPONSE_X0]));
calculEtat:
	I_PUSH 6
	I_NOT
	I_PUSH 3
	I_AND
	I_PUSH 5
	I_OR
	I_POP 3
	I_PUSH 10
	I_NOT
	I_PUSH 7
	I_AND
	I_PUSH 9
	I_OR
	I_POP 7
	I_PUSH 14
	I_NOT
	I_PUSH 11
	I_AND
	I_PUSH 13
	I_OR
	I_POP 11
	I_PUSH 19
	I_NOT
	I_PUSH 15
	I_AND
	I_PUSH 18
	I_OR
	I_POP 15
#Calcul stabilite
	I_PUSH 3
	I_PUSH 4
	I_EQ
	I_PUSH 7
	I_PUSH 8
	I_EQ
	I_AND
	I_PUSH 11
	I_PUSH 12
	I_EQ
	I_AND
	I_PUSH 15
	I_PUSH 16
	I_EQ
	I_AND
	I_JF debutBoucleStable
	I_PUSHI 1
	I_POP 20
finBoucleStable1: 
# fin de la boucle while(1) on recommence au debut
	I_JP boucleWhile		
END
