#include<LPC21xx.h>
#include<stdio.h>
typedef unsigned int u32;
typedef unsigned char u8;
extern const char freq[4];
extern const char bitSize[8];

/*timer driver*/
// indicate LED on P0.19 as an error
extern void delay_ms(u32 ms);
extern void delay_sec(u32 sec);

/*uart0 driver*/
// indicate LED on P0.19 as an error if not initialised lcd
//Use P0.0 Txd and P0.1 RxD after init

extern void uart0_init(u32 baudrate);
extern void uart0_tx(u8 data);
extern u8 uart0_rx(void);
extern void uart0_tx_string(char * data);
extern void uart0_tx_int(int data);
extern void uart0_tx_hex(int data);
extern void uart0_tx_float(float data);
/*uart1 driver*/
// indicate LED on P0.19 as an error if not initialised lcd
//Use P0.8 Txd and P0.9 RxD after init 
extern void uart1_init(u32 baudrate);
extern void uart1_tx(u8 data);
extern u8 uart1_rx(void);

/*lcd driver*/
// indicate LED on P0.19 as an error if not initialised lcd
// Uses P1.17 as RS 
// Uses P1.18 as RW 
// Uses P1.19 as EN 
// Uses P1.20 to P1.23 pins for data and commands
extern void lcd4_init(void);
extern void lcd4_cmd(u8 cmd);
extern void lcd4_data(u8 data);
extern void lcd4_int(int data);
extern void lcd4_string_pos(char *s, u8 startingPos);
extern void lcd4_string(char *s);
extern void lcd4_cgram_pattern(u8 * data, u8 pos);
void lcd4_float(float data);

/*adc driver*/
// indicate LED on P0.19 as an error if not initialised adc
// P0.27 AIN0
// P0.28 AIN1
// P0.29 AIN2
// P0.30 AIN3
extern void adc_init(u8 bits);
extern u32 adc_read(u8 channel);


/*lcd driver 8 bit*/
// indicate LED on P0.19 as an error if not initialised lcd
#define RS (1 << 11)
// RW is connected to ground
#define EN (1 << 10)
// Uses P0.11 as RS 
// Uses P0.10 as EN 
// Uses P0.0 to P0.7 pins for data and commands
extern void lcd8_init(void);
extern void lcd8_cmd(u8 cmd);
extern void lcd8_data(u8 data);
extern void lcd8_int(int data);
extern void lcd8_string_pos(char *s, u8 startingPos);
extern void lcd8_string(char *s);
extern void lcd8_cgram_pattern(u8 * data, u8 pos);
