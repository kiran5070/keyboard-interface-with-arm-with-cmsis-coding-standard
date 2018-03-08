#include "Buffer.h"
char Data_Buffer[128];
 char Write_index=0,Read_index=0;
void Buffer_Write(char Data_to_Buf)
{
	
	Data_Buffer[Write_index]=Data_to_Buf;
	Write_index++;
	Write_index&=127; //write upto the size,it is equalent to for(i=0;i<128;i++)
}
void Buffer_Read(unsigned char* Data_from_Buffer)
{
	static char i=0;
	*Data_from_Buffer=Data_Buffer[Read_index];
   Read_index++;
  Read_index&=127; 
}
char Keyhit_Comparison(void)
{
	if(Write_index==Read_index)
		return 0;
	else
		return 1;
}