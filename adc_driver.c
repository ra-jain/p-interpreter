#include"header.h"

u32 maxValue;
void adc_init(u8 bits)
{
	u8 index, i;	
	for(index = 0;index < 8;index++)
	{
		if(bits == bitSize[index])
		{
			break;
		}
	}
	maxValue = 0;
	for(i = 0;i < bits;i++)
	{
		maxValue |= (1 << i);
	}
	ADCR = 0x200400 | (index << 17);
}


u32 adc_read(u8 channel)
{
	u32 result = 0;
	ADCR |= (1 << channel);
	ADCR |= (1 << 24);
	while((ADDR >> 31 & 1) == 0);
	result = (ADDR >> 6) & maxValue;
	ADCR ^= (1 << 24);
	ADCR ^= (1 << channel);
	return result;
}
