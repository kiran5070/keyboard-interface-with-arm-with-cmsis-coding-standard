#include "PLLSET.h"


void Pll_Setup(char Clock_Freq)
{
	PLL0CON = 0x01;
	switch(Clock_Freq)
	  {
			case 60     :   PLL0CFG = 0x24;
			                break;
			case 12     :   PLL0CFG = 0x60;
			                break;
			case 24     :   PLL0CFG = 0x41;
			                break;
			case 36     :   PLL0CFG = 0x42;
			                break;
			case 48     :   PLL0CFG = 0x23;
			                break;
		}
}
void Feed_Set(void)
{
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;

}
void Pll_Connect(void)
{
	while( !( PLL0STAT & PLOCK ));
  PLL0CON = 0x03;

}
void Pll_Main(char Clock_Freq,char PCLK_Sel )
{
	Pll_Setup(Clock_Freq);
	Feed_Set();
	Pll_Connect();
	Feed_Set();
	switch(PCLK_Sel)
	  {
			case 0     :    VPBDIV=0x00;
			                break;
			case 1     :    VPBDIV=0x01;
			                break;
			case 2     :    VPBDIV=0x02;
			                break;
		}
	
}

