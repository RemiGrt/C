// Exemple de code en C (extrait generateCode) et ce qui est généré
// en ASM
//
// Le mapping memory est le suivant
//# 000 : but0
//# 001 : but0'rise
//# 002 : but0'fall
//# 003 : but1
//# 004 : but1'rise
//# 005 : but1'fall
//# 006 : but2
//# 007 : but2'rise
//# 008 : but2'fall
//# 009 : an0
//# 010 : an1
//# 011 : led0
//# 012 : led1
//# 013 : led2
//# 014 : led3
//# 015 : stable 
//# 016 : e0
//# 017 : e1
//# 018 : e2
//# 019 : e3
//# 020 : old_e0
//# 021 : old_e1
//# 022 : old_e2
//# 023 : old_e3
//# 024 : appel_e0
//# 025 : appel_e1
//# 026 : appel_e2
//# 027 : appel_e3
//# 028 : reponse_e0
//# 029 : reponse_e1
//# 030 : reponse_e2
//# 031 : reponse_e3
//

// n définit le nombre d'étape
n=nbEtapes(en);

// Cas 1
//
// C
//
printf("#\tOLD_Ei=Ei\n");
etape=en;
while (etape!=NULL)
  {
    printf("\tpush\t%d\n",16+etape->id);
    printf("\tpop\t%d\n",16+n+etape->id);
    etape=etape->next;
  }

//
// Assembleur généré
//
//#	OLD_Ei=Ei
//	push	16
//	pop	20
//	push	17
//	pop	21
//	push	18
//	pop	22
//	push	19
//	pop	23


// Cas 2
//
// C
//
etape=en;
while (etape!=NULL)
  {
    printf ("#calcul de la nouvelle valeur de %s\n", etape->name);
    printf("\tpush\t%d\n",16+etape->id);
    printf("\tpush\t%d\n",16+3*n+etape->id);
    printf("\tnot\n");
    printf("\tand\n");
    printf("\tpush\t%d\n",16+2*n+etape->id);
    printf("\tor\n");
    printf("\tpop\t%d\n",16+etape->id);
    etape=etape->next;
  }

//
// Assembleur généré
//
//#calcul de la nouvelle valeur de e0
//	push	16
//	push	28
//	not
//	and
//	push	24
//	or
//	pop	16
//#calcul de la nouvelle valeur de e1
//	push	17
//	push	29
//	not
//	and
//	push	25
//	or
//	pop	17
//#calcul de la nouvelle valeur de e2
//	push	18
//	push	30
//	not
//	and
//	push	26
//	or
//	pop	18
//#calcul de la nouvelle valeur de e3
//	push	19
//	push	31
//	not
//	and
//	push	27
//	or
//	pop	19
//
