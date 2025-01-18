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
# 016 : e2
# 017 : e3
# 018 : old_e0
# 019 : old_e1
# 020 : old_e2
# 021 : old_e3
# 022 : appel_e0
# 023 : appel_e1
# 024 : appel_e2
# 025 : appel_e3
# 026 : reponse_e0
# 027 : reponse_e1
# 028 : reponse_e2
# 029 : reponse_e3
	pushi	0
	pop	13
	pushi	1
	pop	14
	pushi	0
	pop	22
	pushi	0
	pop	26
	pushi	0
	pop	23
	pushi	0
	pop	27
	pushi	0
	pop	24
	pushi	0
	pop	28
	pushi	0
	pop	25
	pushi	0
	pop	29
mainloop:
	push	13
	pushi	0
	eq
	jf	finloop
	push	14
	pop	18
	push	15
	pop	19
	push	16
	pop	20
	push	17
	pop	21
#evaluation de la transition t0
	push	14
	pushi	1
	eq
	push	1
	push	6
	pushi	128
	ls
	and
	and
	jf Jtransition0
	pushi	1
	pop	23
	pushi	1
	pop	26
	Jtransition0:
#evaluation de la transition t1
	push	15
	pushi	1
	eq
	push	1
	push	6
	pushi	128
	gt
	and
	and
	jf Jtransition1
	pushi	1
	pop	24
	pushi	1
	pop	27
	Jtransition1:
#evaluation de la transition t2
	push	16
	pushi	1
	eq
	push	1
	push	6
	pushi	128
	ls
	and
	and
	jf Jtransition2
	pushi	1
	pop	25
	pushi	1
	pop	28
	Jtransition2:
#evaluation de la transition t3
	push	17
	pushi	1
	eq
	push	4
	and
	jf Jtransition3
	pushi	1
	pop	22
	pushi	1
	pop	29
	Jtransition3:
#calcul de la nouvelle valeur de e0
	push	14
	push	26
	not
	and
	push	22
	or
	pop	18
#calcul de la nouvelle valeur de e1
	push	15
	push	27
	not
	and
	push	23
	or
	pop	19
#calcul de la nouvelle valeur de e2
	push	16
	push	28
	not
	and
	push	24
	or
	pop	20
#calcul de la nouvelle valeur de e3
	push	17
	push	29
	not
	and
	push	25
	or
	pop	21
#Test de stabilité
	push	14
	push	18
	eq
	push	15
	push	19
	eq
	push	16
	push	20
	eq
	push	17
	push	21
	eq
	and
	and
	and
	jf suiteloop
	pushi	1
	pop	13
suiteloop:
	jp mainloop
finloop:
#Affectation des sorties
	push	14
	pushi	1
	eq
	jf JAffectation0
	pushi	1
	pop	8
JAffectation0:
	push	15
	pushi	1
	eq
	jf JAffectation1
	pushi	1
	pop	9
JAffectation1:
	push	16
	pushi	1
	eq
	jf JAffectation2
	pushi	1
	pop	10
JAffectation2:
	push	17
	pushi	1
	eq
	jf JAffectation3
	pushi	1
	pop	11
JAffectation3:
	halt
	end
