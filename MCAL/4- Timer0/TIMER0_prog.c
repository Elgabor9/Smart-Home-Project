#include "Std_Types.h"
#include "Bit_Math.h"

#include "DIO_int.h"

#include "TIMER0_int.h"
#include "TIMER0_config.h"
#include "TIMER0_private.h"

void TIMER0_voidInit(void)
{
    if(TIMER0_MODE==CTC)
    {
        Set_Bit(TCCR0, 3);
        Clear_Bit(TCCR0, 6);

        Set_Bit(TIMSK, 1);
        Set_Bit(TCCR0, 0);
        Clear_Bit(TCCR0, 1);
        Set_Bit(TCCR0, 2);
    }
    else
    {
        Clear_Bit(TCCR0, 3);
        Clear_Bit(TCCR0, 6);
    }

}

void TIMER0_voidDelay1Sec(void)
{

    Set_Bit(TCCR0, 0);
    Clear_Bit(TCCR0, 1);
    Set_Bit(TCCR0, 2);

    for(u8 count = 0; count < 50; count++)
    {
        TCNT0 = 256-156;

        while(Get_Bit(TIFR, 0) == 0);
        Set_Bit(TIFR, 0);
    }

    TCCR0 &= 0xF8;
}

void TIMER0_voidSetCompare(u8 Val)
{
    OCR0 = Val;
}


