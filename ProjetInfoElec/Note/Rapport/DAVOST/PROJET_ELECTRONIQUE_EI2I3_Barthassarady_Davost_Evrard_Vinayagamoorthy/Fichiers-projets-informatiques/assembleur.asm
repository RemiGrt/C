#Assembleur qui reprend le code vm_codops.c void grafcet_interuption()
#Rappel du tableau de variable
#1:stable
#2:e1
#3:e2
#4:e3
#5:e4
#6:appel_e1
#7:appel_e2
#8:appel_e3
#9:appel_e4
#10:reponse_e1
#11:reponse_e2
#12:reponse_e3
#13:reponse_e4
#14:old_e1
#15:old_e2
#16:old_e3
#17:old_e4
#18:old_but1 
#19:old_but2
#20:pot
#21:but1
#22:but2 
#23:rise_but1
#24:rise_but2


# declaration e1=1 e2=0 e3=0 e4=0 but1=0 but2=0;	
	I_PUSHI 1
	I_POP e1
	I_PUSHI 0
	I_POP e2
	I_PUSHI 0
	I_POP e3
	I_PUSHI 0
	I_POP e4

# debut 
jump_while1:

#initialisation old_but1 = but1 et old_but2 = but2;
	I_PUSH old_but1  
	I_POP  but1
	I_PUSH old_but2  
	I_POP  but2

#if(but1==1 && old_but1==0)
	I_PUSH old_but1
	I_PUSHI 0
	I_EQ
	I_PUSH but1
	I_PUSHI 1
	I_EQ
	I_AND
	I_JF jf1 
	I_PUSHI 1
	I_POP rise_but1
jf1:
	
#if(but1==0 && old_but1==1)
	I_PUSH old_but1
	I_PUSHI 1
	I_EQ
	I_PUSH but1
	I_PUSHI 0
	I_EQ
	I_AND
	I_JF jf2 
	I_PUSHI 0
	I_POP rise_but1
jf2:

#if(but2==1 && old_but2==0)
	I_PUSH old_but2
	I_PUSHI 0
	I_EQ
	I_PUSH but2
	I_PUSHI 1
	I_EQ
	I_AND
	I_JF jf3 
	I_PUSHI 1
	I_POP rise_but2
jf3:

#if(but2==0 && old_but2==1)
	I_PUSH old_but2
	I_PUSHI 1
	I_EQ
	I_PUSH but2
	I_PUSHI 0
	I_EQ
	I_AND
	I_JF jf4 
	I_PUSHI 0
	I_POP rise_but2
jf4:

# initialisation stable=0,appel_e1 =0 appel_e2=0,appel_e3=0,appel_e4=0;
#				reponse_e1=0,reponse_e2=0,reponse_e3=0,reponse_e4=0;
		
	I_PUSHI 0
	I_POP stable
	I_PUSHI 0
	I_POP appel_e1
	I_PUSHI 0
	I_POP appel_e2
	I_PUSHI 0
	I_POP appel_e3
	I_PUSHI 0
	I_POP appel_e4
	I_PUSHI 0
	I_POP reponse_e1
	I_PUSHI 0
	I_POP reponse_e2
	I_PUSHI 0
	I_POP reponse_e3
	I_PUSHI 0
	I_POP reponse_e4

jump_while_stable:

#if (e1==1 && (rise_but1==1 && pot< 128))
	I_PUSHI 128
	I_PUSH pot
	I_LS
	I_PUSHI 1
	I_PUSH rise_but1
	I_EQ
	I_AND
	I_PUSHI 1
	I_PUSH e1
	I_EQ
	I_AND
	I_JF jf5
	I_PUSHI 1
	I_POP appel_e2	
	I_PUSHI 1
	I_POP reponse_e1
jf5:

#if (e2==1 && (rise_but1==1 && pot > 128))
	I_PUSHI 128
	I_PUSH pot
	I_GT
	I_PUSHI 1
	I_PUSH rise_but1
	I_EQ
	I_AND
	I_PUSHI 1
	I_PUSH e2
	I_EQ
	I_AND
	I_JF jf6
	I_PUSHI 1
	I_POP appel_e3	
	I_PUSHI 1
	I_POP reponse_e2
jf6:

#if (e3==1 && (rise_but1==1 && pot > 128))
	I_PUSHI 128
	I_PUSH pot
	I_LS
	I_PUSHI 1
	I_PUSH rise_but1
	I_EQ
	I_AND
	I_PUSHI 1
	I_PUSH e3
	I_EQ
	I_AND
	I_JF jf6
	I_PUSHI 1
	I_POP appel_e4	
	I_PUSHI 1
	I_POP reponse_e3
jf6:
	
#if (e4==1 && rise_but2==1)
	I_PUSHI 1
	I_PUSH rise_but2
	I_EQ
	I_PUSHI 1
	I_PUSH e4
	I_EQ
	I_JF jf7
	I_PUSHI 1
	I_POP appel_e1
	I_PUSHI 1
	I_POP reponse_e4
jf7:

#old_e1=e1;
#e1=(appel_e1 || (e1 && !(reponse_e1)));

	I_PUSH e1
	I_POP old_e1
	
	I_PUSH reponse_e1
	I_NOT 
	I_PUSH e1
	I_AND
	I_PUSH appel_e1
	I_OR 

#old_e2=e2;
#e2=(appel_e2 || (e2 && !(reponse_e2)));

	I_PUSH e2
	I_POP old_e2
	
	I_PUSH reponse_e2
	I_NOT 
	I_PUSH e2
	I_AND
	I_PUSH appel_e2
	I_OR 	
 	
#old_e3=e3;
#e3=(appel_e3 || (e3 && !(reponse_e3)));

	I_PUSH e3
	I_POP old_e3
	
	I_PUSH reponse_e3
	I_NOT 
	I_PUSH e3
	I_AND
	I_PUSH appel_e3
	I_OR 

#old_e4=e4;
#e2=(appel_e4 || (e4 && !(reponse_e4)));

	I_PUSH e4
	I_POP old_e4
	
	I_PUSH reponse_e4
	I_NOT 
	I_PUSH e4
	I_AND
	I_PUSH appel_e4
	I_OR 

#if ((e1==old_e1) && (e2==old_e2) && (e3==old_e3) && (e4==old_e4))

	I_PUSH old_e1
	I_PUSH e1
	I_EQ
	I_PUSH old_e2
	I_PUSH e2
	I_EQ
	I_PUSH old_e3
	I_PUSH e3
	I_EQ
	I_PUSH old_e4
	I_PUSH e4
	I_EQ
	I_JF jump_while_stable
	I_PUSHI 1
	I_POP stable
	I_JP jump_while1
	
#fin
	I_HALT
	I_END


