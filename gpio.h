#ifndef __GPIO_H
#define __GPIO_H

#include "types.h"
#include <lpc214x.h>



#define PORT0 0
#define PORT1 1 

#define OUTPUT 1
#define INPUT 0

#define HIGH 1
#define LOW 0

 


#define FUNC0 0
#define FUNC1 1
#define FUNC2 2
#define FUNC3 3


enum PIN_NUM {PIN_NUM0,PIN_NUM1,PIN_NUM2,PIN_NUM3,PIN_NUM4,PIN_NUM5,PIN_NUM6,
	            PIN_NUM7,PIN_NUM8,PIN_NUM9,PIN_NUM10,PIN_NUM11,PIN_NUM12,PIN_NUM13,
              PIN_NUM14,PIN_NUM15,PIN_NUM16,PIN_NUM17,PIN_NUM18,PIN_NUM19,PIN_NUM20,
              PIN_NUM21,PIN_NUM22,PIN_NUM23,PIN_NUM24,PIN_NUM25,PIN_NUM26,PIN_NUM27,
              PIN_NUM28,PIN_NUM29,PIN_NUM30,PIN_NUM31};




void GPIOFuncSel(uint8_t Portnum, uint8_t Pinnum, uint8_t Func);
void GPIOSetDir(uint8_t Portnum, uint8_t Pinnum, uint8_t Dirn);
void GPIOSetVal(uint8_t Portnum, uint8_t Pinnum, uint8_t Value);
void GPIOSetBusVal(uint8_t Portnum, uint8_t Pinnum, uint8_t BusValue);
void GPIOSet_4bit_BusVal(uint8_t Portnum, uint8_t Pinnum, uint8_t BusValue);
uint8_t GPIOGetVal(uint8_t Portnum, uint8_t Pinnum);
void delay(uint32_t count);












#endif
