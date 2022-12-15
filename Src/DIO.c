#include "types.h"
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include <time.h>

void delay(double number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 100 * number_of_seconds;
 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

void DIO_init(void)
{
  SYSCTL_RCGCGPIO_R|=0x20; //clk =1 at port F
  while((SYSCTL_PRGPIO_R & 0x20)!= 0x20); //actual clk value check 
  GPIO_PORTF_LOCK_R = 0x4C4E434B; 
  GPIO_PORTF_CR_R |= 0x1F; 
  GPIO_PORTF_DIR_R|= 0x0E;
  GPIO_PORTF_PUR_R|= 0x11;
  GPIO_PORTF_DEN_R|= 0x1F;
  
  SYSCTL_RCGCGPIO_R|=0x2; //clk =1 at port B
  while((SYSCTL_PRGPIO_R & 0x2)!= 0x2); //actual clk value check 
  GPIO_PORTB_LOCK_R = 0x4C4E434B; 
  GPIO_PORTB_CR_R |= 0x8; 
  GPIO_PORTB_DIR_R|= 0x00;
  GPIO_PORTB_PDR_R|= 0x8;
  GPIO_PORTB_DEN_R|= 0x8;
  
}

void DIO_WritePort(ulong32_ptr port,ulong32 value)
{
  *port = value;
}

void DIO_WritePin(ulong32_ptr port,uint16 pin,uint16 value)
{
  //*port &= (value << pin);
  if(value == 1)
  {
    setBit(*port , pin);
  }
  else if (value == 0)
  {
    clearBit(*port, pin);
  }
}

void DIO_TogglePin(ulong32_ptr port,uint16 pin)
{
  toggleBit(*port,pin);
}

uint8 DIO_ReadPin(ulong32_ptr port,uint16 pin)
{
  return getBit(*port,pin);
}

uint32 DIO_ReadPort(ulong32_ptr port)
{
  return *(port);
}

