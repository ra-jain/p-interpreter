#include"header.h"

void uart0_init(u32 baudrate)
{
	int pclk, result;
	pclk = freq[VPBDIV % 4] * 1000000;
	result = pclk / (baudrate * 16);

	PINSEL0 |= 0x5;
	U0LCR = 0x83;
	U0DLL = result & 0xFF;
	U0DLM = (result & 0xFF00) >> 8;
	U0LCR = 0x03;
}

void uart0_tx(u8 data)
{
	U0THR = data;
	while((U0LSR >> 5 & 1) == 0);	
}

u8 uart0_rx(void)
{
	while((U0LSR & 1) == 0);
	return U0RBR;
}

void uart0_tx_string(char * data)
{
	while(*data){
		U0THR = *data;
		while((U0LSR >> 5 & 1) == 0);
		data++;
	}	
}

void uart0_tx_int(int data)
{
	int res, r;
	char count;
	if (data == 0)
	{
		uart0_tx('0');
		return;
	}
	if (data < 0)
	{
		uart0_tx('-');
		data = data * -1;
	}
	count = 0;
	for(res = 0; data; data = data / 10)
	{
		r = data % 10;	
		res = res * 10 + r;
		count++;
	}
	while(res)
	{
		r = res % 10;
		uart0_tx(r + 48);
		res = res / 10;
		count--;
	}
	while(count)
	{
		uart0_tx('0');
		count--;
	}	
}

void uart0_tx_float(float data)
{
	char a[50];
	sprintf(a,"%f",data);
	uart0_tx_string(a);
}


void uart0_tx_hex(int data)
{
	int i, flag, res;
	flag = 0;
	for(i = 7; i>= 0; i--)
	{
		res = ((data >> (4*i)) & 0xF);
		if(res > 0)
		{
			flag = 1;
		}
		if(flag)
		{
			if(res < 10)
			{
				U0THR = '0' + res;
				while((U0LSR >> 5 & 1) == 0);
			}
			else 
			{
				U0THR = 'A' + res - 10;
				while((U0LSR >> 5 & 1) == 0);
			}	
		} 
	}	
}



void uart0_init_interrupt(u32 baudrate, u8 priority)
{
	uart0_init(baudrate);
	
}
