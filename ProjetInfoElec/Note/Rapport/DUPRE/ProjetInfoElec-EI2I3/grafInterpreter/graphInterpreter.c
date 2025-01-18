#include <stdio.h>
#include <string.h>
#define DEBUG 1

// Fonction d'interpretation d'un graphcet.
// Cette fonction est propre a un graphcet donnée
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

      // ToDo
            
#if DEBUG
      printf("\te0\te1\te2\te3\n");
      printf("Eold\t%d\t%d\t%d\t%d\n",old_e0,old_e1,old_e2,old_e3);
      printf("Appel\t%d\t%d\t%d\t%d\n",appel_e0,appel_e1,appel_e2,appel_e3);
      printf("Reponse\t%d\t%d\t%d\t%d\n",reponse_e0,reponse_e1,reponse_e2,reponse_e3);
      printf("Ecur \t%d\t%d\t%d\t%d\n",e0,e1,e2,e3);
      printf("---------------------------------\n");
#endif
                
    }

}
}


int main(int argc, char **argv)
{
  grafcet_interpreter();
  return 0;
}

