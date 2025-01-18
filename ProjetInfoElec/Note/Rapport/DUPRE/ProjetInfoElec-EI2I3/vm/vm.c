#include <stdio.h>
#include "vm_codeps.h"

int pc = 0;
int sp = -1;
int code[100];
int stack[100];
char variable[100];

void Init_TIM15_CH1_Input_Capture_With_Interrupt (void);
void init_PIN_Output(GPIO_TypeDef GPIO, int num_Pin);
void init_PIN_Input(GPIO_TypeDef GPIO, int num_Pin);
void Choix_val_Sortie(GPIO_TypeDef GPIO, int num_Pin, int val);
void init_PIN_Alternate_Function(GPIO_TypeDef GPIO, int num_Pin, int num_AF);

void read_bin(char *filename){
	int nbr_instruct, a, b, i;
	FILE *file;
	file=fopen(filename, "r");
	fscanf(file, "%d", &nbr_instruct);
	printf("Nombre d'instructions =%d\n", nbr_instruct);
	for(i=0; i<nbr_instruct; i++){
		fscanf(file, "%d:%d", &a, &b);
		code[a]=b;
		printf("code[a]=%d\n", code[a]);
	}
	fclose(file);
}

void init_PIN_Output(GPIO_TypeDef GPIO, int num_Pin){
	//Initialisation des Horloges pour les GPIOs
	RCC->AHBENR |=(1<<17);
	RCC->AHBENR |=(1<<18);
	RCC->AHBENR |=(1<<19);
	RCC->AHBENR |=(1<<20);
	RCC->AHBENR |=(1<<21);
	RCC->AHBENR |=(1<<22);
	
	GPIO.MODER &=~(1UL<<((2*num_Pin)+1));   /* choix mode General Purpose Output bit à '0' */
    GPIO.MODER |=(1UL<<(2*num_Pin));    /* choix mode General Purpose Output bit à '1' */
    GPIO.OTYPER &=~(1UL<<num_Pin);   /* choix techno de sortie Push-Pull : bit à '0' */
    GPIO.PUPDR &=~(1UL<<((2*num_Pin)+1));   /* desactivation resistance de tirage: bit à '0' */
    GPIO.PUPDR &=~(1UL<<(2*num_Pin));   /* desactivation resistance de tirage: bit à '0' */
    GPIO.OSPEEDR&=~(1UL<<((2*num_Pin)+1));  /* choix vitesse de sortie bit à '0' */
    GPIO.OSPEEDR|=(1UL<<(2*num_Pin));   /* choix vitesse de sortie  '0' */
	
}

void init_PIN_Input(GPIO_TypeDef GPIO, int num_Pin){
	//Initialisation des Horloges pour les GPIOs
	RCC->AHBENR |=(1<<17);
	RCC->AHBENR |=(1<<18);
	RCC->AHBENR |=(1<<19);
	RCC->AHBENR |=(1<<20);
	RCC->AHBENR |=(1<<21);
	RCC->AHBENR |=(1<<22);
	
	GPIO.MODER &=~(1UL<<((2*num_Pin)+1));   /* choix mode Input bit à '0' */
    GPIO.MODER &=~(1UL<<(2*num_Pin));    /* choix mode Input bit à '0' */
    GPIO.PUPDR &=~(1UL<<((2*num_Pin)+1));   /* desactivation resistance de tirage: bit à '0' */
    GPIO.PUPDR &=~(1UL<<(2*num_Pin));   /* desactivation resistance de tirage: bit à '0' */
  	
}

void Choix_val_Sortie(GPIO_TypeDef GPIO, int num_Pin, int val){
	if(val == 0) GPIO.ODR &=~ (1<<num_Pin);
	else if (val == 1) GPIO.ODR |= (1<<num_Pin);
}

