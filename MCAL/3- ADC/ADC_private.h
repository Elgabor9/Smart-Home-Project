#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#define ADMUX    *((volatile u8 *)0x27)
#define ADCSRA   *((volatile u8 *)0x26)
#define ADCH     *((volatile u8 *)0x25)
#define ADCL     *((volatile u8 *)0x24)
#define ADC_DATA *((volatile u16*)0x24)

#define REFS1 7
#define REFS0 6
#define ADLAR 5

#define ADEN  7
#define ADSC  6
#define ADATE 5
#define ADIF  4
#define ADIE  3
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0

#endif