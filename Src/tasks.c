#include "DIO.h"
#include "types.h"
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"


void blink_lights()
{
   DIO_WritePort(&GPIO_PORTF_DATA_R,0x02);
   delay(1);
   DIO_WritePort(&GPIO_PORTF_DATA_R,0x04);
   delay(1);
   DIO_WritePort(&GPIO_PORTF_DATA_R,0x08);
   delay(1);
}

void task0()
{
  DIO_WritePort(&GPIO_PORTF_DATA_R,0x02);
  delay(1);
  printf("%d",DIO_ReadPin(&GPIO_PORTF_DATA_R,0x1));
  DIO_WritePort(&GPIO_PORTF_DATA_R,0x04);
  delay(1);
  printf("%d",DIO_ReadPin(&GPIO_PORTF_DATA_R,0x2));
  DIO_WritePort(&GPIO_PORTF_DATA_R,0x08);
  delay(1);
  printf("%d",DIO_ReadPin(&GPIO_PORTF_DATA_R,0x3));
  DIO_WritePin(&GPIO_PORTF_DATA_R,3,2);
  printf("%d",DIO_ReadPort(&GPIO_PORTF_DATA_R));
  printf("%x",GPIO_PORTF_DATA_BITS_R[0x3FC]);
}

void task1()
{
  uint8 pinB = DIO_ReadPin(&GPIO_PORTB_DATA_R,3);
  uint8 pinF = DIO_ReadPin(&GPIO_PORTF_DATA_R,4);
  /*if(pinF == 0 || pinB == 1)//((DIO_ReadPort(&GPIO_PORTF_DATA_R)&0x11)!=0x11)
  {
    
    while(pinF == 0 || pinB == 1)//((DIO_ReadPort(&GPIO_PORTF_DATA_R)&0x11)!=0x11)
    {
      uint8 pinB = DIO_ReadPin(&GPIO_PORTB_DATA_R,3);
      uint8 pinF = DIO_ReadPin(&GPIO_PORTF_DATA_R,4);//port=DIO_ReadPort(&GPIO_PORTF_DATA_R);
    }
  }*/
  //uint32 value = port&0x11;
  
  if(pinF == 0 & pinB == 1){
    DIO_TogglePin(&GPIO_PORTF_DATA_R,3);
  }else if(pinB){
    DIO_TogglePin(&GPIO_PORTF_DATA_R,1);
  }
  else if(pinF==0){
    DIO_TogglePin(&GPIO_PORTF_DATA_R,2);
  }
  delay(0.5);
}

void task2()
{
  uint8 pinB = DIO_ReadPin(&GPIO_PORTB_DATA_R,3);
  uint8 pinF = DIO_ReadPin(&GPIO_PORTF_DATA_R,4);
  static uint8 state = 0;
  
  switch(state){
  case 0: //white
    DIO_WritePort(&GPIO_PORTF_DATA_R,0x0E);
    break;
  case 1: //Red
    DIO_WritePort(&GPIO_PORTF_DATA_R,0x02);
    break;
  case 2: //Green
    DIO_WritePort(&GPIO_PORTF_DATA_R,0x08);
    break;
  case 3: //Blue
    DIO_WritePort(&GPIO_PORTF_DATA_R,0x04);
    break;
  }
  delay(0.5);
  if(pinF==0&&pinB==1){
        state=0;
      }
  else if(pinB)
  {
    if(state == 3){
      state = 0;
    }else {
      state++;
    }
      
  }else if(pinF==0)
  {
    if(state == 0){
      state = 3;
    }else {
      state--;
    }
  }
}

void task1_lab4()
{
    int arr[]={2,3,4,5,6,7,7,7,8,8,1,9,8,1,1};
    int size = sizeof(arr)/sizeof(arr[0]);
    uint8 pinB = DIO_ReadPin(&GPIO_PORTB_DATA_R,3);
    uint8 pinF = DIO_ReadPin(&GPIO_PORTF_DATA_R,4);
    static uint8 state;
    static int16 i = -1;
    
    
    if(pinF==0||pinB==1){
      if(i==size-1 || i ==-1){
        i = 0;
      }else{
        i++;
      }
      if(arr[i]%2==0){
        state = 1;
      }else{
        state = 0;
      }
      
      switch(state){
      case 0: //Red
        DIO_WritePort(&GPIO_PORTF_DATA_R,0x02);
        break;
      case 1: //Blue
        DIO_WritePort(&GPIO_PORTF_DATA_R,0x04);
        break;
      }
      delay(0.5);
    }
}