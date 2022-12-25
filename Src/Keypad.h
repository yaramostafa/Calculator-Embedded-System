#ifndef KEY_H
  #define KEY_H

#include "types.h"
#include "DIO.h"
void KeyPad_Init(void);
uint8 KeyPad_Read_task1(void);
uint32 getDigits_task1(uint8_ptr op, uint16 firstflag);
uint8 ReadInputs_task1();

#endif