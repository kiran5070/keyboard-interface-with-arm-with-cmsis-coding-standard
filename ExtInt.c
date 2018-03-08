#include "ExtInt.h"
#include "gpio.h"
int i;
void Interrupt_Pinsell_Init(int Interrupt_Count,...)
{
	int pinsel;
	va_list Location;
	va_start(Location,Interrupt_Count);
	while(Interrupt_Count--)
	{
		pinsel=va_arg(Location,int);
		switch(pinsel)
		{
			case INTERRUPT0_PIN0_1 :GPIOFuncSel(PORT0,INTERRUPT0_PIN0_1,FUNC3);
			                        
                              break;			
			case INTERRUPT1_PIN0_3 :GPIOFuncSel(PORT0,INTERRUPT1_PIN0_3,FUNC3);
			                        
                              break;			
			case INTERRUPT2_PIN0_7 :GPIOFuncSel(PORT0,INTERRUPT2_PIN0_7,FUNC3);
			                        
                              break;
      case INTERRUPT3_PIN0_9 :GPIOFuncSel(PORT0,INTERRUPT3_PIN0_9,FUNC3);
			                        
                              break;
      case INTERRUPT1_PIN0_14:GPIOFuncSel(PORT0,INTERRUPT1_PIN0_14,FUNC2);
			                        
                              break;
      case INTERRUPT2_PIN0_15:GPIOFuncSel(PORT0,INTERRUPT2_PIN0_15,FUNC2);
			                        
                              break;						
      case INTERRUPT0_PIN0_16:GPIOFuncSel(PORT0,INTERRUPT0_PIN0_16,FUNC1);
			                        
                              break;
			case INTERRUPT3_PIN0_20:GPIOFuncSel(PORT0,INTERRUPT3_PIN0_20,FUNC3);
			                        
                              break;
			case INTERRUPT3_PIN0_30:GPIOFuncSel(PORT0,INTERRUPT3_PIN0_30,FUNC2);
			                        
                              break;
      			
		}
		
	}
	
}
void External_Interrupt_Init(char level_Mode,char Rise_or_fall,char Interrupt_Selection,char slot)
{ 
	char Vic_Interrupt;
	EXTINT|=(1<<Interrupt_Selection);
	switch(Interrupt_Selection)
	{
		case INTERRUPT0 :Vic_Interrupt=VIC_INTERRUPT0;
                     break;
    case INTERRUPT1 :Vic_Interrupt=VIC_INTERRUPT1;
                     break;
    case INTERRUPT2 :Vic_Interrupt=VIC_INTERRUPT2;
                     break;
    case INTERRUPT3 :Vic_Interrupt=VIC_INTERRUPT3;
                     break;		
	}           
	if(level_Mode==EGDE_SENSITIVE_LEVEL)
		EXTMODE=(1<<Interrupt_Selection);
	else
		EXTMODE&=~(1<<Interrupt_Selection);
	
	if(Rise_or_fall==FALLING_EDGE)	
	  EXTPOLAR&=~(1<<Interrupt_Selection);
	else
		EXTPOLAR=(1<<Interrupt_Selection);
	
	External_Vic_Init(Vic_Interrupt,slot);
	//EXTINT|=(1<<0);
	
}
	
void External_Vic_Init(char Interrupt_Sel,char slot)
{
	VICIntSelect&=~(1<<Interrupt_Sel);
	HWDR_VICVECTADDR(slot)=(unsigned int)Ps2keyboard_Interrupt;
	HWDR_VICVECTCNT(slot)=(1<<5)|Interrupt_Sel;
	VICIntEnable=(1<<Interrupt_Sel);
	
}
__irq void Ext_Int(void)
{
	i=0;
	while(i<8)
	{
	GPIOSetVal(PORT0,PIN_NUM22,HIGH);
	delay(1000);
	GPIOSetVal(PORT0,PIN_NUM22,LOW);
	delay(1000);i++;}
	
	EXTINT|=(1<<0);
	VICVectAddr=0;
	
}
