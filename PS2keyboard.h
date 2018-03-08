#ifndef __PS2keyboard_h
#define __PS2keyboard_h
#include "gpio.h"
#include "LCD.h"
#include "PLLSET.h"
#include "Buffer.h"
#include "ExtInt.h"
#define START 1
#define PARITY_BIT 10
#define STOP 11
#define PS2KEYBOARD_PORT 0
#define PS2_DATA_READ 21
#define PS2_INT_PIN 30

#define BREAK_CODE 0XF0
#define LEFT_SHIFT 0X12
#define RIGHT_SHIFT 0x59

#define CAP 0x58
#define NUM 0x77
#define ACK 0xFA

#define CMD_PARITY_BIT 8
#define CMD_STOP_BIT 9
#define CMD_ACK 10


extern uint8_t Character_Array[20];
extern unsigned char unshifted[68][2];
extern unsigned char shifted[68][2];
__irq void Ps2keyboard_Interrupt(void);
void decode();
void StartCmd();
void SendCmd();




#endif
