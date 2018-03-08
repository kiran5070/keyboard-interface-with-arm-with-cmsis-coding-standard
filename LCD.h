#ifndef __LCD_h
#define __LCD_h

#include "gpio.h"
#include <stdarg.h>
#include <stdio.h>

#define LCD_4BIT 1
#define LCD_8BIT 0

#define x 0
#define y 1

#define LCDPORT PORT0
#define GPIOFunc FUNC0
#define LCDCONTROL PORT0
#define COMMAND 0
#define DATA 1


#define LCD_RS PIN_NUM12
#define LCD_EN PIN_NUM13

void Lcd_bit_Initial(void);
void Lcd_putchar(char data);
void Lcd_putstring(char *strings);
void Custom_Char_Send(void);
void gotoXorY(char pos,char Com);
void PrintF(char *,...);
char* convert(unsigned int, int);

#endif
