#include <REGX51.H>
#include "Sys.h"
#include "SEG_8.h"
#include "DS1302.h"
#include "DS18B20.h"
#include "Delay.h"

#define ROLL 1
#define TIME 2
#define DATE 3
#define TEMP 4

#define ROM_0 0
#define ROM_1 1

uchar Flag = ROLL;			//显示模式标志位
uchar Key_Counter;			//按键计数次数变量
uchar Timer0_Counter;		//定时器0计数变量
uchar SEG_ShiftFlag;		//数码管滚动判断位
uchar ConvertT_Counter;		//温度转换时间计次

void Timer0_Init(void);
void Timer1_Init(void);
void EXT0_Init(void);

void main(void)
{
	
	uchar Num[8], Silding_Num[28];
	int T0, T1;
	uchar Ret;
	
	DS18B20_Match_ConfigT(0x1f, ROM_0);
	DS18B20_Match_ConvertT(ROM_0);

	DS18B20_Match_ConfigT(0x1f, ROM_1);
	DS18B20_Match_ConvertT(ROM_1);
	
	SEG_Init(Num);
	DS1302_Init();
	Timer0_Init();
	Timer1_Init();
	EXT0_Init();

	SEG_Mode_Select(0x00);
	
	while(1)
	{
		if (Flag == ROLL)
		{
			uchar i=0, j;
			while (Silding_Num[i+7]!=0xFE)
			{
				Silding_Num[27] = 0xFE; //作结束字符
				if (Flag == ROLL)
				{
					
					//---------------------时间部分----------------------//
					//秒
					Ret = DS1302_ReadByte(0x81);
					Silding_Num[7] = SEG_Char[BCDCode_GetUnit(Ret)];
					Silding_Num[6] = SEG_Char[BCDCode_GetDecade(Ret)];
					Silding_Num[5] = 0xBF;	//字符'-'，作间隔
					//分
					Ret = DS1302_ReadByte(0x83);
					Silding_Num[4] = SEG_Char[BCDCode_GetUnit(Ret)];
					Silding_Num[3] = SEG_Char[BCDCode_GetDecade(Ret)];
					Silding_Num[2] = 0xBF;	//字符'-'，作间隔
					//时
					Ret = DS1302_ReadByte(0x85);
					Silding_Num[1] = SEG_Char[BCDCode_GetUnit(Ret)];
					Silding_Num[0] = SEG_Char[BCDCode_GetDecade(Ret)];
					Silding_Num[8] = 0xF7;	//字符'_'，作间隔
					//日
					Ret = DS1302_ReadByte(0x87);
					Silding_Num[16] = SEG_Char[BCDCode_GetUnit(Ret)];
					Silding_Num[15] = SEG_Char[BCDCode_GetDecade(Ret)];
					Silding_Num[14] = 0xBF;	//字符'-'，作间隔
					//月
					Ret = DS1302_ReadByte(0x89);
					Silding_Num[13] = SEG_Char[BCDCode_GetUnit(Ret)];
					Silding_Num[12] = SEG_Char[BCDCode_GetDecade(Ret)];
					Silding_Num[11] = 0xBF;	//字符'-'，作间隔
					//年
					Ret = DS1302_ReadByte(0x8D);
					Silding_Num[10] = SEG_Char[BCDCode_GetUnit(Ret)];
					Silding_Num[9] 	= SEG_Char[BCDCode_GetDecade(Ret)];
					Silding_Num[17] = 0xF7;	//字符'_'，作间隔
					
					for (j=0;j<8;j++)
					{
						Num[j]=Silding_Num[i+j];
					}
					//---------------------温度部分----------------------//
					if (ConvertT_Counter >= 2)	//判断是否留有足够的温度转换时间
					{
						TR1 = 0;	ConvertT_Counter = 0; 	//停止计时并清零计数标志位ConvertT_Counter
						//ROM_0
						T0 = DS18B20_Match_ReadT(ROM_0);
						if (T0 < 0)	//判断正负
						{
							T0 = -T0;
							Silding_Num[18] = 0xBF;			//显示"-"
						}
						else
						{
							Silding_Num[18] = 0xFF;	  	 	//显示"空"
						}
						Silding_Num[19] = SEG_Char[T0/100];
						Silding_Num[20] = SEG_Char[T0/10%10];
						Silding_Num[21] = SEG_Char[T0%10];
						DS18B20_Match_ConvertT(ROM_0);
						Silding_Num[22] = 0xF7;	//字符'_'，作间隔
						SEG_Display(Num);	//DS18B20的match指令时间较长，所以需要在读取每个ROM后添加数码管刷屏显示代码，确保显示稳定
						//ROM_1
						T1 = DS18B20_Match_ReadT(ROM_1);
						if (T1 < 0)	//判断正负
						{
							T1 = -T1;
							Silding_Num[23] = 0xBF;			//显示"-"
						}
						else
						{
							Silding_Num[23] = 0xFF;	   		//显示"空"
						}
						Silding_Num[24] = SEG_Char[T1/100];
						Silding_Num[25] = SEG_Char[T1/10%10];
						Silding_Num[26] = SEG_Char[T1%10];
						DS18B20_Match_ConvertT(ROM_1);
						SEG_Display(Num);
						TR1 = 1;			//开启计时
					}
					SEG_Display(Num);
					if (SEG_ShiftFlag)		//判断数码管是否向左滚动
					{	
						i++;
						SEG_ShiftFlag=0;
					}
				}
				else
				{break;}	
			}
		}
		else if (Flag == TIME)
		{
			//秒
			Ret = DS1302_ReadByte(0x81);
			Num[7] = SEG_Char[BCDCode_GetUnit(Ret)];
			Num[6] = SEG_Char[BCDCode_GetDecade(Ret)];
			Num[5] = 0xBF;	//字符'-'，作间隔
			//分
			Ret = DS1302_ReadByte(0x83);
			Num[4] = SEG_Char[BCDCode_GetUnit(Ret)];
			Num[3] = SEG_Char[BCDCode_GetDecade(Ret)];
			Num[2] = 0xBF;	//字符'-'，作间隔
			//时
			Ret = DS1302_ReadByte(0x85);
			Num[1] = SEG_Char[BCDCode_GetUnit(Ret)];
			Num[0] = SEG_Char[BCDCode_GetDecade(Ret)];
			
			SEG_Display(Num);
		}
		else if (Flag == DATE)
		{
			//日
			Ret = DS1302_ReadByte(0x87);
			Num[7] = SEG_Char[BCDCode_GetUnit(Ret)];
			Num[6] = SEG_Char[BCDCode_GetDecade(Ret)];
			Num[5] = 0xBF;	//字符'-'，作间隔
			//月
			Ret = DS1302_ReadByte(0x89);
			Num[4] = SEG_Char[BCDCode_GetUnit(Ret)];
			Num[3] = SEG_Char[BCDCode_GetDecade(Ret)];
			Num[2] = 0xBF;	//字符'-'，作间隔
			//年
			Ret = DS1302_ReadByte(0x8D);
			Num[1] = SEG_Char[BCDCode_GetUnit(Ret)];
			Num[0] = SEG_Char[BCDCode_GetDecade(Ret)];
			SEG_Display(Num);
		}
		else if (Flag == TEMP)
		{	
			if (ConvertT_Counter >= 2)	//判断是否留有足够的转换时间
			{
				//停止计时并清零计数标志位ConvertT_Counter
				TR1 = 0;	ConvertT_Counter = 0;
				//ROM_0
				T0 = DS18B20_Match_ReadT(ROM_0);
				if (T0 < 0)	//判断正负
				{
					T0 = -T0;
					Num[0] = 0xBF;		//显示"-"
				}
				else
				{
					Num[0] = 0xFF;	   //显示"空"
				}
				Num[1] = SEG_Char[T0/100];
				Num[2] = SEG_Char[T0/10%10];
				Num[3] = SEG_Char[T0%10];
				DS18B20_Match_ConvertT(ROM_0);
				SEG_Display(Num);
				//ROM_1
				T1 = DS18B20_Match_ReadT(ROM_1);
				if (T1 < 0)	//判断正负
				{
					T1 = -T1;
					Num[4] = 0xBF;		//显示"-"
				}
				else
				{
					Num[4] = 0xFF;	   //显示"空"
				}
				Num[5] = SEG_Char[T1/100];
				Num[6] = SEG_Char[T1/10%10];
				Num[7] = SEG_Char[T1%10];
				DS18B20_Match_ConvertT(ROM_1);
				SEG_Display(Num);
				TR1 = 1;
			}
			SEG_Display(Num);
		}
	}
}
/**
  * @brief  定时器0初始化函数
  */ 
