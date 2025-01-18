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
# 019 : e3
# 020 : old_e0
# 021 : old_e1
# 022 : old_e2
# 023 : old_e3
# 024 : appel_e0
# 025 : appel_e1
# 026 : appel_e2
# 027 : appel_e3
# 028 : reponse_e0
# 029 : reponse_e1
# 030 : reponse_e2
# 031 : reponse_e3
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
	pop	20
	push	17
	pop	21
	push	18
	pop	22
	push	19
	pop	23
#	APPEL_Ei=REPONSE_Ei=0
	pushi	0
	pop	24
	pushi	0
	pop	28
	pushi	0
	pop	25
	pushi	0
	pop	29
	pushi	0
	pop	26
	pushi	0
	pop	30
	pushi	0
	pop	27
	pushi	0
	pop	31
#test de franchissement de la transition t0
	push	16
	pushi	1
	eq
GenerateAsm debut
	push	1
	push	9
	pushi	128
	ls
	and
GenerateAsm fin
	and
	jf	next0000
	pushi	1
	pop	25
	pushi	1
	pop	28
next0000:
#test de franchissement de la transition t1
	push	17
	pushi	1
	eq
GenerateAsm debut
	push	1
	push	9
	pushi	128
	gt
	and
GenerateAsm fin
	and
	jf	next0001
	pushi	1
	pop	26
	pushi	1
	pop	29
 	pushi	1
	pop	30
next0002:
#test de franchissement de la transition t3
	push	19
	pushi	1
	eq
GenerateAsm debut
	push	4
GenerateAsm fin
	and
	jf	next0003
	pushi	1
	pop	24
	pushi	1
	pop	31
next0003:
#calcul de la nouvelle valeur de e0
	push	16
	push	28
	not
	and
	push	24
	or
	pop	16
#calcul de la nouvelle valeur de e1
	push	17
	push	29
	not
	and
	push	25
	or
	pop	17
#calcul de la nouvelle valeur de e2
	push	18
	push	30
	not
	and
	push	26
	or
	pop	18
#calcul de la nouvelle valeur de e3
	push	19
	push	31
	not
	and
	push	27
	or
	pop	19
#test de stabilite
	push	16
	push	20
	eq
	push	17
	push	21
	eq
	push	18
	push	22
	eq
	push	19
	push	23
	eq
	and
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
	pushi	0
	pop	11
output0001:
	push	18
	pushi	1
	eq
	jf	output0002
	pushi	0
	pop	11
output0002:
	push	19
	pushi	1
	eq
	jf	output0003
	pushi	1
	pop	11
output0003:
	halt
	end
