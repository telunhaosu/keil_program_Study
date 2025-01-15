#include <REGX51.H>
#include <intrins.h>
unsigned char m = 0;
unsigned char n = 0;
unsigned char tmp1;
unsigned char tmp2;
void EX0_Init(void);
void EX1_Init(void);
void Delay300ms();
void main()
{
	EX0_Init();
	EX1_Init();
	EA = 1;
	while(1)
	{
		P2 = 0xff;
	}
}

//外部中断0初始化
void EX0_Init(void)
{

	//设置触发方式 外部中断0
	IT0 = 1; //下降沿触发 随后IE0置1
	EX0 = 1; // 子开关 IE:中断允许寄存器 
	PX0 = 0; //中断优先级-低
}
//外部中断1初始化
void EX1_Init(void)
{

	//设置触发方式 外部中断0
	IT1 = 1;	//下降沿触发 随后IE0置1
	EX1 = 1;	// 子开关 IE:中断允许寄存器  
	PX1 = 1;	//中断优先级-高
}

/*
1.中断服务函数一定是一个没有返回值的函数
2.中断服务函数一定是一个没有参数的函数
3.中断服务函数函数名后跟关键字 interrupt
4.interrupt n 0-4	8*n + 0013H = 中断向量入口地址
5.中断服务函数不能被主程序或其他程序所调用
6.n 后跟 sing m(0-3)工作寄存器组
*/
void EX0_ISR(void) interrupt 0
{
	tmp1 = 0x55;
	for ( m = 0; m < 8; m++)
	{
		tmp1 = _cror_(tmp1, 1);
		P2 = tmp1;
		Delay300ms();
	}
}
void EX1_ISR(void) interrupt 2
{
	tmp2 = 0xfe;
		for ( n = 0; n < 8; n++)
	{
		tmp2 = _cror_(tmp2, 1);
		P2 = tmp2;
		Delay300ms();
	}
}

void Delay300ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 3;
	j = 72;
	k = 161;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

