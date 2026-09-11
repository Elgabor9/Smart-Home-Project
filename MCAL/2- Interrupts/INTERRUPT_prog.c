#include "Std_Types.h"
#include "Bit_Math.h"

#include "DIO_int.h"

#include "INTERRUPT_int.h"
#include "INTERRUPT_config.h"
#include "INTERRUPT_private.h"


void INTERRUPT_init(void)
{
	DIO_voidSetPinDirection(DPORTD,PIN3,INPUT);
	DIO_voidSetPinValue(DPORTD,PIN3,HIGH);

    Clear_Bit(MCUCR, ISC11);
    Set_Bit(MCUCR, ISC10);

    Clear_Bit(MCUCR, ISC01);
    Set_Bit(MCUCR, ISC00);

    Set_Bit(GICR, 6);
    Set_Bit(GICR, 7);

    Set_Bit(SREG, 7);
}