#include "DIO.h"
#include "tm4c123gh6pm.h"
#include <stdio.h>
#include "LCD.h"

void KeyPad_Init(void)
{
  SYSCTL_RCGCGPIO_R|=0x10; //clk =1 at port E
  while((SYSCTL_PRGPIO_R & 0x10)!= 0x10); //actual clk value check 
  GPIO_PORTE_LOCK_R = 0x4C4E434B;
  GPIO_PORTE_CR_R |= 0xF; 
  GPIO_PORTE_DIR_R = 0xF;
  GPIO_PORTE_DEN_R|= 0xF;
  
  SYSCTL_RCGCGPIO_R|=0x4; //clk =1 at port C
  while((SYSCTL_PRGPIO_R & 0x4)!= 0x4); //actual clk value check 
  GPIO_PORTC_LOCK_R = 0x4C4E434B;
  GPIO_PORTC_CR_R = 0xF0; 
  GPIO_PORTC_DIR_R= 0x00;
  GPIO_PORTC_PDR_R|= 0xF0;
  GPIO_PORTC_DEN_R|= 0xF0;
  
   /*SYSCTL_RCGCGPIO_R|=0x2; //clk =1 at port B
  while((SYSCTL_PRGPIO_R & 0x2)!= 0x2); //actual clk value check 
  GPIO_PORTB_LOCK_R = 0x4C4E434B; 
  GPIO_PORTB_CR_R |= 0x7F;
  GPIO_PORTB_DIR_R|= 0x7F;
  //GPIO_PORTB_PDR_R|= 0x8;
  GPIO_PORTB_DEN_R|= 0x7F;*/
}

uint8 KeyPad_Read(void)
{
  uint8 table[4][4]={
    {'1','2','3','+'},
    {'4','5','6','-'},
    {'7','8','9','/'},
    {'x','0','F','='}
  };
  
  uint32 port = 0;
  while(port == 0){
  
  for(int i=0;i<4;i++){
    
    DIO_WritePort(&GPIO_PORTE_DATA_R,(1<<i));
    port = DIO_ReadPort(&GPIO_PORTC_DATA_R)&0xF0;  
      
    if(port == 0x10){return table[i][0];}
    else if(port == 0x20){return table[i][1];}
    else if(port == 0x40){return table[i][2];}
    else if(port == 0x80){return table[i][3];}
    
  }}
  return 'A';
}

uint32 concatenate(uint32 x, uint32 y)
{
    uint32 shift;
    x = x*10;
    shift = x + y;
    return shift;
} 

uint32 checkFlag(uint8 x){
    uint8 op[] = {'+', '-', '/', 'x','='};
    for(int i=0;i<5;i++){
        if(x == op[i]){
            return 0;
        }
    }
    return 1;
}

uint32 getDigits(uint8_ptr op){
  uint32 counter = 0;
  uint32 digit = 0;
  uint8 x;
  uint32 y;
  uint32 flag = 1;
  
  while((counter<6) && (flag == 1)){
    //printf("d\n");   
    x = KeyPad_Read();
    delay(0.3);
    
    if(x != 'A'){ 
      
      flag = checkFlag(x);
    
    if(counter == 5 || flag == 0){
      *op = x;
      
      break;
    }
    y = x - '0';
    digit = concatenate(digit,y);
    //x = KeyPad_Read();
    counter++;
    //delay(0.5);
    }else{}
  }
  return digit;
}


/*uint32 GetDigits(){
  uint8 op[] = {'+', '-', '/', 'x'};
  uint32 counter = 1;
  uint32 digit = 0;
  uint8 x = KeyPad_Read();
  uint32 y;
  while(counter<6){
    counter++;
    y = x - '0';
    digit = concatenate(digit,y);
    x = KeyPad_Read();
    //delay(0.5);
  }
  return digit;
}
  /*if(x != op[0] && x != op[1] && x != op[2] && x != op[3]){
    digit = x;
  }
  else{
    //return "invalid input";
  }
  while(x != op[0] && x != op[1] && x != op[2] && x != op[3]){
    
  }
}*/
void ReadInputs(){
    uint8_ptr op;
    uint8 e;
    op = &e;
    uint32 x = getDigits(op);
    
    uint8_ptr op2;
    uint8 e2;
    op2 = &e2;
    uint32 y = getDigits(op2);
    
    double64 result;
    
    switch(e){
      case '+':
        result = x+y;
        break;
        
      case '-':
        result = x-y;
        break;
        
      case '/':
        result = (double64)x/y;
        break;
        
      case 'x':
        result = x*y;
        break;     
    } 
    
    uint8_ptr equ;
    uint8 buffer[50];
    uint8 buffer2[50];
    sprintf(buffer, "%d %c %d %c ",x, e, y, e2);
    sprintf(buffer2, "%f ",result);
    
    
    
    LCD_Cmd(0x01);		
    LCD_Cmd(0x80);               //Force the cursor to beginning of 1st line
    delayMs(500);											
    LCD_Write_String(buffer);
    LCD_Cmd(0xC0);
    LCD_Write_String(buffer2);
    delayMs(500);   
    //printf("%s \n",buffer);
    //printf("%d %c %d %c %f \n", x, e, y, e2, result);
}
