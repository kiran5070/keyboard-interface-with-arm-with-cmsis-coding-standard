#ifndef __ExtInt_h
#define __ExtInt_h
#include <stdarg.h>
#include "PS2keyboard.h"
#define VIC_INTERRUPT0 14
#define VIC_INTERRUPT1 15
#define VIC_INTERRUPT2 16
#define VIC_INTERRUPT3 17
#define INTERRUPT0 0
#define INTERRUPT1 1
#define INTERRUPT2 2
#define INTERRUPT3 3
#define INTERRUPT_INT_PIN 14
#define EGDE_SENSITIVE_LEVEL 1
#define LEVEL_SENSITIVE 0
#define RISING_EDGE 1
#define FALLING_EDGE 0
#define HWDR_VICVECTCNT(SLOT) *(&VICVectCntl0+SLOT)
#define HWDR_VICVECTADDR(SLOT) *(&VICVectAddr0+SLOT)
#define INTERRUPT0_PIN0_1 1
#define INTERRUPT1_PIN0_3 3
#define INTERRUPT2_PIN0_7 7
#define INTERRUPT3_PIN0_9 9
#define INTERRUPT1_PIN0_14 14
#define INTERRUPT2_PIN0_15 15
#define INTERRUPT0_PIN0_16 16
#define INTERRUPT3_PIN0_20 20
#define INTERRUPT3_PIN0_30 30
enum SLOT {SLOT0,SLOT1,SLOT2,SLOT3,SLOT4,SLOT5,SLOT6,SLOT7,SLOT8,SLOT9,SLOT10,SLOT11,SLOT12,SLOT13,SLOT14,SLOT15,SLOT16};

void Interrupt_Pinsell_Init(int Interrupt_Count,...);
void External_Interrupt_Init(char level_Mode,char Rise_or_fall,char Interrupt_Sel,char slot);
void External_Vic_Init(char Interrupt_Sel,char slot);
__irq void Ext_Int(void);




#endif
