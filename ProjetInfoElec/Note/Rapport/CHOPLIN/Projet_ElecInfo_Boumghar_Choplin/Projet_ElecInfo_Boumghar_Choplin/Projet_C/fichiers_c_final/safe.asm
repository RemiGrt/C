# 000 : but0
# 001 : but0'rise
# 002 : but0'fall
# 003 : but1
# 004 : but1'rise
# 005 : but1'fall
# 006 : an0
# 007 : an1
# 008 : led0
# 009 : led1
# 010 : led2
# 011 : led3
# 013 : stable 
# 014 : e0
# 015 : e1
# 016 : old_e0
# 017 : old_e1
# 018 : appel_e0
# 019 : appel_e1
# 020 : reponse_e0
# 021 : reponse_e1
	pushi	0
	pop	13
	pushi	0
	pop	18
	pushi	0
	pop	20
	pushi	0
	pop	19
	pushi	0
	pop	21
mainloop:
	push	13
	pushi	0
	eq
	jf	finloop
	push	14
	pop	16
	push	15
	pop	17
#test de franchissement de la transition t0
	push	14
	pushi	1
	eq
	push	1
	and
	jf	next0000
	pushi	1
	pop	19
	pushi	1
	pop	20
next0000:
#test de franchissement de la transition t1
	push	15
	pushi	1
	eq
	push	2
	and
	jf	next0001
	pushi	1
	pop	18
	pushi	1
	pop	21
next0001:
#calcul de la nouvelle valeur de e0
	push	14
	push	20
	not
	and
	push	18
	or
	pop	14
#calcul de la nouvelle valeur de e1
	push	15
	push	21
	not
	and
	push	19
	or
	pop	15
#test de stabilite
	push	14
	push	16
	eq
	push	15
	push	17
	eq
	and
	jf	suiteloop
	pushi	1
	pop	13
suiteloop:
	jp	mainloop
finloop:
#affectation des sorties
	push	14
	pushi	1
	eq
	jf	output0000
	pushi	0
	pop	8
output0000:
	push	15
	pushi	1
	eq
	jf	output0001
	pushi	0
	pop	8
output0001:
	halt
	end
