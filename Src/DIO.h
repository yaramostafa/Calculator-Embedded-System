#ifndef DIO_H
  #define DIO_H
#include "types.h"

void delay(double number_of_seconds);
void DIO_init(void);
void DIO_WritePort(ulong32_ptr port,ulong32 value);
void DIO_WritePin(ulong32_ptr port,uint8 pin,uint8 value);
void DIO_TogglePin(ulong32_ptr port,uint16 pin);
uint8 DIO_ReadPin(ulong32_ptr port,uint8 pin);
uint32 DIO_ReadPort(ulong32_ptr port);

#endif