#ifndef INTERRUPT_PRIVATE_H
#define INTERRUPT_PRIVATE_H


#define MCUCR  *((volatile u8 *)0x55)
#define MCUCSR *((volatile u8 *)0x54)
#define GICR   *((volatile u8 *)0x5B)
#define GIFR   *((volatile u8 *)0x5A)
#define SREG   *((volatile u8 *)0x5F)

#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3


#endif