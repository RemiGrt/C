# 000 : but0
# 001 : but0'rise
# 002 : but0'fall
# 003 : but1
# 004 : but1'rise
# 005 : but1'fall
# 006 : but2
# 007 : but2'rise
# 008 : but2'fall
# 009 : an0
# 010 : an1
# 011 : led0
# 012 : led1
# 013 : led2
# 014 : led3
# 015 : stable 
# 016 : e0
# 017 : e1
# 018 : e2
# 019 : old_e0
# 020 : old_e1
# 021 : old_e2
# 022 : appel_e0
# 023 : appel_e1
# 024 : appel_e2
# 025 : reponse_e0
# 026 : reponse_e1
# 027 : reponse_e2
#	stable=0
	pushi	0
	pop	15
mainloop:
#	tant que stable=0
	push	15
	pushi	0
	eq
	jf	finloop
#	OLD_Ei=Ei
	push	16
	pop	19
	push	17
	pop	20
	push	18
	pop	21
#	APPEL_Ei=REPONSE_Ei=0
	pushi	0
	pop	22
	pushi	0
	pop	25
	pushi	0
	pop	23
	pushi	0
	pop	26
	pushi	0
	pop	24
	pushi	0
	pop	27
#test de franchissement de la transition t0
	push	16
	pushi	1
	eq
GenerateAsm debut
	push	1
GenerateAsm fin
	and
	jf	next0000
	pushi	1
	pop	23
	pushi	1
	pop	25
next0000:
#test de franchissement de la transition t1
	push	17
	pushi	1
	eq
GenerateAsm debut
	push	4
GenerateAsm fin
	and
	jf	next0001
	pushi	1
	pop	24
	pushi	1
	pop	26
next0001:
#test de franchissement de la transition t2
	push	18
	pushi	1
	eq
GenerateAsm debut
	push	7
GenerateAsm fin
	and
	jf	next0002
	pushi	1
	pop	22
	pushi	1
	pop	27
next0002:
#calcul de la nouvelle valeur de e0
	push	16
	push	25
	not
	and
	push	22
	or
	pop	16
#calcul de la nouvelle valeur de e1
	push	17
	push	26
	not
	and
	push	23
	or
	pop	17
#calcul de la nouvelle valeur de e2
	push	18
	push	27
	not
	and
	push	24
	or
	pop	18
#test de stabilite
	push	16
	push	19
	eq
	push	17
	push	20
	eq
	push	18
	push	21
	eq
	and
	and
	jf	suiteloop
	pushi	1
	pop	15
suiteloop:
	jp	mainloop
finloop:
#affectation des sorties
	push	16
	pushi	1
	eq
	jf	output0000
	pushi	0
	pop	11
output0000:
	push	17
	pushi	1
	eq
	jf	output0001
	pushi	1
	pop	11
output0001:
	push	18
	pushi	1
	eq
	jf	output0002
	pushi	2
	pop	11
output0002:
	halt
	end
