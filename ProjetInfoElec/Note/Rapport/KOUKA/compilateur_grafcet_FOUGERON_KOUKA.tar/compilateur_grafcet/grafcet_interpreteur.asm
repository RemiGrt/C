###Affectation###

	I_PUSHI 0 
	I_POP stable


###On entre dans l'étape 1###

	I_PUSHI 1
	I_POP e1
	I_PUSHI 0
	I_POP e2
	I_PUSHI 0
	I_POP e3
	I_PUSHI 0
	I_POP e4

	while1:

###old_but1= 0 old_but2= 0###

# On entre dans l'étape 1 #
	I_PUSHI 0 
	I_POP old_but1

	I_PUSHI 0 
	I_POP old_but2

###Calcule des rise up###

# if(old_but1==0 &&  but1==1)
#			rise_but1=1;
#		}
#		else{
#			rise_but1=0;
#		}

	#On afffecte une valeur aux variables
	I_PUSHI 0 
	I_PUSH old_but
	I_EQ
	I_PUSHI 1
	I_PUSH but1
	#On effectue les opérations après l'affectation
	I_EQ
	I_AND
	#Condition sinon avant verif de risebut=1
	I_JF toto
	I_PUSHI 1
	I_POP rise_but1
	I_J toto1
toto: 
	I_PUSHI 0
	I_POP rise_but1
	
toto1:
	I_PUSHI 0 
	I_PUSH old_but2
	I_EQ
	I_PUSHI 1
	I_PUSH but2	
	I_EQ
	I_AND
	I_JF totti
	I_PUSHI 1
	I_POP rise_but2
	I_J toto2
totti: 
	I_PUSHI 0
	I_POP rise_but2

###Etape 3  initialise à 0 les appels et reponses### 

#if((e1==1) && (rise_but1==1 && Pot<128)){
#				appel_e2=1;//Mise à 1 de e2
#		stable=0
toto2:
	I_PUSHI 1
	I_PUSH e1
	I_EQ
	I_PUSHI 1
	I_PUSH rise_but1
	I_EQ
	I_PUSHI 128
	I_PUSH Pot
	I_INF
	I_AND
	I_AND
	I_PUSHI 1
	I_POP appel_e2
	I_J toto3
	I_PUSHI 0
	I_POP stable
	
	##Etiquette##
	
	while: 
	
	I_PUSHI 0
	I_PUSH stable
	I_EQ
	
	###Etape 4###
toto3:
	I_PUSHI e1
	I_POP old_e1
	I_PUSHI e2
	I_POP old_e2
	I_PUSHI e3
	I_POP old_e3
	I_PUSHI e4
	I_POP old_e4
	I_PUSHI 0
	I_POP appel_e1
	I_PUSHI 0
	I_POP appel_e2
	I_PUSHI 0
	I_POP appel_e3
	I_PUSHI 0
	I_POP appel_e4
	
###Etape 5 Condition de passage au étapes suivantes###

#if((e1==1) && (rise_but1==1 && Pot<128)){
#				appel_e2=1;//Mise à 1 de e2
#				reponse_e1=1;//Mise à 0 de e1
#				printf("\nrentré dans condition 1");
	I_PUSHI 1
	I_PUSH e1
	I_EQ
	I_PUSHI 1
	I_PUSH rise_but1
	I_EQ
	I_PUSHI 128
	I_PUSH Pot
	I_INF
	I_AND
	I_AND
	I_PUSHI 1
	I_POP appel_e2
	I_PUSHI 1
	I_POP reponse_e1
	I_J totu
	
#if((e2==1) && (rise_but1==1 && Pot>128)){	
#				appel_e3=1;//Mise à 1 de e3
#				reponse_e2=1;//Mise à 0 de e2
#				printf("\nrentré dans condition 2");

totu:
	I_PUSHI 1
	I_PUSH e2
	I_EQ
	I_PUSHI 1
	I_PUSH rise_but1
	I_EQ
	I_PUSHI 128
	I_PUSH Pot
	I_SUP
	I_AND
	I_AND
	I_AND
	I_PUSHI 1
	I_POP appel_e3
	I_PUSHI 1
	I_POP reponse_e2
	I_J tota
	
#if((e3==1) && (rise_but1==1 && Pot<128)){
#				appel_e4=1;//Mise à 1 de e4
#				reponse_e3=1;//Mise à 0 de e3
#				printf("\nrentré dans condition 3");
					
tota:
	I_PUSHI 1
	I_PUSH e3
	I_EQ
	I_PUSHI 1
	I_PUSH rise_but1
	I_EQ
	I_PUSHI 128
	I_PUSH Pot
	I_INF
	I_AND
	I_AND
	I_AND
	I_PUSHI 1
	I_POP appel_e4
	I_PUSHI 1
	I_POP reponse_e3
	I_J tote

#if((e4==1) && (rise_but2==1)){
#				appel_e1=1;//Mise à 1 de e1
#				reponse_e4=1;//Mise à 0 de e4
#				printf("\nrentré dans condition 4");
#			}		
	
tote:
	I_PUSHI 1
	I_PUSH e4
	I_EQ
	I_PUSHI 1
	I_PUSH rise_but2
	I_EQ
	I_AND
	I_AND
	I_PUSHI 1
	I_POP appel_e1
	I_PUSHI 1
	I_POP reponse_e4
	I_J totou
	
###Etape 6 Calcul des etats e_x###

#			e1 = appel_e1 || (e1 && !(reponse_e1));
#			e2 = appel_e2 || (e2 && !(reponse_e2));
#			e3 = appel_e3 || (e3 && !(reponse_e3));
#			e4 = appel_e4 || (e4 && !(reponse_e4));	

totou:
I_PUSHI reponse_e1
I_NOT
I_PUSHI e1
I_AND
I_PUSHI appel_e1
I_OR
I_POP e1

I_PUSHI reponse_e2
I_NOT
I_PUSHI e2
I_AND
I_PUSHI appel_e2
I_OR
I_POP e2

I_PUSHI reponse_e3
I_NOT
I_PUSHI e3
I_AND
I_PUSHI appel_e3
I_OR
I_POP e3

I_PUSHI reponse_e4
I_NOT
I_PUSHI e4
I_AND
I_PUSHI appel_e4
I_OR
I_POP e4

###Etape 7 Calcul de la stabilité###

#if(e1==old_e1 && e2==old_e2 && e3==old_e3 && e4==old_e4){
#				stable=1;
#			}

	I_PUSHI old_e1
	I_PUSH e1
	I_EQddLabel
	I_PUSHI old_e2
	I_PUSH e2
	I_EQ
	I_PUSHI old_e3
	I_PUSH e3
	I_EQ
	I_PUSHI old_e4
	I_PUSH e4
	I_EQ
	I_AND
	I_AND
	I_AND
	I_J totan
	I_PUSHI 1
	I_POP stable
	
	
	I_J while
	I_J while1
	I_HALT 	
	END
#













