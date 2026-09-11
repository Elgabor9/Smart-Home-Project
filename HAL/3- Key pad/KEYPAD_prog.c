#include "Std_Types.h"
#include "Bit_Math.h"

#include "DIO_int.h"

#include "KEYPAD_int.h"
#include "KEYPAD_config.h"
#include "KEYPAD_private.h"

u8 matrix[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'c','0','=','+'}};

void KEYPAD_init(void)
{

	DIO_voidSetPinDirection(DPORTB,PIN0,INPUT);
	DIO_voidSetPinDirection(DPORTB,PIN1,INPUT);
	DIO_voidSetPinDirection(DPORTB,PIN2,INPUT);
	DIO_voidSetPinDirection(DPORTB,PIN3,INPUT);
	DIO_voidSetPinDirection(DPORTB,PIN4,OUTPUT);
	DIO_voidSetPinDirection(DPORTB,PIN5,OUTPUT);
	DIO_voidSetPinDirection(DPORTB,PIN6,OUTPUT);
	DIO_voidSetPinDirection(DPORTB,PIN7,OUTPUT);

	DIO_voidSetPinValue(DPORTB,PIN0,HIGH);
	DIO_voidSetPinValue(DPORTB,PIN1,HIGH);
	DIO_voidSetPinValue(DPORTB,PIN2,HIGH);
	DIO_voidSetPinValue(DPORTB,PIN3,HIGH);

}

u8 KEYPAD_get(void)
{

	u8 row=0,col=0;
	for(row=0;row<4;row++)
		{
			DIO_voidSetPinValue(DPORTB,row+4,LOW);
			for(col=0;col<4;col++)
				{
					if(DIO_u8ReadPinValue(DPORTB,col)==LOW)
						{
							while(DIO_u8ReadPinValue(DPORTB,col)==LOW);
							DIO_voidSetPinValue(DPORTB,row+4,HIGH);
							return (matrix[col][row]);
						}
				}
			DIO_voidSetPinValue(DPORTB,row+4,HIGH);
		}
 	return 0xFF ;

}