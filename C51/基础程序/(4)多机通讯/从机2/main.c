#include<reg51.h>
#include<intrins.h>

unsigned char code key_code[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
#define b_addr 21
void send() interrupt 0
{
	SBUF=2;
	while(TI==0);
	TI=0;
}

void play() interrupt 4
{
	if(T0)
	{
	RI=0;
	if(RB8==1)
	{
		if(SBUF==b_addr)
		{
			SM2=0;
		}
	}
	else
	{
		P1=key_code[SBUF];
		SM2=1;
	}
	}

}
void main()
{
	IT0=1;EX0=1;
	SCON=0xf0;
	TMOD=0x20;
	TH1=TL1=0xfd;//²¨ÌØÂÊ9600
	TR1=1;
	ES=1;
	EA=1;
	P1=key_code[0];
	while(1);
}
