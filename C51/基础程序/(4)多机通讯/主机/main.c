#include<reg51.h>
#include<intrins.h>

#define a_addr 20//设置从机1的地址
#define b_addr 21//设置从机2的地址

unsigned char code key_code[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
unsigned char num1=0;//发送给从机1
unsigned char num2=0;//发送给从机2

void send_a() interrupt 0
{
	TB8=1;
	SBUF=a_addr;
	while(TI==0);
	TI=0;
	TB8=0;
	num1=(num1+1)%16;
	SBUF=num1;
	while(TI==0);
	TI=0;
}

void send_b() interrupt 2
{
	TB8=1;
	SBUF=b_addr;
	while(TI==0);
	TI=0;
	TB8=0;
	num2=(num2+1)%16;
	SBUF=num2;
	while(TI==0);
	TI=0;
}
void play() interrupt 4
{
		P1=key_code[SBUF];
		RI=0;
}
void main()
{
	IT0=1;EX0=1;
	IT1=1;EX1=1;
	ES = 1;
	EA=1;//打开中断
	TMOD=0x20;
	SCON=0xf8;//方式3 SM2=1 许接
	SM2 = 0;
	TH1=TL1=0xfd;//波特率9600
	TR1=1;
	P1=key_code[0];
	while(1);
}
