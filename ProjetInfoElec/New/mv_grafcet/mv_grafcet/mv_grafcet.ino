#include <A4990MotorShield.h>

/*
 * This example uses the A4990MotorShield library to drive each motor with the
 * Pololu A4990 Dual Motor Driver Shield for Arduino forward, then backward. 
 * The yellow user LED is on when a motor is set to a positive speed and off when
 * a motor is set to a negative speed.
 */

#define LED_PIN 13

#define OP_ADD    1 
#define OP_SUB    2
#define OP_MULT   3
#define OP_DIV    4

#define OP_NEG    7
#define OP_AND    8
#define OP_OR   9
#define OP_NOT    10
#define OP_EQ   11
#define OP_LS   12
#define OP_GT   13

#define OP_INC    14  
#define OP_DEC    15

#define OP_PUSH   100
#define OP_PUSHI  101
#define OP_POP      102

#define OP_JP   200
#define OP_JF   201

#define OP_HALT   403

A4990MotorShield motors;
char line[20];
int cptLine;
int pc;
int sp;
int v;
int codeSegment[]={
101,
0,102,15,100,15,101,0,11,201,159,100,16,102,19,100,17,
102,20,100,18,102,21,101,0,102,22,101,0,102,25,101,0,
102,23,101,0,102,26,101,0,102,24,101,0,102,27,100,16,
101,1,11,100,1,8,201,65,101,1,102,23,101,1,102,25,
100,17,101,1,11,100,4,8,201,83,101,1,102,24,101,1,
102,26,100,18,101,1,11,100,7,8,201,101,101,1,102,22,
101,1,102,27,100,16,100,25,10,8,100,22,9,102,16,100,
17,100,26,10,8,100,23,9,102,17,100,18,100,27,10,8,
100,24,9,102,18,100,16,100,19,11,100,17,100,20,11,100,
18,100,21,11,8,8,201,157,101,1,102,15,200,4,100,16,
101,1,11,201,170,101,0,102,11,100,17,101,1,11,201,181,
101,1,102,11,100,18,101,1,11,201,192,101,2,102,11,403,
};
int pile[20];
int vars[50];
int run_mv;

int c0,c1,c2;
int old_c0, old_c1, old_c2;
int rise_c0, rise_c1, rise_c2;

void run()
{
  while (codeSegment[pc]!=OP_HALT)
  {
    switch (codeSegment[pc])
    {
      case OP_ADD:
        pile[sp-1]=pile[sp-1]+pile[sp]; 
        sp-- ; pc++ ; break;
      case OP_SUB:
        pile[sp-1]=pile[sp-1]-pile[sp]; 
        sp-- ; pc++ ; break;
      case OP_MULT:
        pile[sp-1]=pile[sp-1]*pile[sp]; 
        sp-- ; pc++ ; break;
      case OP_DIV:
        pile[sp-1]=pile[sp-1]/pile[sp]; 
        sp-- ; pc++ ; break;
      case OP_NEG:
        pile[sp]=-pile[sp]; 
        pc++ ; break;
      case OP_AND:
        pile[sp-1]=((int)pile[sp-1] & (int)pile[sp]); 
        sp-- ; pc++ ; break;
      case OP_OR:
        pile[sp-1]=((int)pile[sp-1] | (int)pile[sp]); 
        sp-- ; pc++ ; break;
      case OP_NOT:
        pile[sp]=(1-(int)pile[sp]); 
        pc++ ; break;
      case OP_EQ:
        pile[sp-1]=(pile[sp-1]==pile[sp]) ? 1 : 0; 
        sp-- ; pc++ ; break;
      case OP_LS:
        pile[sp-1]=(pile[sp-1]<pile[sp]) ? 1 : 0; 
        sp-- ; pc++ ; break;
      case OP_GT:
        pile[sp-1]=(pile[sp-1]>pile[sp]) ? 1 : 0; 
        sp-- ; pc++ ; break;
      case OP_PUSH:
        sp++;
        pile[sp]=vars[codeSegment[pc+1]];
        pc=pc+2; 
        break;
      case OP_POP:
        vars[codeSegment[pc+1]]=pile[sp];
        sp--;
        pc+=2;
        break;
      case OP_PUSHI:
        sp++;
        pile[sp]=codeSegment[pc+1];
        pc+=2;
        break;
      case OP_JP:
        pc=codeSegment[pc+1];
        break;
      case OP_JF:
        if (pile[sp]==0)
          pc=codeSegment[pc+1];
        else
          pc=pc+2;
        sp--;
        break;
      default:
        break;
    }
  }
}
/* 
 * For safety, it is good practice to monitor motor driver faults and handle
 * them in an appropriate way. If a fault is detected, both motor speeds are set
 * to zero and it is reported on the serial port.
 */
void stopIfFault()
{
  if (motors.getFault())
  {
    motors.setSpeeds(0,0);
    Serial.println("Fault");
    while(1);
  }
}

void setup()
{
  pinMode(LED_PIN, OUTPUT);

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  
  Serial.begin(9600);

  motors.setM1Speed(0);

   run_mv=1;
   pc=0;
   sp=-1;
  
   cptLine=0;

  c0=c1=c2=0;
  old_c0=old_c1=old_c2=0;
  rise_c0=rise_c1=rise_c2=0;
  //fall_c0=fall_c1=fall_c2=0;

  vars[16]=1;
  vars[17]=0;
  vars[18]=0;
  
}

void loop()
{
  int pos,v;
  /*
   if (Serial.available())
   {
      char c=Serial.read();
      line[cptLine++]=c;
      if (c=='@')
      {
        line[cptLine++]='\0';
        sscanf(line,"%d:%d@",&pos,&v);
        codeSegment[pos]=v;
        cptLine=0;
      }   
      else if (c=='R')
      {
        run_mv=1;
      }
      Serial.write(c);
   }
*/
   c0=1-digitalRead(2);
   c1=1-digitalRead(3);
   c2=1-digitalRead(4);

   if ((c0==1) && (old_c0==0))
     rise_c0=1;
   else
     rise_c0=0;

   if ((c1==1) && (old_c1==0))
     rise_c1=1;
   else
     rise_c1=0;

   if ((c2==1) && (old_c2==0))
     rise_c2=1;
   else
     rise_c2=0;

   vars[1]=rise_c0;
   vars[4]=rise_c1;
   vars[7]=rise_c2;
   
   if (run_mv==1)
   {
        pc=0;
        run();
   }

  /* 
  Serial.print(rise_c0);
  Serial.print(' ');
  Serial.print(rise_c1);
  Serial.print(' ');
  Serial.println(rise_c2);
*/

  if (vars[11]==0)
    motors.setM1Speed(0);
  else if (vars[11]==1)
    motors.setM1Speed(400);
  else if (vars[11]==2)
    motors.setM1Speed(-400);
  
   old_c0=c0;
   old_c1=c1;
   old_c2=c2;
   
}
