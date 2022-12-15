#include "types.h"
#include "tm4c123gh6pm.h"
#include "DIO.h"
#include "bitwise_operation.h"
#include <stdio.h>
#include <time.h>
#include "Keypad.h"
#include "LCD.h"
#include <stdlib.h>

int main()
{ 
  KeyPad_Init();
  LCD_init();
								
   while(1){
    ReadInputs();
   }	
  
  return 0;
}
