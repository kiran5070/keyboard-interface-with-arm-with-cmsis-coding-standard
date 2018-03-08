#include "PS2keyboard.h"
#include "Buffer.h"

unsigned char Numlock_number[20][2]={0x4A,'/',
0x7c,'*',
0x7b,'-',
0x6c,'7',
0x75,'8',
0x7d,'9',
0x79,'+',
0x6b,'4',
0x73,'5',
0x74,'6',
0x69,'1',
0x72,'2',
0x7a,'3',
0x70,'0',
0x71,'.'};
unsigned char unshifted[68][2] = {0x0d,'9',
0x0e,'|',
0x15,'q',
0x16,'1',
0x1a,'z',
0x1b,'s',
0x1c,'a',
0x1d,'w',
0x1e,'2',
0x21,'c',
0x22,'x',
0x23,'d',
0x24,'e',
0x25,'4',
0x26,'3',
0x29,' ',
0x2a,'v',
0x2b,'f',
0x2c,'t',
0x2d,'r',
0x2e,'5',
0x31,'n',
0x32,'b',
0x33,'h',
0x34,'g',
0x35,'y',
0x36,'6',
0x39,',',
0x3a,'m',
0x3b,'j',
0x3c,'u',
0x3d,'7',
0x3e,'8',
0x41,',',
0x42,'k',
0x43,'i',
0x44,'o',
0x45,'0',
0x46,'9',
0x49,'.',
0x4a,'-',
0x4b,'l',
0x4c,'ø',
0x4d,'p',
0x4e,'+',
0x52,'æ',
0x54,'å',
0x55,'\\',
0x5a,13,
0x5b,'¨',
0x5d,'\\',
0x61,'<',
0x66,'8',
0,0
};
unsigned char shifted[68][2] = {
	0x0d,9,
0x0e,'§',
0x15,'Q',
0x16,'!',
0x1a,'Z',
0x1b,'S',
0x1c,'A',
0x1d,'W',
0x1e,'"',
0x21,'C',
	0x22,'X',
0x23,'D',
0x24,'E',
0x25,'¤',
0x26,'#',
0x29,' ',
0x2a,'V',
0x2b,'F',
0x2c,'T',
0x2d,'R',
0x2e,'%',
0x31,'N',
0x32,'B',
0x33,'H',
0x34,'G',
0x35,'Y',
0x36,'&',
0x39,'L',
0x3a,'M',
0x3b,'J',
0x3c,'U',
0x3d,'/',
0x3e,'(',
0x41,';',
0x42,'K',
0x43,'I',
0x44,'O',
0x45,'=',
0x46,')',
0x49,':',
0x4a,'_',
0x4b,'L',
0x4c,'Ø',
0x4d,'P',
0x4e,'?',
0x52,'Æ',
0x54,'Å',
0x55,'`',
0x5a,13,
0x5b,'^',
0x5d,'*',
0x61,'>',
0x66,8,
0,0
};
static char i=0;
 char flag=0;
  uint8_t bitcount=0,CmtCnt=0,send=0,AckFlag=0,FrameCount=0;
