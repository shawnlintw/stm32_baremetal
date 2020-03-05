#define GPIOG_MODER ( *((volatile unsigned long *) (0x40021800+ 0x0) ) )
#define GPIOG_OSPEEDR (*((volatile unsigned long *) (0x40021800+ 0x8) ) )
#define GPIOG_BSRR	( *((volatile unsigned long *) (0x40021800+ 0x18)) )
#define RCC_AHB1ENR	( *((volatile unsigned long *) (0x40023800+ 0x30)) )


void ResetISR(void);
void NMIException(void);
void HardFaultException(void);
void delay(void);

typedef void (*pfnISR)(void); 		// Pointer to exception handle function


__attribute__ ((section(".isr_vector")))
pfnISR VectorTable[] =
{
	(pfnISR) (0x20010000),			// The initial stack pointer is the top of SRAM
	ResetISR,						// The reset handler
	NMIException,
	HardFaultException
};

void delay(void)
{
	unsigned int i;
	for (i=0; i<500000; i++)
	{
		asm("nop");
	}
}

int leds[4][2] =
{
	{0,0},
	{0,1},
	{1,1},
	{1,0},
};


//asm(".word 0x20001000");
//asm(".word main");

int main(){

	int i=0;
	int c=0;
	RCC_AHB1ENR = (1<<6); 		/* GPIOGEN =1 */
	GPIOG_MODER = 0x14000000;   // set 13 and 14 be output mode.

	while(1){
		
		for(i=0; i<4; i++)
		{
			if (leds[i][0] ==0)
			{
				GPIOG_BSRR = (1<<13);
			}
			else
			{
				GPIOG_BSRR = (1<<29);
			}

			if (leds[i][1]==0)
			{
				GPIOG_BSRR = (1<<14);
			}
			else
			{
				GPIOG_BSRR = (1<<30);
			}
			delay();
		}

		//GPIOG_BSRR=(1<<14); 	/* ON  */
		//for (c=0; c<500000; c++);
		//GPIOG_BSRR= (1<<30); 	/* OFF */
		//for (c=0; c<500000; c++);
		
	}
}

/*
* The following are constructs created by the linker, indicating where the "data"
* and "bss" segments reside in memory. The initializers for the "data" segment 
* resides immediately following the "text" segment.
*/
extern unsigned long _etext;
extern unsigned long _data;
extern unsigned long _edata;
extern unsigned long _bss;
extern unsigned long _ebss;

void ResetISR(void)
{
	unsigned long *src, *dst;


	/* Copy the segment initializers from flash to SRAM. */

	src = &_etext;
	dst = &_data;
	while (dst < &_edata)
	{
		*dst++ = *src++;
	}

	/* Zero fill the bss segment */

	for(dst = &_bss; dst < &_ebss; dst++)
	{
		*dst =0;
	}

	/* Call the application's entry point. */
	main();
}
void NMIException(void)
{
	return;
}

void HardFaultException(void)
{
	return;
}
