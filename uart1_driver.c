#include"header.h"

void uart1_init(u32 baudrate)
{
	int pclk, result;
	pclk = freq[VPBDIV % 4] * 1000000;
	result = pclk / (baudrate * 16);

	PINSEL0 |= 0x5 << 16;
	U1LCR = 0x83;
	U1DLL = result & 0xFF;
	U1DLM = (result & 0xFF00) >> 8;
	U1LCR = 0x03;
}

void uart1_tx(u8 data)
{
	U1THR = data;
	while((U1LSR >> 5 & 1) == 0);	
}

u8 uart1_rx(void)
{
	while((U1LSR & 1) == 0);
	return U1RBR;
}
