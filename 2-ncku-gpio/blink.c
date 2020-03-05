#define GPIOG_MODER ( *((volatile unsigned long *) (0x40021800+ 0x0) ) )
#define GPIOG_OSPEEDR (*((volatile unsigned long *) (0x40021800+ 0x8) ) )
#define GPIOG_BSRR	( *((volatile unsigned long *) (0x40021800+ 0x18)) )
#define RCC_AHB1ENR	( *((volatile unsigned long *) (0x40023800+ 0x30)) )

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
	{1,0},
	{0,1},
	{1,0},
	{0,1},
};

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
	}
}
