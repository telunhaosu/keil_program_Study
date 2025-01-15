#include <REGX51.H>
#include <intrins.h>
void Delay5000ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 38;
	j = 0;
	k = 118;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}




void main()
{
	
	
	while(1)
	{
//		P2 = 0x00;
//		Delay5000ms();
//		P2 = 0xff;
//		Delay5000ms();
	}
}
