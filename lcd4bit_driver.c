#include"header.h"
#define RS4 (1 << 17)
#define RW4 (1 << 18)
#define EN4 (1 << 19)
// data at 20 to 23 pins

void lcd4_init(void)
{
	IODIR1 = 0xFE0000;
	lcd4_cmd(0x03);
	lcd4_cmd(0x02);
	lcd4_cmd(0x28);
	lcd4_cmd(0x01);
	lcd4_cmd(0x0E);												
}

void lcd4_cmd(u8 cmd)
{
	unsigned int temp;
	IOCLR1 = 0xFE0000;
	temp = (cmd & 0xF0)<< 16;
	IOSET1 = temp;
	IOCLR1 = RS4;
	IOCLR1 = RW4;
	IOSET1 = EN4;
	delay_ms(2);
	IOCLR1 = EN4;

	IOCLR1 = 0xFE0000;
	temp = (cmd & 0x0F)<< 20;
	IOSET1 = temp;
	IOCLR1 = RS4;
	IOCLR1 = RW4;
	IOSET1 = EN4;
	delay_ms(2);
	IOCLR1 = EN4;
} 

void lcd4_data(u8 data)
{
	unsigned int temp;
	IOCLR1 = 0xFE0000;
	temp = (data & 0xF0)<< 16;
	IOSET1 = temp;
	IOSET1 = RS4;
	IOCLR1 = RW4;
	IOSET1 = EN4;
	delay_ms(2);
	IOCLR1 = EN4;

	IOCLR1 = 0xFE0000;
	temp = (data & 0x0F)<< 20;
	IOSET1 = temp;
	IOSET1 = RS4;
	IOCLR1 = RW4;
	IOSET1 = EN4;
	delay_ms(2);
	IOCLR1 = EN4;
}

void lcd4_string(char *s)
{
	while(*s) {
		lcd4_data(*s);
		s++;
	}	
} 

void lcd4_string_pos(char *s, u8 startingPos) {
	if(startingPos > 0x8F && startingPos < 0xC0)
	{
		startingPos = 0xCF - (0xC0 - startingPos) + 1;;
	}
	lcd4_cmd(startingPos);
	while(*s) {
		lcd4_data(*s);
		if(startingPos == 0x8F) {
			startingPos = 0x80;
			lcd4_cmd(startingPos);
		}
	
		if(startingPos == 0xCF) {
			startingPos = 0xC0;
			lcd4_cmd(startingPos);
		}
		s++;
		startingPos++;
	}
}

void lcd4_cgram_pattern(u8 * data, u8 pos)
{
	int i;
	lcd4_cmd(pos);
	for(i = 0; i < 7; i++)
	{
		lcd4_data(data[i]);
	}			
}

void lcd4_int(int data)
{
	int res, r;
	char count;
	if (data == 0)
	{
		lcd4_data('0');
		return;
	}
	if (data < 0)
	{
		lcd4_data('-');
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
		lcd4_data(r + 48);
		res = res / 10;
		count--;
	}
	while(count)
	{
		lcd4_data('0');
		count--;
	}	
}

void lcd4_float(float data)
{
	char a[50];
	sprintf(a,"%.2f",data);
	lcd4_string(a);
}
