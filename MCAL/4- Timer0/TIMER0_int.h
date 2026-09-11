#ifndef TIMER0_INT_H
#define TIMER0_INT_H

void TIMER0_voidInit(void);
void TIMER0_voidDelay1Sec(void);

//CTC
#define CTC 0
#define NORMAL 1
void TIMER0_voidSetCompare(u8 Copy_u8OCRValue);


#endif