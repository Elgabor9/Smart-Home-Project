/*
* GccApplication1.c
*
* Created: 8/31/2026 7:42:41 PM
* Author : ELgabor
*/

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Std_Types.h"
#include "Bit_Math.h"

#include "DIO_int.h"

#include "LCD_int.h"

#include "KEYPAD_int.h"

#include "STEPMOTOR_int.h"

#include "INTERRUPT_int.h"

#include "TIMER0_int.h"

#include "TIMER1_int.h"

#include "ADC_int.h"

#include "UART_int.h"


#define LIGHT_EVENING 0
#define LIGHT_AFTERNOON 1
#define LIGHT_MORNING 2

#define HOT 0
#define WARM 1
#define COLD 2

#define PWM_FULL 255
#define PWM_HALF 128
#define PWM_OFF 0

#define motor_port DPORTD
#define LED_port DPORTA
#define motor_pin PIN4
#define LED_pin PIN3
//global variables
u8 Current_Room_Tempreature;
u8 Current_Room_Light;


#define OFF 0
#define ON 1
u8 Light_mode=OFF;
void Light_Switch(u8 mode);

u16 Temp_sensor (void);
void light_sensor (void);


int main(void)
{
	DIO_voidInitialization();
	LCD_init();
	KEYPAD_init();
	TIMER0_voidInit();
	TIMER1_voidInitServo();
	INTERRUPT_init();
	ADC_voidInit();
	UART_voidInit();
	
	//Buzzer
	DIO_voidSetPinDirection(DPORTD,PIN7,OUTPUT);
	//Servo motor
	DIO_voidSetPinDirection(DPORTD,PIN5, OUTPUT);
	//Switch
	DIO_voidSetPinDirection(DPORTD,PIN6, OUTPUT);
	//in_Led EXTI
	DIO_voidSetPinDirection(DPORTA,PIN4, OUTPUT);
	//Temp sensor
	DIO_voidSetPinDirection(DPORTA,PIN1,INPUT);
	//LDR sensor
	DIO_voidSetPinDirection(DPORTA,PIN0,INPUT);
	//Fan
	DIO_voidSetPinDirection(motor_port,motor_pin,OUTPUT);
	//Out_Led
	DIO_voidSetPinDirection(LED_port,LED_pin,OUTPUT);
	//Door Servo Motor
	DIO_voidSetPinDirection(DPORTD, PIN1, OUTPUT);
	DIO_voidSetPinDirection(DPORTD, PIN0, INPUT);
	
	u8 string[16];
	u8 idx=0;
	u8 pressed_key,wrong_PIN=0;
	LCD_SendString(" ENTER PIN: ");
	GoToXY(0,1);
	
	/* Replace with your application code */
	while (1)
	{
		
		pressed_key=KEYPAD_get();
		if(pressed_key>='0'&& pressed_key<='9')
		{
			LCD_sendChar('*');
			string[idx]=pressed_key;
			idx++;
		}
		else if(pressed_key=='=')
		{
			u32 num=0;
			for(u8 i=0;i<idx;i++)
			{
				num = (num * 10) + (string[i] - '0');
			}
			
			if(num==951236)
			{
				wrong_PIN=0;
				
				u8 door_state = 0 , door2_state = 0;      // 0 = Unlocked, 1 = Locked
				u8 fan_state = 0;       // 0 = OFF, 1 = ON
				u8 Sensors = 0; // 0 = Sensors Control, 1 = User Controls
				
				TIMER1_voidSetServoAngle(90); //2222222222222
				UART_voidTransmit('1');
				
				Light_Switch(ON);
				
				GoToXY(0,1);
				LCD_SendString("  CORRECT PIN    ");
				GoToXY(0,1);
				_delay_ms(1000);
				LCD_SendCommand(0x01);
				LCD_SendString("   WELCOME    ");
				_delay_ms(1000);
				LCD_SendCommand(0x01);
				
				PWM_Init();
				
				
				while(1)
				{
					u16 tmp_val = Temp_sensor();
					light_sensor();
					
					if (Sensors == 0)
					{
						switch (Current_Room_Tempreature) {
							case HOT:  Motor_SetSpeed(PWM_FULL); fan_state = 1; break;
							case WARM: Motor_SetSpeed(PWM_HALF); fan_state = 1; break;
							case COLD: Motor_SetSpeed(PWM_OFF);  fan_state = 0; break;
						}
						switch(Current_Room_Light){
							case LIGHT_EVENING:	 DIO_voidSetPinValue(LED_port, LED_pin, HIGH); break;
							case LIGHT_AFTERNOON: DIO_voidSetPinValue(LED_port, LED_pin, HIGH); break;
							case LIGHT_MORNING:   DIO_voidSetPinValue(LED_port, LED_pin, LOW);  break;
						}
					}
					
					GoToXY(0, 0);
					LCD_SendString(" T:");
					LCD_voidWriteNumber(tmp_val);
					LCD_SendString("C Dr:");
					if(door_state == 0 && door2_state == 0 ) LCD_SendString("UNLCK");
					else LCD_SendString("LOCK ");
					
					GoToXY(0, 1);
					LCD_SendString("L:");
					if(DIO_u8ReadPinValue(DPORTA,PIN4) == HIGH) LCD_SendString("ON");
					else LCD_SendString("OFF");
					
					LCD_SendString(" F:");
					if(fan_state == 1) LCD_SendString("ON ");
					else LCD_SendString("OFF");
					
					LCD_SendString("0:Menu");
					
					u8 key = 0xFF;
					for(u8 wait = 0; wait < 50; wait++)
					{
						key = KEYPAD_get();
						if(key != 0xFF) break;
						_delay_ms(10);
					}
					
					if (key == '0')
					{
						u8 in_menu = 1;
						while (in_menu)
						{
							LCD_SendCommand(0x01);
							LCD_SendString(" 1:Door   2:LED");
							GoToXY(0, 1);
							LCD_SendString(" 3:Fan    4:Auto ");
							
							u8 choice = 0xFF;
							while (choice == 0xFF) choice = KEYPAD_get();
							
							switch (choice)
							{
								case '1': // Door Sub-Menu
								{
									u8 in_door_menu = 1;
									
									while (in_door_menu)
									{
										LCD_SendCommand(0x01);
										LCD_SendString(" 1:LOCK1 2:LOCK2");
										GoToXY(0, 1);
										LCD_SendString(" 3:Back");
										
										u8 door_choice = 0xFF;
										while (door_choice == 0xFF) door_choice = KEYPAD_get();
										
										switch (door_choice)
										{
											case '1': // Toggle Door 1
											TIMER1_voidInitServo();
											if (door_state == 0) {
												TIMER1_voidSetServoAngle(0); 
												door_state = 1;
												LCD_SendCommand(0x01); LCD_SendString(" DOOR 1 LOCKED! ");
											}
											else 
											{
												TIMER1_voidSetServoAngle(90);
												door_state = 0;
												LCD_SendCommand(0x01); LCD_SendString(" DOOR 1 UNLOCKED");
											}
											_delay_ms(1000);
											PWM_Init();
											break;
											
											case '2': // Toggle Door 2 (AVR 2 via UART)
											if (door2_state == 0) {
												UART_voidTransmit('0'); // Send Lock to Slave AVR
												door2_state = 1;
												LCD_SendCommand(0x01); LCD_SendString(" DOOR 2 LOCKED! ");
											}
											else
											{
												UART_voidTransmit('1'); // Send Unlock to Slave AVR
												door2_state = 0;
												LCD_SendCommand(0x01); LCD_SendString(" DOOR 2 UNLOCKED");
											}
											_delay_ms(1000);
											break;
											
											case '3': // Back
											in_door_menu = 0;
											break;
										}
									}
								}
								break;
								
								case '2': //Toggle Light Sub-Menu
								Sensors = 1; //Disables the LDR sensor
								u8 in_light_menu = 1;
								
								while (in_light_menu)
								{
									LCD_SendCommand(0x01);
									LCD_SendString(" 1:In LED");
									GoToXY(0, 1);
									LCD_SendString("2:OutLED 7:Back");
									
									u8 light_choice = 0xFF;
									while (light_choice == 0xFF) light_choice = KEYPAD_get();
									
									switch (light_choice)
									{
										case '1': // Toggle Inside LED
										if (Light_mode == ON) {
											Light_Switch(OFF);
											LCD_SendCommand(0x01); LCD_SendString("  IN LIGHT OFF  ");
										}
										else {
											Light_Switch(ON);
											LCD_SendCommand(0x01); LCD_SendString("  IN LIGHT ON   ");
										}
										_delay_ms(1000);
										break;
										
										case '2': // Toggle Outside LED
										if (DIO_u8ReadPinValue(DPORTA, PIN3) == HIGH) {
											DIO_voidSetPinValue(DPORTA, PIN3, LOW);
											LCD_SendCommand(0x01); LCD_SendString("  OUT LIGHT OFF ");
										}
										else {
											DIO_voidSetPinValue(DPORTA, PIN3, HIGH);
											LCD_SendCommand(0x01); LCD_SendString("  OUT LIGHT ON  ");
										}
										_delay_ms(1000);
										break;
										
										case '7': // Back
										in_light_menu = 0;
										break;
									}
								}
								break;
								
								case '3': //Toggle Fan
								Sensors = 1; //Disables the Temp sensor
								if (fan_state == 1) {
									Motor_SetSpeed(PWM_OFF);
									fan_state = 0;
									LCD_SendCommand(0x01); LCD_SendString("    FAN OFF     ");
								}
								else {
									Motor_SetSpeed(PWM_FULL);
									fan_state = 1;
									LCD_SendCommand(0x01); LCD_SendString("    FAN ON      ");
								}
								_delay_ms(1000);
								break;
								
								case '4': // Re-enable Sensors
								Sensors = 0;
								LCD_SendCommand(0x01);
								LCD_SendString(" SENSORS ACTIVE ");
								_delay_ms(1000);
								
								LCD_SendCommand(0x01);
								LCD_SendString(" T:");
								LCD_voidWriteNumber(tmp_val);
								LCD_SendString("C Dr:");
								if(door_state == 0 && door2_state == 0 ) LCD_SendString("UNLCK");
								else LCD_SendString("LOCK ");
								
								GoToXY(0, 1);
								LCD_SendString("L:");
								if(DIO_u8ReadPinValue(DPORTA,PIN4) == HIGH) LCD_SendString("ON");
								else LCD_SendString("OFF");
								
								LCD_SendString(" F:");
								if(fan_state == 1) LCD_SendString("ON ");
								else LCD_SendString("OFF");
								
								in_menu = 0;
								break;
								
								case '0':
								in_menu = 0;
								break;
							}
						}
					}
				}
			}
			
			
			
			else //wrong PIN
			{
				idx=0;
				wrong_PIN++;
				
				GoToXY(0,1);
				LCD_SendString("    WRONG PIN    ");
				DIO_voidSetPinValue(DPORTD,PIN7,HIGH);
				_delay_ms(300);
				GoToXY(0,1);
				LCD_SendString("              ");
				_delay_ms(300);
				GoToXY(0,1);
				LCD_SendString("    WRONG PIN    ");
				DIO_voidSetPinValue(DPORTD,PIN7,LOW);
				_delay_ms(300);
				GoToXY(0,1);
				LCD_SendString("              ");
				_delay_ms(300);
				LCD_SendCommand(0x01);
				LCD_SendString(" ENTER PIN: ");
				GoToXY(0,1);
				
				if(wrong_PIN==3)
				{
					LCD_SendCommand(0x01);
					LCD_SendString(" SYSTEM LOCKED! ");
					
					for(u16 sec = 20; sec > 0; sec--)
					{
						if(sec<10)
						{
							GoToXY(0,1);
							LCD_SendString(" WAIT 00:0");
							LCD_voidWriteNumber(sec);
							LCD_SendString(" SEC ");
						}
						else
						{
							GoToXY(0,1);
							LCD_SendString(" WAIT 00:");
							LCD_voidWriteNumber(sec);
							LCD_SendString(" SEC ");
						}
						
						TIMER0_voidDelay1Sec();
					}
					
					LCD_SendCommand(0x01);
					LCD_SendString(" FINAL WARNING! ");
					_delay_ms(2000);
					LCD_SendCommand(0x01);
					LCD_SendString(" ENTER PIN: ");
					GoToXY(0,1);
				}
				
				else if(wrong_PIN >= 4)
				{
					LCD_SendCommand(0x01);
					LCD_SendString("     ALERT   ");
					GoToXY(0,1);
					LCD_SendString(" CALLING 911...  ");
					
					while(1)
					{
						DIO_voidSetPinValue(DPORTD, PIN7, HIGH);
						_delay_ms(200);
						DIO_voidSetPinValue(DPORTD, PIN7, LOW);
						_delay_ms(200);
					}
				}
			}
		}
	}
	
	
}


