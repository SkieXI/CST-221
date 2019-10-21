#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long u32;
typedef long s32;
typedef unsigned short u16;
typedef short s16;
typedef usigned char u8;

u32 ClearBit_u32(u32 data, u8 bit);


{
u32 myUnsignedData = 2147483648;

printf("mnyUnsignedData = 0x%08X", myUnsignedData);
printf("\nmyUnsignedData shifted 31 = 0x%08X", myUnsignedData >> 31);
printf("\n");

}
pringf(

s32 myData = 0x800000000;

s32 maskedData = (myData & 0x7FFFFFFF);

maskedData >>= 31;

maskedData |= 0x800000000;

u32 rawData = 0;

printf("\nrawData = 0x%08X", rawData -rawData);


printf("\nOriginal myData = 0x%08X", Mydata);
printf("\nmyData masked and shifted 31 = 0x%08X", maskedData);


//New Code
u32 ClearBit_u32(u32, u8 bit)
{
    u32 bitMask = 0x1 << bit;
    
    
}

pritnf("\n");
