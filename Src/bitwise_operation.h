#ifndef BITWISE_OP
  #define BITWISE_OP

#define setBit(Register , Bit)(Register |= (1<< Bit))
#define clearBit(Register , Bit)(Register &= !(1<< Bit))
#define getBit(Register , Bit)(((Register & (1<<Bit))>>Bit)) 
#define toggleBit(Register , Bit)(Register ^= (1<<Bit))

#endif
