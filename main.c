#include "Extint.h"
#include "Buffer.h"
extern char flag;
//extern uint8_t bitcount;
 //uint8_t Character_Array[20];
//extern unsigned char unshifted[68][2];
int main()
{
	uint8_t i;
	GPIOSetDir(PORT0,22,OUTPUT);
	GPIOSetDir(PS2KEYBOARD_PORT,PS2_DATA_READ,INPUT);
	Interrupt_Pinsell_Init(1,INTERRUPT3_PIN0_30);
  Pll_Main(PLLCLOCK,Pclk_Same);
	Lcd_bit_Initial();
	External_Interrupt_Init(EGDE_SENSITIVE_LEVEL,FALLING_EDGE,INTERRUPT3,SLOT0);
	PrintF("ps2");
	
		
	while(1)
	{
	     if(Keyhit_Comparison())	
       {decode();
			 
			flag=0;
		}			

	}
}
