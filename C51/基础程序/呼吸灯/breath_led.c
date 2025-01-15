#include "reg52.h"
#define uint unsigned int
#define uchar unsigned char
void  delay(uint ms)
{
	uint i, j;
	for (i = ms; i > 0; i--)	//1ms
		for (j = 114; j > 0; j--);
}

void pwm(uchar n)
{
	
	P2 = 0x00;
	delay(n);
	P2 = 0xFF;
	delay(10 - n);
}

void main(void)
{
	while(1)
	{
			uchar i, j;
	for (i = 0; i <= 10; i++)
		pwm(i);
	for (j = 10; j >=0; j--)
		pwm(j);
	}
}