void Light_Switch(u8 mode)
{
	Light_mode=mode;
	DIO_voidSetPinValue(DPORTD,PIN6,HIGH);
	_delay_ms(500);
	DIO_voidSetPinValue(DPORTD,PIN6,LOW);
}

ISR(INT0_vect)
{
	if(Light_mode==ON)
	{
		DIO_voidSetPinValue(DPORTA,PIN4,HIGH);
	}
	else if(Light_mode==OFF)
	{
		DIO_voidSetPinValue(DPORTA,PIN4,LOW);
	}
	else
	{
		/*NOCODE*/
	}
	
}





u16 Temp_sensor (void){
	u16 adc1_value  = ADC_u16Read(ADC1);
	u32 VOLT1_value = ((u32)adc1_value*5000UL)/1024UL;
	
	if(VOLT1_value>270){
		Current_Room_Tempreature = HOT;
	}
	else if(VOLT1_value<=270&&VOLT1_value>180){
		Current_Room_Tempreature = WARM;
	}
	else if(VOLT1_value<=180){
		Current_Room_Tempreature = COLD;
	}
	else{
		/*NOCODE*/
	}
	return (VOLT1_value+1UL)/10UL ; //+1UL  ???? ?? ?? ?????? ??????? ??????? ??????? ??????? ???????? ????? ????? ???
}

void light_sensor (void){
	u16 adc0_value  = ADC_u16Read(ADC0);
	u16 VOLT0_value = ((u32)adc0_value*5000UL)/1024UL;

	if(VOLT0_value>3500){
		Current_Room_Light=LIGHT_MORNING; //LDR resistance is small and the voltage across ADC is high
	}
	else if(VOLT0_value<=3500&&VOLT0_value>1500){
		Current_Room_Light=LIGHT_AFTERNOON;
	}
	else if(VOLT0_value<=1500&&VOLT0_value>0){
		Current_Room_Light=LIGHT_EVENING; //LDR resistance is large and the voltage across ADC is low
	}
	else {
		/*NOCODE*/
	}
}