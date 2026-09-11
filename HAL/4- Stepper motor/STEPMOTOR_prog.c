#include "Std_Types.h"
#include "Bit_Math.h"

#include "DIO_int.h"

#include "STEPMOTOR_int.h"
#include "STEPMOTOR_config.h"
#include "STEPMOTOR_private.h"

#define F_CPU 1000000UL
#include <util/delay.h>

void STEPMOTOR_init(void)
{
    DIO_voidSetPinDirection(STEPMOTOR_PORT,PIN0,OUTPUT);
    DIO_voidSetPinDirection(STEPMOTOR_PORT,PIN1,OUTPUT);
    DIO_voidSetPinDirection(STEPMOTOR_PORT,PIN2,OUTPUT);
    DIO_voidSetPinDirection(STEPMOTOR_PORT,PIN3,OUTPUT);
}

void FULL_STEP(u8 Direction)
{
    if(Direction == 1)
    {
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00000001);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00000010);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00000100);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00001000);
        _delay_ms(2000);
    }
    else if(Direction == 0)
    {
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00001000);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00000100);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00000010);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00000001);
        _delay_ms(2000);
    }
}

void HALF_STEP(u8 Direction)
{
    if(Direction == 1)
    {
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00001001);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00000001);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00000011);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00000010);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00000110);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00000100);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00001100);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00001000);
        _delay_ms(2000);
    }
    else if(Direction == 0)
    {
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00001000);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00001100);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00000100);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00000110);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00000010);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00000011);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00000001);
        _delay_ms(2000);
        DIO_voidSetPortValue(STEPMOTOR_PORT,0b00001001);
        _delay_ms(2000);
    }
}