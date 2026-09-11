#ifndef TIMER1_INT_H
#define TIMER1_INT_H

void TIMER1_voidInitServo(void);

void TIMER1_voidSetServoAngle(u8 Angle);

//PWM
void PWM_Init(void);
void Motor_SetSpeed(u8 duty_cycle);

#endif