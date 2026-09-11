#include <string.h>
#include <stdlib.h>

#include "Std_Types.h"
#include "Bit_Math.h"

#define F_CPU 1000000UL
#include <util/delay.h>

#include "DIO_int.h"

#include "LCD_int.h"
#include "LCD_config.h"
#include "LCD_int.h"


void LCD_SendCommand(u8 command)
{

    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, LOW);
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, LOW);

    //Send command hex to Data Port
    DIO_voidSetPortValue(LCD_DATA_PORT, command);

    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, HIGH);
    _delay_ms(2);
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, LOW);
}

void LCD_sendChar(u8 Data)
{
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, HIGH);
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, LOW);
    DIO_voidSetPortValue(LCD_DATA_PORT, Data);

    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, HIGH);
    _delay_ms(2);
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, LOW);
}


void LCD_init()
{
    DIO_voidSetPortDirection(LCD_DATA_PORT, OUTPUT);
    DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_RS_PIN, OUTPUT);
    DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_RW_PIN, OUTPUT);
    DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_EN_PIN, OUTPUT);
    _delay_ms(40);

    LCD_SendCommand(0x38);
    _delay_ms(1);

    LCD_SendCommand(0x0C);
    _delay_ms(1);

    LCD_SendCommand(0x01);
    _delay_ms(2);

}

void LCD_SendString(u8 *str)
{
    u8 i = 0;
    while(i<strlen(str))
    {
        LCD_sendChar(str[i]);
        i++;
    }
}

void GoToXY(u8 x, u8 y)
{

    u8 new=0;

    if(y==0) new=x;
    else if(y==1) new=0x40+x;

    LCD_SendCommand(new+0x80);

}

void LCD_voidWriteNumber(s32 number)
{

    u8 print[15];
    ltoa(number, (char*)print, 10);
    LCD_SendString(print);

}