#include <stdio.h>
#include <string.h>
//#include "canon_serial.h"
#define DEBUG 1

void grafcet_interpreter()
{
        char buf[256];
        int but0,but1,an0,an1,oldbut0,oldbut1,risebut0,risebut1,fallbut0,fallbut1;
	int stable;
	int e0,e1,e2,e3;
	int old_e0,old_e1,old_e2,old_e3;
	int appel_e0, appel_e1, appel_e2, appel_e3;
	int reponse_e0, reponse_e1, reponse_e2, reponse_e3;
        
	e0=1;
        e1=0;
        e2=0;
        e3=0;
        
        
        while (1)
          {
            // lecture des entrees
            oldbut0=0;
            oldbut1=0; 
          
            printf("but0: "); 
            scanf("%d",&but0); 
            printf("but1: "); 
            scanf("%d",&but1); 
            printf("pot: "); 
            scanf("%d",&an0); 
          
          
            if ((oldbut0==0) && (but0==1)) 
             risebut0=1; 
            else 
              risebut0=0; 
            if ((oldbut1==0) && (but1==1)) 
              risebut1=1; 
            else 
              risebut1=0; 
          
            // specifique a un grafcet donne
            stable=0;
          
            while (stable==0)
              {
                appel_e0=0 ; reponse_e0=0;
                appel_e1=0 ; reponse_e1=0;
                appel_e2=0 ; reponse_e2=0;
                appel_e3=0 ; reponse_e3=0;
            

                old_e0 = e0;
                old_e1 = e1;
                old_e2 = e2;
                old_e3 = e3;
       
                if ((e0==1) && ((risebut0==1) && (an0<128)))
                  {
                    appel_e1=1; reponse_e0=1;
                  }
                if ((e1==1) && ((risebut0==1) && (an0>128)))
                  {
                    appel_e2=1; reponse_e1=1;
                  }
                if ((e2==1) && ((risebut0==1) && (an0<128)))
                  {
                    appel_e3=1; reponse_e2=1;
                  }
                if ((e3==1) && (risebut1==1))
                  {
                    appel_e0=1; reponse_e3=1;
                  }
                
                e0= appel_e0 | (e0 & !reponse_e0);
                e1= appel_e1 | (e1 & !reponse_e1);
                e2= appel_e2 | (e2 & !reponse_e2);
                e3= appel_e3 | (e3 & !reponse_e3);
                
                
                if ((e0==old_e0) && (e1==old_e1) && (e2==old_e2) && (e3==old_e3))
                  {
                    stable=1;
                  }
#if DEBUG
                printf("\te0\te1\te2\te3\n");
                printf("Eold\t%d\t%d\t%d\t%d\n",old_e0,old_e1,old_e2,old_e3);
                printf("Appel\t%d\t%d\t%d\t%d\n",appel_e0,appel_e1,appel_e2,appel_e3);
                printf("Reponse\t%d\t%d\t%d\t%d\n",reponse_e0,reponse_e1,reponse_e2,reponse_e3);
                printf("Ecur \t%d\t%d\t%d\t%d\n",e0,e1,e2,e3);
                printf("---------------------------------\n");
#endif
                
              }
          
 //           if (e0==1)
 //             printf("----E0\n");
 //           if (e1==1)
 //             printf("----E1\n");
 //           if (e2==1)
 //             printf("----E2\n");
 //           if (e3==1)
 //             printf("----E3\n");
          }
}


int main(int argc, char **argv)
{
  //initserial();
  grafcet_interpreter();
  
  return 0;
}

