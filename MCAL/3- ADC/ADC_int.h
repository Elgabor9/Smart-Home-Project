#ifndef ADC_int_h
#define ADC_int_h

#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6
#define ADC7 7

void ADC_voidInit(void);
u16 ADC_u16Read(u8 Channel);

#endif