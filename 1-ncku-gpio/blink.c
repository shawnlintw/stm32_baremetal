#define GPIOG_MODER ( *((volatile unsigned long *) (0x40021800+ 0x0) ) )
#define GPIOG_OSPEEDR (*((volatile unsigned long *) (0x40021800+ 0x8) ) )
#define GPIOG_BSRR	( *((volatile unsigned long *) (0x40021800+ 0x18)) )
#define RCC_AHB1ENR	( *((volatile unsigned long *) (0x40023800+ 0x30)) )


void ResetISR(void);
void NMIException(void);
void HardFaultException(void);
void delay(void);

typedef 




asm(".word 0x20001000");
asm(".word main");

int main(){

	unsigned int c=0;

	RCC_AHB1ENR = (1<<6); 		/* GPIOGEN =1 */
	GPIOG_MODER = 0x14000000;   // set 13 and 14 be output mode.

	while(1){
		GPIOG_BSRR=(3<<13); 	/* ON  */
		for (c=0; c<500000; c++);
		GPIOG_BSRR= (3<<29); 	/* OFF */
		for (c=0; c<500000; c++);
	}
}

