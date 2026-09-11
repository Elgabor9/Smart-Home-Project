#include "Std_Types.h"
#include "Bit_Math.h"

#include "DIO_int.h"

#include "UART_int.h"
#include "UART_config.h"
#include "UART_private.h"

void UART_voidInit(void)
{
    u8 UCSRC_temp = 0;

    u16 UBRR_val = (UART_F_CPU / (16UL * UART_BAUD_RATE)) - 1;
    UBRRL = (u8)UBRR_val;
    UBRRH = (u8)(UBRR_val >> 8);

    Set_Bit(UCSRB, 4);
    Set_Bit(UCSRB, 3);

    Set_Bit(UCSRC_temp, 7);
    Set_Bit(UCSRC_temp, 2);
    Set_Bit(UCSRC_temp, 1);

    UCSRC = UCSRC_temp;
}

void UART_voidTransmit(u8 Copy_u8Data)
{
    while (Get_Bit(UCSRA, 5) == 0);

    UDR = Copy_u8Data;
}

u8 UART_u8Receive(void)
{
    while (Get_Bit(UCSRA, 7) == 0);

    return UDR;
}
