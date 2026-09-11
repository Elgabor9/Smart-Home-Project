#ifndef _LCD_INT_H_
#define _LCD_INT_H_


//init
void LCD_init();

//char
void LCD_sendChar(u8 Data);

//send command
void LCD_SendCommand(u8 command);

//Send String
void LCD_SendString (u8 *str);

//move cursor
void GoToXY(u8 x, u8 y);

//print number
void LCD_voidWriteNumber(s32 num);

#endif