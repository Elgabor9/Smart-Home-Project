#define F_CPU 8000000UL

#include <util/delay.h>
#include "Std_Types.h"
#include "DIO_int.h"
#include "UART_int.h"
#include "TIMER1_int.h"

int main(void)
{
	DIO_voidInitialization();
	DIO_voidSetPinDirection(DPORTD, PIN5, OUTPUT);

	
	DIO_voidSetPinDirection(DPORTD, PIN0, INPUT);
	DIO_voidSetPinDirection(DPORTD, PIN1, OUTPUT);
	UART_voidInit();
	TIMER1_voidInitServo();
	u8 received_data;
	
	while (1)
	{
		received_data = UART_u8Receive();
		if (received_data == '1')
		{
			TIMER1_voidSetServoAngle(90);
		}
		if (received_data == '0')
		{
			TIMER1_voidSetServoAngle(0);
		}
		_delay_ms(10);
	}
}