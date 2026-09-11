#ifndef _STEPMOTOR_int_h
#define _STEPMOTOR_int_h

#define CLOCK_WISE 0
#define COUNTER_WISE 1

void STEPMOTOR_init(void);

void FULL_STEP(u8 Direction);

void HALF_STEP(u8 Direction);



#endif