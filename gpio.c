#include "gpio.h"

void GPIOFuncSel(uint8_t Portnum, uint8_t Pinnum, uint8_t Func)
{
	uint8_t pinsel =0;
    if(Portnum==PORT0)
		{
			if(Pinnum>=16)
			{
				Pinnum=Pinnum-16;
				pinsel++;
	    } 
			Pinnum=Pinnum*2;
			if(pinsel==0)
         PINSEL0 = (PINSEL0&(~FUNC3)<<Pinnum)|Func<<Pinnum;
			
      else
				 PINSEL1 = (PINSEL1&(~FUNC3)<<Pinnum)|Func<<Pinnum;
    }	
		else if(Portnum==PORT1)
	      PINSEL2 |= (PINSEL2&(~FUNC3)<<Pinnum)|Func<<Pinnum;
}

void GPIOSetDir(uint8_t Portnum, uint8_t Pinnum, uint8_t Dirn)
{
	  switch(Portnum)
	  {
      case PORT0:
				  if(Dirn==OUTPUT)
						IODIR0 |= 1<<Pinnum;
					else
						IODIR0 &= ~(1<<Pinnum);
      break;

      case PORT1:
         	 if(Dirn==OUTPUT)
						IODIR1 |= 1<<Pinnum;
					else
						IODIR1 &= ~(1<<Pinnum);
			break;
   }
}

void GPIOSetVal(uint8_t Portnum, uint8_t Pinnum, uint8_t Value)
{
	  switch(Portnum)
	  {
			case PORT0:				
				if(Value==HIGH)
					IOSET0 |= 1<<Pinnum;
				else
					IOCLR0 |= 1<<Pinnum;
				
			break;
				
			case PORT1:
				  if(Value==HIGH)
				  IOSET1 |= 1<<Pinnum;
				else
					IOCLR1 |= 1<<Pinnum;
			break;
		}
}		
void GPIOSetBusVal(uint8_t Portnum, uint8_t Pinnum, uint8_t BusValue)
{
	  switch(Portnum)
	  {
			case PORT0:
				  IOCLR0 |= 0xFF<<Pinnum;
				  IOSET0 |= BusValue<<Pinnum;
			 break;
			case PORT1:
				  IOCLR1 |= 0xFF<<Pinnum;
				  IOSET1 |=BusValue<<Pinnum;
			break;
		}
}		
void GPIOSet_4bit_BusVal(uint8_t Portnum, uint8_t Pinnum, uint8_t BusValue)
{
	switch(Portnum)
	  {
			case PORT0:
				  IOCLR0 |= 0xF<<Pinnum;
				  IOSET0 |= BusValue<<Pinnum;
			 break;
			case PORT1:
				  IOCLR1 |= 0xF<<Pinnum;
				  IOSET1 |=BusValue<<Pinnum;
			break;
		}
	
}

uint8_t GPIOGetVal(uint8_t Portnum, uint8_t Pinnum)
{
    uint32_t read;
	
	 if(Portnum==PORT0)
	  read = IOPIN0 &(1<<Pinnum);
	 else
		read = IOPIN1 &(1<<Pinnum);
   
	 if(read)
		 return HIGH;
	 else 
		 return LOW;
}	
	
void delay(uint32_t count)
{
	int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<1000;j++);
}






