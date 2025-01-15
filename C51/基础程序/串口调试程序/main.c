#include <REGX52.H>
#define uchar unsigned char
uchar rec = 0;
sfr AUXR =0x8E;
void main(void)
{
	SCON = 0x50;
	TMOD = 0x20;	
	TL1 = 0xfd;
	TH1 = 0xfd;
	ES = 1;
	EA = 1;
	
	
	
	TR1 = 1;	
	while(1);
}

void serial_routine() interrupt 4
{
	if (T1)
	{
		T1 = 0;
	}
	if (RI)
	{
		RI = 0;
		rec = SBUF;
		switch(rec)
		{
			case 1:P2 = ~0x01;break;
			case 2:P2 = ~0x02;break;
			case 3:P2 = ~0x04;break;
			case 4:P2 = ~0x08;break;
			case 5:P2 = ~0x10;break;
			case 6:P2 = ~0x20;break;
			case 7:P2 = ~0x40;break;
			case 8:P2 = ~0x80;break;
			default:SBUF = 0x0e; P2 = 0xaa;
		}
	}
}
