#include <REGX51.H>
typedef unsigned char u8;
unsigned char led[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
u8 i = 0;

void Delay(unsigned int i);
u8 MatrixKey(void);
void Display(u8 num);

void main()
{
	u8 ret = 0;
	u8 m,n, tmp = 99;
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xD0;		//设置定时初值
	TH0 = 0x6F;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	EA = 1; 	//总中断打开
	ET0 = 1;	//允许T0中断
	TR0 = 0;
	while(1)
	{
		ret = MatrixKey();
		if (ret)
		{
			
			tmp = ret;
			P3_2 = 0;
			TR0 = 1;
			m = tmp /10;	//取十位
			n = tmp % 10;	//取个位
		}
		if(tmp)
		{
			if (tmp == 99)		//默认显示
			{
				P0 = 0xfd; 		//十位
				P2 = 0xbf;
				Delay(15);
				
				P0 = 0xfe;	//个位
				P2 = 0xbf;	
				Delay(15);
			}
		else
		{
			P0 = 0xfd; 		//十位
			P2 = ~led[m];
			Delay(15);
			
			P0 = 0xfe;	//个位
			P2 = ~led[n];	
			Delay(15);
		}
		}
	}
}


unsigned char MatrixKey()
{
	unsigned char KeyNumber=0;
	
	P1=0xFF;// 1111 1111 全部置高电平默认
	P1_3=0; // 矩阵按键第一行扫描
	if(P1_7==0){Delay(15);KeyNumber=1; while(!P1_7);}
	if(P1_6==0){Delay(15);KeyNumber=5; while(!P1_6);}
	if(P1_5==0){Delay(15);KeyNumber=9; while(!P1_5);}
	if(P1_4==0){Delay(15);KeyNumber=13;while(!P1_4);}
										 
	P1=0xFF;           
	P1_2=0; // 矩阵按键二
	if(P1_7==0){Delay(15);KeyNumber=2; while(!P1_7);}
	if(P1_6==0){Delay(15);KeyNumber=6; while(!P1_6);}
	if(P1_5==0){Delay(15);KeyNumber=10;while(!P1_5);}
	if(P1_4==0){Delay(15);KeyNumber=14;while(!P1_4);}
										 
	P1=0xFF;           
	P1_1=0; // 矩阵按键三
	if(P1_7==0){Delay(15);KeyNumber=3; while(!P1_7);}
	if(P1_6==0){Delay(15);KeyNumber=7; while(!P1_6);}
	if(P1_5==0){Delay(15);KeyNumber=11;while(!P1_5);}
	if(P1_4==0){Delay(15);KeyNumber=15;while(!P1_4);}
										 
	P1=0xFF;           
	P1_0=0; // 矩阵按键四
	if(P1_7==0){Delay(15);KeyNumber=4; while(!P1_7);}
	if(P1_6==0){Delay(15);KeyNumber=8; while(!P1_6);}
	if(P1_5==0){Delay(15);KeyNumber=12;while(!P1_5);}
	if(P1_4==0){Delay(15);KeyNumber=16;while(!P1_4);}
	
	return KeyNumber;
}

void Delay(unsigned int i)
{
	unsigned int j;
	for (; i >0; i--)
	{
		for (j = 124; j > 0; j--);
	}
}	

void timer0() interrupt 1
{	
	TL0 = 0xD0;		//设置定时初值
	TH0 = 0x5F;		//设置定时初值
	i++;
	if(i == 12)	//一秒
	{
		P3_2 = 1;
		i = 0;
	}
}