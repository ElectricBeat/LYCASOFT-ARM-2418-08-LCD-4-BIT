#include <lpc214x.h>
#include "LPC2148_delay.h"

#define RS 0x00000100;
#define EN 0x00000200;

void Lcd_Command(char cmd)                          
{
	IOCLR0 = 0XFF;
	IOSET0 = (cmd & 0XF0);
	IOCLR0 = RS;
	IOSET0 = EN;
	delay(5);
	IOCLR0 = EN;
	
	IOCLR0 = 0XFF;
	IOSET0 = ((cmd<<4) & 0XF0);
	IOCLR0 = RS;
	IOSET0 = EN;
	delay(5);
	IOCLR0 = EN;
}

void Lcd_Data(char Data)
{
	IOCLR0 = 0XFF;
	IOSET0 = (Data & 0XF0);
	IOSET0 = RS;
	IOSET0 = EN;
	delay(5);
	IOCLR0 = EN;
	
	IOCLR0 = 0XFF;
	IOSET0 = ((Data<<4) & 0XF0);
	IOSET0 = RS;
	IOSET0 = EN;
	delay(5);
	IOCLR0 = EN;
}

void Lcd_String(const unsigned char *Str)
{
	while(*Str)
	{
		Lcd_Data(*Str++);
	}
}

void Lcd_Intialization()
{
	Lcd_Command(0x02);
	Lcd_Command(0x28);
	Lcd_Command(0x06);
	Lcd_Command(0x0c);
}

int main()
{
	PINSEL0 = 0x00000000;
	IODIR0 = 0x3F0;
	
	Lcd_Intialization();
	
	while(1)
	{
		Lcd_Command(0x80);
		Lcd_String("LYCASOFT");
	}
}