void init_PIN_Alternate_Function(GPIO_TypeDef GPIO, int num_Pin, int num_AF){
	//Initialisation des Horloges pour les GPIOs
	RCC->AHBENR |=(1<<17);
	RCC->AHBENR |=(1<<18);
	RCC->AHBENR |=(1<<19);
	RCC->AHBENR |=(1<<20);
	RCC->AHBENR |=(1<<21);
	RCC->AHBENR |=(1<<22);
	
	GPIO.MODER |=(1UL<<((2*num_Pin)+1));   /* choix mode Alternate Function bit à '1' */
    GPIO.MODER &=~(1UL<<(2*num_Pin));    /* choix mode Alternate Function bit à '0' */
    GPIO.OTYPER &=~(1UL<<num_Pin);   /* choix techno de sortie Push-Pull : bit à '0' */
    GPIO.PUPDR &=~(1UL<<((2*num_Pin)+1));   /* desactivation resistance de tirage: bit à '0' */
    GPIO.PUPDR &=~(1UL<<(2*num_Pin));   /* desactivation resistance de tirage: bit à '0' */
    GPIO.OSPEEDR&=~(1UL<<((2*num_Pin)+1));  /* choix vitesse de sortie bit à '0' */
    GPIO.OSPEEDR|=(1UL<<(2*num_Pin));   /* choix vitesse de sortie  '0' */

	if(num_AF <= 7){
		if(num_AF & 1<<3)	GPIO.AFR[0] |= (1UL<<((4*num_AF)+3));
		else if(!(num_AF & 1<<3))	GPIO.AFR[0] &=~ (1UL<<((4*num_AF)+3));
		if(num_AF & 1<<2)	GPIO.AFR[0] |= (1UL<<((4*num_AF)+2));
		else if(!(num_AF & 1<<2))	GPIO.AFR[0] &=~ (1UL<<((4*num_AF)+2));
		if(num_AF & 1<<1)	GPIO.AFR[0] |= (1UL<<((4*num_AF)+1));
		else if(!(num_AF & 1<<1))	GPIO.AFR[0] &=~ (1UL<<((4*num_AF)+1));
		if(num_AF & 1<<0)	GPIO.AFR[0] |= (1UL<<(4*num_AF));
		else if(!(num_AF & 1<<0))	GPIO.AFR[0] &=~ (1UL<<(4*num_AF));
	}
	else {
		if((num_AF-8) & 1<<3)	GPIO.AFR[1] |= (1UL<<((4*(num_AF-8))+3));
		else if(!((num_AF-8) & 1<<3))	GPIO.AFR[1] &=~ (1UL<<((4*(num_AF-8))+3));
		if((num_AF-8) & 1<<2)	GPIO.AFR[1] |= (1UL<<((4*(num_AF-8))+2));
		else if(!((num_AF-8) & 1<<2))	GPIO.AFR[1] &=~ (1UL<<((4*(num_AF-8))+2));
		if((num_AF-8) & 1<<1)	GPIO.AFR[1] |= (1UL<<((4*(num_AF-8))+1));
		else if(!((num_AF-8) & 1<<1))	GPIO.AFR[1] &=~ (1UL<<((4*(num_AF-8))+1));
		if((num_AF-8) & 1<<0)	GPIO.AFR[1] |= (1UL<<(4*(num_AF-8)));
		else if(!((num_AF-8) & 1<<0))	GPIO.AFR[1] &=~ (1UL<<(4*(num_AF-8)));
	}
	/*switch(num_AF){
		case 0 :
			GPIO.AFR[0] &=~(1UL<<0);
	*/
}

void run(){
	while(code[pc]!= I_HALT){
		switch( code[pc] ){
			case I_PUSHI :  stack[++sp] = code[pc+1];
						    pc += 2;
						    printf("I_PUSHI\n"); 
						    break;
			case I_ADD :    stack[sp-1] += stack[sp];
						    pc += 1;
						    sp--;
						    printf("I_ADD\n");
						    break;
			case I_SUB : 	stack[sp-1] -= stack[sp];
							pc += 1;
							sp--;
							break;
			case I_MULT :   stack[sp-1] *= stack[sp];
						    pc += 1;
						    sp--;
						    printf("I_MULTI\n");
						    break;
			case I_DIV :	stack[sp-1] /= stack[sp];
							pc += 1;
							sp--;
							break;
			case I_NEG :	stack[sp] = -stack[sp];
							pc += 1;
							break;
			case I_AND :	stack[sp-1] = stack[sp] && stack[sp-1];
							pc += 1;
							sp--;
							break;
			case I_OR : 	stack[sp-1] = stack[sp] || stack[sp-1];
							pc += 1;
							sp--;
							break;
			case I_NOT :	stack[sp] = ~stack[sp];
							pc += 1;
							break;
			case I_LS :		if(stack[sp-1]<stack[sp]) stack[sp-1]=1;
							else stack[sp-1]=0;
							pc+=1;
							sp--;
							break;
			case I_GT :		if(stack[sp-1]>stack[sp]) stack[sp-1]=1;
							else stack[sp-1]=0;
							pc+=1;
							sp--;
							break;
			case I_PUSH :   stack[++sp] = variable[code[pc+1]];
						    pc += 2;
						    printf("I_PUSH\n");
						    break;
			case I_POP :    variable[code[pc+1]] = stack[sp-1];
							pc+=2;
							printf("I_POP\n");
							break;
			case I_EQ :     if(stack[sp] == stack[sp-1]) stack[sp-1] = 1;
							else stack[sp-1] = 0;
							sp--;
							pc++;
							printf("I_EQ\n");
							break;
			case I_JF :     if(stack[sp] == 1) pc+=2;
							else pc = code[pc+1];
							printf("I_JF\n");
							break;  
			case I_J :      pc = code[pc+1];
							printf("I_J\n");
							break;
		} 
		printf("stack : %d %d %d %d %d\n", stack[0], stack[1], stack[2], stack[3], stack[4]);
		printf("sp : %d\n", sp);
		printf("pc : %d\n", pc);
	}
	printf("I_HALT\n");
	printf("stack[sp] = %d \n",stack[sp]);
}

int main(int argc, char *argv[]){
	
	read_bin(argv[1]);
	Init_TIM15_CH1_Input_Capture_With_Interrupt ();
	TIM15->CR1 |=(1<<0); 							  // Start Timer TIM15
	Rapp_cycl=0;
	variable[0]=5;
	run();
	return 0;
}
