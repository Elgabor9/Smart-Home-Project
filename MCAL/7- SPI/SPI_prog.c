#include "Std_Types.h"
#include "Bit_Math.h"

#include "DIO_int.h"

#include "SPI_int.h"
#include "SPI_config.h"
#include "SPI_private.h"

void SPI_voidInitMaster(void)
{
    DIO_voidSetPinDirection(DPORTB, PIN5, OUTPUT);
    DIO_voidSetPinDirection(DPORTB, PIN7, OUTPUT);
    DIO_voidSetPinDirection(DPORTB, PIN4, OUTPUT);

    DIO_voidSetPinValue(DPORTB, PIN4, HIGH);

    DIO_voidSetPinDirection(DPORTB, PIN6, INPUT);

    Set_Bit(SPCR, 6);
    Set_Bit(SPCR, 4);
    Set_Bit(SPCR, 0);
}

void SPI_voidInitSlave(void)
{
    DIO_voidSetPinDirection(DPORTB, PIN6, OUTPUT);

    DIO_voidSetPinDirection(DPORTB, PIN5, INPUT);
    DIO_voidSetPinDirection(DPORTB, PIN7, INPUT);
    DIO_voidSetPinDirection(DPORTB, PIN4, INPUT);

    Set_Bit(SPCR, 6); // SPE
}

u8 SPI_u8Transceive(u8 Copy_u8Data)
{
    SPDR = Copy_u8Data;

    while (Get_Bit(SPSR, 7) == 0);

    return SPDR;
}