uint8_t Character_Array[20];
uint8_t ledCmd[5] ={0xED,0x04,0x00,0x02,0x06};
__irq void Ps2keyboard_Interrupt(void)
{
	
	static uint8_t byte=0x00;
  
	static uint8_t parityval=0;
	static uint8_t read,read_int;
	
	if(send)
	{
	
		SendCmd(); //for cap and num it wil true
		           
	}
	else
	{
	GPIOSetVal(PORT0,22,HIGH);
	read=GPIOGetVal(PS2KEYBOARD_PORT,PS2_DATA_READ);
		read_int=GPIOGetVal(PS2KEYBOARD_PORT,PS2_INT_PIN);
	bitcount++;

	//if(bitcount>32)
		//flag=1;
	
	
	switch(bitcount)
	{
		case START              : byte=0x00;
		                          if(!(read==0 && read_int==0))		                        
			                        bitcount=0;
		
		                          break;
		case PARITY_BIT         : parityval=read;
                              break;
    case STOP               : Buffer_Write(byte);
		                           
		                          
		                          bitcount=0;
                              flag=1;
                              break;
		
    default                 : byte=byte>>1;
                              if(read)
                              byte=byte|0x80;	
                              break;														
	} 
   GPIOSetVal(PORT0,22,LOW);
 
}
 EXTINT=(1<<3);
	VICVectAddr=0;
}
void decode()
{
	uint8_t read_byte,shiftcapnum=0;
	
	static uint8_t is_up=0,shift=0,mode=0,cap=0,num=0;
	uint8_t i;
	
	Buffer_Read(&read_byte);
	if(!is_up)
	{
		
		switch(read_byte)
		{
			case BREAK_CODE    : is_up=1; 
			                     break;
			case LEFT_SHIFT    : shift=1;
			                     break;
			case RIGHT_SHIFT   : shift=1;
			                     break;
			case CAP           : cap^=1;
			                     CmtCnt=0;
			                     AckFlag=0;
			                     send=1;
			                     StartCmd();
									         break;
      case NUM           : num^=1;
                           CmtCnt=0;   //normaly it will zero because first data will be 0xed after that only the real data will send
			                     AckFlag=0;
			                     send=1;     //if it press send fun become one and sendcomand fun will work
                           StartCmd(); // it comtain the instruction to send data to keyboard			
										       break;
      case ACK           : AckFlag++; // if we get ed keybaord send a ackflag[oxfa],next case in cap or num data also ,after it reach it will send a 0xfa-ack
			                     
			                     if(cap && num && (AckFlag<2)) /*here we are checking ackflag<2,beacause once ed pass we get ack value will be 1,then condtion check and send again the data of cap or num.  
                                                          *backwise steps after ed it will send cap or num to keybaord after that keybaord give a ack at tat time ,it no need to work tat conditon again,at tat time ack value will be zero */     
														{ 
													 CmtCnt=4;               
														 send=1;
														 StartCmd();
													 }
													 else if((!cap) && num && (AckFlag<2))
													 {
														 CmtCnt=3;                 
														 send=1;
														 StartCmd();
													 }
													 else if(cap && (!num) && (AckFlag<2))
													 { 
														                                   
														 CmtCnt=1;
														 send=1;
														 StartCmd();
													 }
													 else if((!cap)&& (!num) && (AckFlag<2))
													 {
														 CmtCnt=2;
														 send=1;                     
														 StartCmd();
													 }
													 else
													 {send=0;}
													 break;
                           			
			default   :       //last threebit tuk as bit for num,cap,shift.that value will change according to the on and off
                   //shiftcapnum=shift*100+cap*10+num;
			             if(shift)
                   shiftcapnum|=(1<<2);
                   else
                   shiftcapnum&=~(1<<2);

                   if(cap)
                   shiftcapnum|=(1<<1);
									 else
									 shiftcapnum&=~(1<<1);
									 
									 if(num)
									 shiftcapnum|=(1<<0);
									 else
									 shiftcapnum&=~(1<<0);
									 
                   switch(shiftcapnum)
                   {
										 case 0x0 :for(i=0;unshifted[i][0]!=read_byte && unshifted[i][0];i++);
										           if(unshifted[i][0]==read_byte)
										           Lcd_putchar(unshifted[i][1]);
															 break;
										 case 0x1 :for(i=0;unshifted[i][0]!=read_byte && unshifted[i][0];i++);
										           if(unshifted[i][0]==read_byte)
											         Lcd_putchar(unshifted[i][1]);
										
										
										           for(i=0;Numlock_number[i][0]!=read_byte && Numlock_number[i][0];i++);
										           if(Numlock_number[i][0]==read_byte)
											         Lcd_putchar(Numlock_number[i][1]);
															 break;
															 
										 case 0x4 :for(i=0;shifted[i][0]!=read_byte && shifted[i][0];i++);
										           if(shifted[i][0]==read_byte)
										           Lcd_putchar(shifted[i][1]);
															 break;
										 case 0x5 :for(i=0;shifted[i][0]!=read_byte && shifted[i][0];i++);
										           if(shifted[i][0]==read_byte)
										           Lcd_putchar(shifted[i][1]);
											
											
										           for(i=0;Numlock_number[i][0]!=read_byte && Numlock_number[i][0];i++);
										           if(Numlock_number[i][0]==read_byte)
											         Lcd_putchar(Numlock_number[i][1]);
															 break;
										 case 0x2 :
											         for(i=0;shifted[i][0]!=read_byte && shifted[i][0];i++);
										           if(shifted[i][0]==read_byte)
										           Lcd_putchar(shifted[i][1]);
															 break;
										 case 0x3 :for(i=0;shifted[i][0]!=read_byte && shifted[i][0];i++);
										           if(shifted[i][0]==read_byte)
										           Lcd_putchar(shifted[i][1]);
											
											
										           for(i=0;Numlock_number[i][0]!=read_byte && Numlock_number[i][0];i++);
										           if(Numlock_number[i][0]==read_byte)
											         Lcd_putchar(Numlock_number[i][1]);	
															 break;
										 case 0x6 :for(i=0;unshifted[i][0]!=read_byte && unshifted[i][0];i++);
										           if(unshifted[i][0]==read_byte)
										           Lcd_putchar(unshifted[i][1]);
															 break;
										 case 0x7 :for(i=0;unshifted[i][0]!=read_byte && unshifted[i][0];i++);
										           if(unshifted[i][0]==read_byte)
										           Lcd_putchar(unshifted[i][1]);
										
											         for(i=0;Numlock_number[i][0]!=read_byte && Numlock_number[i][0];i++);
										           if(Numlock_number[i][0]==read_byte)
											         Lcd_putchar(Numlock_number[i][1]);
                               break;															 
                   }
                   									 
//				          if(shift==0 && cap==0 && num==0)
//			            {
//                    for(i=0;unshifted[i][0]!=read_byte && unshifted[i][0];i++);
//										if(unshifted[i][0]==read_byte)
//										Lcd_putchar(unshifted[i][1]);
//											
//									}
//				
//									else if(shift==0 && cap==0 && num==1)
//			            {
//										
//										
//                    for(i=0;unshifted[i][0]!=read_byte && unshifted[i][0];i++);
//										if(unshifted[i][0]==read_byte)
//											Lcd_putchar(unshifted[i][1]);
//										
//										
//										for(i=0;Numlock_number[i][0]!=read_byte && Numlock_number[i][0];i++);
//										if(Numlock_number[i][0]==read_byte)
//											Lcd_putchar(Numlock_number[i][1]);
//									}
//									
//									else if(shift==1 && cap==0 && num==0)
//									{
//										for(i=0;shifted[i][0]!=read_byte && shifted[i][0];i++);
//										if(shifted[i][0]==read_byte)
//										Lcd_putchar(shifted[i][1]);
//											
//											
//											
//									}
//									else if(shift==1 && cap==0 && num==1)
//									{
//											for(i=0;shifted[i][0]!=read_byte && shifted[i][0];i++);
//										if(shifted[i][0]==read_byte)
//										Lcd_putchar(shifted[i][1]);
//											
//											
//										for(i=0;Numlock_number[i][0]!=read_byte && Numlock_number[i][0];i++);
//										if(Numlock_number[i][0]==read_byte)
//											Lcd_putchar(Numlock_number[i][1]);
//									}
//									else if(shift==0 && cap==1 && num==0)
//									{
//										for(i=0;shifted[i][0]!=read_byte && shifted[i][0];i++);
//										if(shifted[i][0]==read_byte)
//										Lcd_putchar(shifted[i][1]);
//											
//									}
//									else if(shift==0 && cap==1 && num==1)
//									{
//										for(i=0;shifted[i][0]!=read_byte && shifted[i][0];i++);
//										if(shifted[i][0]==read_byte)
//										Lcd_putchar(shifted[i][1]);
//											
//											
//										for(i=0;Numlock_number[i][0]!=read_byte && Numlock_number[i][0];i++);
//										if(Numlock_number[i][0]==read_byte)
//											Lcd_putchar(Numlock_number[i][1]);	
//									}
//									
//									else if(shift==1 && cap==1 && num==0)
//									{
//										for(i=0;unshifted[i][0]!=read_byte && unshifted[i][0];i++);
//										if(unshifted[i][0]==read_byte)
//										Lcd_putchar(unshifted[i][1]);
//											
//									}
//									else if(shift==1 && cap==1 && num==1)
//									{
//										for(i=0;unshifted[i][0]!=read_byte && unshifted[i][0];i++);
//										if(unshifted[i][0]==read_byte)
//										Lcd_putchar(unshifted[i][1]);
//										
//											for(i=0;Numlock_number[i][0]!=read_byte && Numlock_number[i][0];i++);
//										if(Numlock_number[i][0]==read_byte)
//											Lcd_putchar(Numlock_number[i][1]);	
//									}
                     										
		}
  }

else
{
	 is_up=0;
   switch(read_byte)
   {
	 case LEFT_SHIFT : shift=0;break;
	 case RIGHT_SHIFT : shift=0;break;
   }
 }	 

}
void StartCmd()
{
	GPIOFuncSel(PS2KEYBOARD_PORT,PS2_INT_PIN,FUNC0); //according to the algorithm we have to make it low for 100..so before that we should make it output[mc to keybord]
	GPIOSetDir(PS2KEYBOARD_PORT,PS2_INT_PIN,OUTPUT); //interrupt pin become output
	GPIOSetDir(PS2KEYBOARD_PORT,PS2_DATA_READ,OUTPUT); //data pine become output
	GPIOSetVal(PS2KEYBOARD_PORT,PS2_INT_PIN,LOW); //algorithm step one : make the clock low for 100 sec
	delay(100);
	GPIOSetVal(PS2KEYBOARD_PORT,PS2_DATA_READ,LOW); //bring the data line low
	delay(100);
	GPIOSetVal(PS2KEYBOARD_PORT,PS2_INT_PIN,HIGH); //realease the clock line or make it high
	FrameCount=0;
//after this step keyboard send a clock that shows it is reaDY.so we should make the interrupt to find clock
	Interrupt_Pinsell_Init(1,INTERRUPT3_PIN0_30); //then interrupt will come ,it jumb to interrupt function
}
void SendCmd()
{
  
	switch(FrameCount)
	{  
		case CMD_PARITY_BIT    :  switch(CmtCnt)
		                          {	
																//according to no of one parity is set
																case 0: GPIOSetVal(PS2KEYBOARD_PORT,PS2_DATA_READ,HIGH); 
																        break;
																case 1: GPIOSetVal(PS2KEYBOARD_PORT,PS2_DATA_READ,LOW);
																        break;
																case 2: GPIOSetVal(PS2KEYBOARD_PORT,PS2_DATA_READ,HIGH);
																        break;
															  case 3: GPIOSetVal(PS2KEYBOARD_PORT,PS2_DATA_READ,LOW);
																        break;
																case 4: GPIOSetVal(PS2KEYBOARD_PORT,PS2_DATA_READ,HIGH);
																        break;
	                            }
															break;
	 case CMD_STOP_BIT       :  GPIOSetVal(PS2KEYBOARD_PORT,PS2_DATA_READ,HIGH);//" algo-9"          
                              GPIOSetDir(PS2KEYBOARD_PORT,PS2_DATA_READ,INPUT); //make it input because keybaord will give a ack represent we get 8 bit of ed,next case corresponding value of cap or num
                              break;
   case CMD_ACK            : 	send=0; //just read that ack value and make send zero to workaa the else condition in isr
                              break;	
   default                 :  /* "algotith 5"eg: in the case capslock first valur that we gonna send ED.it will send bit by bit
		                          *after bit pass in each clock that will work as interrupt*/
		                          if((ledCmd[CmtCnt]>>(FrameCount))&0x01)  //extract eacch data from first side
                              GPIOSetVal(PS2KEYBOARD_PORT,PS2_DATA_READ,HIGH); //it the data is 1 ,mc make dataline high
                              else 
                              GPIOSetVal(PS2KEYBOARD_PORT,PS2_DATA_READ,LOW);  //if it is 0 data line make to low
															break; //after 8 bit it will partiy
 }
  FrameCount++;  
}                              