#include <stdio.h>
#include <string.h>
#include "canon_serial.h"


void grafcet_interpreter()
{
        char buf[256];
        int but0,but1,an0,an1,oldbut0,oldbut1,risebut0,risebut1,fallbut0,fallbut1;
	int stable;
	int e0,e1,e2,e3;
	int old_e0,old_e1,old_e2,old_e3;
	int appel_e0, appel_e1, appel_e2, appel_e3;
	int reponse_e0, reponse_e1, reponse_e2, reponse_e3;

        oldbut0=0;
        oldbut1=0;

	e0=1;

        while (1)
        {
		// lecture des entrees

                readSerial(buf,0);
                sscanf(buf,"%d:%d:%d:%d",&but0,&but1,&an0,&an1);
                if ((oldbut0==0) && (but0==1))
                        risebut0=1;
                else
                        risebut0=0;
                if ((oldbut1==0) && (but1==1))
                        risebut1=1;
                else
                        risebut1=0;

                if ((oldbut0==1) && (but0==0))
                        fallbut0=1;
                else
                        fallbut0=0;
                if ((oldbut1==1) && (but1==0))
                        fallbut1=1;
                else
                        fallbut1=0;

                //printf("but0=%d but1=%d an0=%d an1=%d\n",but0,but1,an0,an1);
                if (risebut0)
		{
                        printf("risebut0\n");
			//tvar[17]=risebut0;	// On suppose que 17 est l'adresse de la variable risebut0 pour la MV 
		}
			
                if (risebut1)
                        printf("risebut1\n");
                if (fallbut0)
                        printf("fallbut0\n");
                if (fallbut1)
                        printf("fallbut1\n");
                oldbut0=but0;
                oldbut1=but1;

		// run();
		// specifique a un grafcet donne

		stable=0;
		appel_e0=0 ; reponse_e0=0;
		appel_e1=0 ; reponse_e1=0;
		appel_e2=0 ; reponse_e2=0;
		appel_e3=0 ; reponse_e3=0;

		while (stable==0)
		{

			old_e0 = e0;
			old_e1 = e1;
			old_e2 = e2;
			old_e3 = e3;

			if ((e0==1) && ((risebut0==1) && (an0<128)))
			{
				printf("receptive t0\n");
				appel_e1=1; reponse_e0=1;
			}
			if ((e1==1) && ((risebut0==1) && (an0>128)))
			{
				printf("receptive t1\n");
				appel_e2=1; reponse_e1=1;
			}
			if ((e2==1) && ((risebut0==1) && (an0<128)))
			{
				printf("receptive t2\n");
				appel_e3=1; reponse_e2=1;
			}
			if ((e3==1) && (risebut1==1))
			{
				printf("receptive t3\n");
				appel_e0=1; reponse_e3=1;
			}

			/*
			if ((e20==1) && (A))
			{
				appel_e21=1;
				appel_e23=1;
				reponse_e20=1;
			}
			*/

			e0= appel_e0 | (e0 & !reponse_e0);
			e1= appel_e1 | (e1 & !reponse_e1);
			e2= appel_e2 | (e2 & !reponse_e2);
			e3= appel_e3 | (e3 & !reponse_e3);

			printf("appel %d %d %d %d\n", appel_e0, appel_e1, appel_e2, appel_e3);
			printf("reponse %d %d %d %d\n", reponse_e0, reponse_e1, reponse_e2, reponse_e3);
			//printf("e0=%d e1=%d e2=%d e3=%d\n",e0,e1,e2,e3);

			if ((e0==old_e0) && (e1==old_e1) && (e2==old_e2) && (e3==old_e3))
			{
				stable=1;
				//printf("stable\n");
			}
		}

		if (e0==1)
			printf("00\n");
		if (e1==1)
			printf("01\n");
		if (e2==1)
			printf("02\n");
		if (e3==1)
			printf("03\n");

/*
		if (e0==1)
			writeSerial("00\n");
		if (e1==1)
			writeSerial("00\n");
		if (e2==1)
			writeSerial("00\n");
		if (e3==1)
			writeSerial("01\n");
*/
		
        }
}


int main(int argc, char **argv)
{
	initserial();
	grafcet_interpreter();

	return 0;
}