void Timer0_Init(void)		//50毫秒@12.000MHz
{
	Timer0_Counter = 0;
	SEG_ShiftFlag = 0;		
	EA = 1;
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0xB0;				//设置定时初始值
	TH0 = 0x3C;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	ET0 = 1;				//使能定时器0中断
	TR0 = 1;				//定时器0开始计时
}

/**
  * @brief  滚动显示模式下，设置每次滚动时间隔设置
  */ 
void Timer0_ISR(void) interrupt 1
{
	
	TL0 = 0xB0;				//设置定时初始值
	TH0 = 0x3C;				//设置定时初始值
	Timer0_Counter++;
	if (Timer0_Counter == 10)
	{
		Timer0_Counter = 0;
		SEG_ShiftFlag = 1;
	}
}

/**
  * @brief  定时器1初始化函数
  */ 
void Timer1_Init(void)		//50毫秒@12.000MHz
{
	EA=1;
	TMOD &= 0x0F;			//设置定时器模式
	TMOD |= 0x10;			//设置定时器模式
	TL1 = 0xB0;				//设置定时初始值
	TH1 = 0x3C;				//设置定时初始值
	TF1 = 0;				//清除TF1标志
	TR1 = 1;				//定时器1开始计时
	ET1=1;					//T1中断子开关
}

/**
  * @brief  ConvertT_Counter：定时器1计次变量
  */ 
void Timer1_ISR(void)	interrupt 3
{
	TL1 = 0xB0;				//设置定时初始值
	TH1 = 0x3C;				//设置定时初始值
	ConvertT_Counter++;
}

/**
  * @brief  外部中断0初始化函数，用于外部机械按键
  */ 
void EXT0_Init(void)
{
	EA = 1;		//打开中断总开关
    IT0 = 1;	//下降沿触发
	EX0 = 1;	//打开中断子开关
}

/**
  * @brief  机械按键外部中断服务函数，切换日期模式和时间
  */ 
void EXT0_Key_ISR(void) interrupt 0
{
	Key_Counter++;
	if (Key_Counter == 0) 	//刷屏显示模式
	{	
		Flag = ROLL;
		Timer0_Init();
		SEG_Mode_Select(0x00);
	}
	else if (Key_Counter ==  1)	//时间显示模式
	{
		Flag = TIME;
		TR0 = 0;
		SEG_Mode_Select(0x01);
	}
	else if(Key_Counter == 2)		//日期显示模式
	{
		Flag = DATE;
		TR0 = 0;
		SEG_Mode_Select(0x02);
	}
	else if(Key_Counter == 3)		//温度显示模式
	{
		Flag = TEMP;
		TR0 = 0;
		SEG_Mode_Select(0x03);
		Key_Counter = -1;
	}
}