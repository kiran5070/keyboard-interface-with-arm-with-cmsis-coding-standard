#ifndef __PLLSET_H
#define __PLLSET_H
#include <lpc214x.h>

#define PLLCLOCK 60
#define Pclk_One_Fourth 0
#define Pclk_Same 1
#define Pclk_Half 2
#define PLOCK 0x400 



void Pll_Setup(char Clock_Freq);
void Feed_Set(void);
void Pll_Connect(void);
void Pll_Main(char Clock_Freq,char PCLK_Sel );









#endif
