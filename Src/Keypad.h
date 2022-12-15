#ifndef KEY_H
  #define KEY_H

#include "types.h"
#include "DIO.h"
void KeyPad_Init(void);
uint8 KeyPad_Read(void);
uint16 GetDigits();
void SevenSegment_Display();
uint32 getDigits();
void ReadInputs();

#endif