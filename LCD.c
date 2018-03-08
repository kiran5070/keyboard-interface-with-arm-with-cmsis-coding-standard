#include "LCD.h"
char customChar[4][8] = { 
		                      0x04,0x0A,0x15,0x0A,0x04,0x00,0x00,0x00,
                          0x04,0x0A,0x15,0x0A,0x04,0x00,0x00,0x00,
		                      0x04,0x0A,0x15,0x0A,0x04,0x00,0x00,0x00,
                          0x04,0x0A,0x15,0x0A,0x04,0x00,0x00,0x00};
void Lcd_bit_Write(char type,char input_data);
void Floattostring(double g);
char str[20];
void Lcd_bit_Initial(void)
{  
	char datapin;
	  GPIOFuncSel(LCDCONTROL,LCD_RS,GPIOFunc);
		GPIOSetDir(LCDCONTROL,LCD_RS,OUTPUT);
    GPIOFuncSel(LCDCONTROL,LCD_EN,GPIOFunc);
		GPIOSetDir(LCDCONTROL,LCD_EN,OUTPUT);			
	
	#if LCD_8BIT
	for(datapin=PIN_NUM16;datapin<PIN_NUM20;datapin++)
	{
	  GPIOFuncSel(LCDPORT,datapin,GPIOFunc);
		GPIOSetDir(LCDPORT,datapin,OUTPUT);		
	}
  #endif
	for(datapin=PIN_NUM15;datapin<PIN_NUM19;datapin++)
	{
	  GPIOFuncSel(LCDPORT,datapin,GPIOFunc);
		GPIOSetDir(LCDPORT,datapin,OUTPUT);		
	}
		
	#if LCD_8BIT
	GPIOSetBusVal(LCDPORT,PIN_NUM16,0x00);		
	Lcd_bit_Write(COMMAND,0x38);
	#elif LCD_4BIT
  GPIOSet_4bit_BusVal(LCDPORT,PIN_NUM15,0x00);
	Lcd_bit_Write(COMMAND,0x33);
	Lcd_bit_Write(COMMAND,0x32);
	Lcd_bit_Write(COMMAND,0x28);
	#endif
	Lcd_bit_Write(COMMAND,0x01);
  Lcd_bit_Write(COMMAND,0x0E);
	Lcd_bit_Write(COMMAND,0x06);
	Lcd_bit_Write(COMMAND,0x80);	
}

void Lcd_bit_Write(char type,char input_data)
{
	volatile char temp;
	  
	  GPIOSetVal(LCDCONTROL,LCD_RS,type);
	  #if LCD_8BIT
	  GPIOSetBusVal(LCDPORT,PIN_NUM16,input_data);
    #elif LCD_4BIT
 	  temp=input_data;	
    temp=(temp & 0xF0)>>4;
    GPIOSet_4bit_BusVal(LCDPORT,PIN_NUM15,temp);
	  GPIOSetVal(LCDCONTROL,LCD_EN,HIGH);
    delay(300);
    GPIOSetVal(LCDCONTROL,LCD_EN,LOW);
	
  	temp=(input_data & 0x0F);
    GPIOSet_4bit_BusVal(LCDPORT,PIN_NUM15,temp);
	  #endif
    GPIOSetVal(LCDCONTROL,LCD_EN,HIGH);
    delay(300);
    GPIOSetVal(LCDCONTROL,LCD_EN,LOW);	
}	

void Lcd_putstring(char *strings)
{
	while(*strings)
	{
		Lcd_putchar(*strings++);
	}
}

void Lcd_putchar(char data)
{
		Lcd_bit_Write(DATA,data);
}
void Custom_Char_Send()
{
	
		uint32_t i,j;
	for(j=0;j<4;j++) //three memory available 
	{
		i=0;
		Lcd_bit_Write(COMMAND,0x40+j*8);
		while(i<8)
		{
			Lcd_putchar(customChar[j][i]);
			delay(800);
			i++;
		}
	}
}
void gotoXorY(char pos,char Com)
{
	switch(pos)
	{
	 case 0  : Lcd_bit_Write(COMMAND,(0X80+Com));
		         break;
	 case 1  : Lcd_bit_Write(COMMAND,(0xC0+Com));
		         break;
	}	
}
void PrintF(char* format,...)
{
	char *Increment;
	char *s;
	int i,num;
	double k;
	va_list FirstLoc;
	va_start(FirstLoc,format);
	for(Increment= format; *Increment!='\0'; Increment++)
	{
		  if(*Increment!='%')
			{ 
				Lcd_putchar(*Increment);
			}
			  
			else
			{				
			  Increment++;
				if(*Increment== '1' || *Increment== '2' || *Increment =='3' || *Increment=='4' || *Increment== '5' || *Increment=='6' || *Increment=='7' || *Increment=='8' || *Increment=='9')
        {
					num=*Increment-0x30;
          for(i=1;i<=num;i++)
          {
					 Lcd_putchar(' ');
          }					 
			    Increment++;
				}
				switch(*Increment)
				{
					 case 'c' : i=va_arg(FirstLoc,int);
					                     Lcd_putchar(i);
					                     break;
					 case 'd' : i=va_arg(FirstLoc,int);
															 if(i<0)
															 {
																 i=-i;
																 Lcd_putchar('-');
															 }
															 Lcd_putstring(convert(i,10));
                               break;														 
					case 'o'  : i=va_arg(FirstLoc,unsigned int);
															 Lcd_putstring(convert(i,8));
															 break;
					case 's'  : s=va_arg(FirstLoc,char *);
               				         Lcd_putstring(s);
                               break;	
          case 'x'  : i=va_arg(FirstLoc,unsigned int);
                               Lcd_putstring(convert(i,16));
                               break;
          case 'f'  : k=va_arg(FirstLoc,double);
															 Floattostring(k);
															 Lcd_putstring(str);
															 break;
                               															 
			  }
	     }	
    }
          va_end(FirstLoc);
}
char* convert(unsigned int num, int base)
{
	    static char Representation[]= "0123456789ABCDEF";
	    static char buffer[50]; 
	    char *ptr; 
	
	    ptr = &buffer[49]; 
	    *ptr = '\0';
      do 
	    { 
		    *--ptr = Representation[num%base]; 
		    num /= base; 
	    }while(num> 0); 
	
	    return(ptr); 
}
void Floattostring(double g)
{
	
	sprintf(str,"%F",g);
	
}

	

