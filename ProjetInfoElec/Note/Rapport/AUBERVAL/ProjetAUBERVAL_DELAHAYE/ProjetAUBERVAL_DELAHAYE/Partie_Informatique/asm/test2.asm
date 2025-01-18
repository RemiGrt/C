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
	jf	toto1
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
	push	1
	push	9
	pushi	128
	ls
	and
	and
	jf	toto
	pushi	1
	pop	25
	pushi	1
	pop	28
toto :
	pushi 0
	pop 1
toto1 : 
	end
