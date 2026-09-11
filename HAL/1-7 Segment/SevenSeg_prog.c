#include "Std_Types.h"
#include "Bit_Math.h"

#include "DIO_int.h"

#include "SevenSeg_config.h"
#include "SevenSeg_private.h"
#include "SevenSeg_int.h"

u8 SevSeg_u8Numbers [10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void SevSegment_voidSetValue(u8 NUM,u8 PortID ,u8 Type)
{
    if(NUM <= 9)
    {
        if(Type == COMMON_CATHODE)
        {
            DIO_voidSetPortValue(PortID, SevSeg_u8Numbers[NUM]);
        }
        else
        {
            DIO_voidSetPortValue(PortID, ~SevSeg_u8Numbers[NUM]);
        }
    }
}
