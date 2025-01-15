#include <STC15F2K60S2.H>
#include <intrins.h>
#define SEG(X)	{P0 = X, P2 = (P2 & 0x1F | 0xE0); P2 &= 0x1F;}
#define COM(X)	{P0 = X, P2 = (P2 & 0x1F | 0xC0); P2 &= 0x1F;}	

void Delay500ms()		//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void main(void)
{
	while(1)
	{
		SEG(0xC0);
		COM(0x01);
		Delay500ms();
		SEG(0xC0);
		COM(0x02);
		Delay500ms();
	}
	
}