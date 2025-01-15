#include <reg51.h>
#include <intrins.h>
sbit crot1 = P3^0;
sbit crot2 = P3^1;
char i = 0;
char j = 0;
unsigned char tmp1 = ~0x3f; 
unsigned char tmp2 = ~0x3f; 
unsigned char led[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void delay(unsigned int i)
{
	unsigned int j;
	for (; i >0; i--)
	{
		for (j = 124; j > 0; j--);
	}
}	

void main()
{
	//定时器初始化
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xD0;		//设置定时初值
	TH0 = 0x6F;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	EA = 1; 	//总中断打开
	ET0 = 1;	//允许T0中断
	TR0 = 1;	//启动定时器T0
	
	// /INT0初始化
	IT0 = 1;
	EX0 = 1;
	// /INT1初始化
	IT1 = 1;
	EX1 = 1;
	
	EA = 1;	//中断总开关
	while(1)
	{
		P3 = 0xfd;
		P2 = tmp2;
		delay(15);
		P3 = 0xfe;
		P2 = tmp1;	
		delay(15);
	};
}

void timer0() interrupt 1
{	
	TR0 = 0;
	TL0 = 0xD0;		//设置定时初值
	TH0 = 0x5F;		//设置定时初值
	i++;
	if(i == 20)	//一秒
	{
		
		tmp1 = ~led[(j+1) % 10];
		j++;
		tmp2 = ~led[j / 10];
		if (j == 60)
		{
			 j = 0;
		}
		i = 0;
	}
	TR0 = 1;
}
void int0_int() interrupt 0
{
	TR0 = ~TR0;
}

void int1_int() interrupt 2
{
	TR0 = 0;			//关定时器
	TL0 = 0xD0;		//设置定时初值
	TH0 = 0x5F;		//设置定时初值
	TF0 = 0;
	//显示清零
	tmp1 = ~0x3f; 
	tmp2 = ~0x3f;
	i = 0;
	j = 0;
}