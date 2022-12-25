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
  //KeyPad_Init();
  //uint8_ptr str = "I want pizza";    //Write any string you want to display on LCD
 
  KeyPad_Init();
  LCD_init();
                                                  
   while(1){
    LCD_Cmd(0x01);
    LCD_Cmd(0x80);               //Force the cursor to beginning of 1st line
    delayMs(500);
    LCD_Write_String("Choose 1)Calc ");
    LCD_Cmd(0xC0);
    LCD_Write_String("2)Tim 3)SP");
     
    uint8 x;
    x = KeyPad_Read_task1();
    delay(0.3);
    if(x == '1'){
      uint8 y = '1';
      while(y != 'F'){
        y = ReadInputs_task1();
      }
     }/*else if(x == '2'){
       
     }else if(x == '3'){
       
     }*/
    
   }	
  
  return 0;
}
