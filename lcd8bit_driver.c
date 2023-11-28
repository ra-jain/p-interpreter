#include"header.h"
#define RS8 (1 << 11)
// RW is connected to ground
#define EN8 (1 << 10)
// data at 0 to 7 pins
void lcd8_init(void)
{
	IODIR0 = 0xCFF;
	lcd8_cmd(0x38);
	lcd8_cmd(0x01);
	lcd8_cmd(0x0E);												
}

void lcd8_cmd(u8 cmd)
{
	IOCLR0 = 0xCFF;
	IOSET0 = cmd;
	IOCLR0 = RS8;
	IOSET0 = EN8;
	delay_ms(2);
	IOCLR0 = EN8;
} 

void lcd8_data(u8 data)
{
	IOCLR0 = 0xCFF;
	IOSET0 = data;
	IOSET0 = RS8;
	IOSET0 = EN8;
	delay_ms(2);
	IOCLR0 = EN8;
}

void lcd8_string(char *s)
{
	while(*s) {
		lcd8_data(*s);
		s++;
	}	
} 

void lcd8_string_pos(char *s, u8 startingPos) {
	if(startingPos > 0x8F && startingPos < 0xC0)
	{
		startingPos = 0xCF - (0xC0 - startingPos) + 1;;
	}
	lcd8_cmd(startingPos);
	while(*s) {
		lcd8_data(*s);
		if(startingPos == 0x8F) {
			startingPos = 0x80;
			lcd8_cmd(startingPos);
		}
	
		if(startingPos == 0xCF) {
			startingPos = 0xC0;
			lcd8_cmd(startingPos);
		}
		s++;
		startingPos++;
	}
}

void lcd8_cgram_pattern(u8 * data, u8 pos)
{
	int i;
	lcd8_cmd(pos);
	for(i = 0; i < 7; i++)
	{
		lcd8_data(data[i]);
	}			
}

void lcd8_int(int data)
{
	int res, r;
	char count;
	if (data == 0)
	{
		lcd8_data('0');
		return;
	}
	if (data < 0)
	{
		lcd8_data('-');
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
		lcd8_data(r + 48);
		res = res / 10;
		count--;
	}
	while(count)
	{
		lcd8_data('0');
		count--;
	}	
}
