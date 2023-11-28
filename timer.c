#include"header.h"
// indicate LED on as an error
#define errorLED (1 << 19);
 
void delay_ms(u32 ms)
{
	if(VPBDIV % 4 == 3)
	{
		IODIR0 |= errorLED;
		IOCLR0 = errorLED; 
		return;	
	}	
	T0TC = T0PC = 0;
	T0PR = freq[VPBDIV % 4] * 1000 - 1;
	T0TCR = 1;
	while(T0TC < ms);
}

void delay_sec(u32 sec)
{
	if(VPBDIV % 4 == 3)
	{
		IODIR0 |= errorLED;
		IOCLR0 = errorLED; 
		return;	
	}
	T0TC = T0PC = 0;
	T0PR = freq[VPBDIV % 4] * 1000000 - 1;
	T0TCR = 1;	
	while(T0TC < sec);
}
