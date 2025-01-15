#include <REGX51.H>
#include "Sys.h"
#include "NixieTupe.h"
#include "DS1302.h"
#include "DS18B20.h"
#include "Delay.h"

#define ROLL 1
#define TIME 2
#define DATE 3
#define TEMP 4

uchar Flag;	//模式标志
char S=0;	//按键计数

uchar SMG_ShiftBit;
uint  TimerCount;                                                             
                                                                             
void Timer0_Init(void)		//100微秒@11.0592MHz
{
	EA = 1;
	TMOD= 0x01;					//设置定时器模式
	TL0 = (65535-50000)%256;	//设置定时初始值
	TH0 = (65535-50000)%256;	//设置定时初始值
	TF0 = 0;					//清除TF0标志
	TR0 = 1;					//定时器0开始计时
}
void Show_Silding(uchar *Num_Silding);

int main(void)
{
	uchar Num[8];	//数码管显示数组
	uchar Ret, Sig;
	uint text;	///dashuiush
	uint my=1;
	uchar Num_Silding[25];
	Num_Silding[24] = 0x7F;
	

	Timer0_Init();
	DS1302_Init();
	
	EA = 1;		//打开总中断开关
	
	PX0 = 1;
    IT0 = 1;	//触发方式设置
	EX0 = 1;	//打开外部中断0
	
	PT0 = 0;
	ET0 = 1;
	
	NixieTupe_Mode_Select(0x01);	//默认为滚动显示
	Flag=1;

	while(1)
	{
		if (Flag == ROLL)
		{
			uchar i=0, j;
			while (Num_Silding[i+7]!=0x7F)
			{
				if (Flag == ROLL)
				{
					text = Read_Temperature(&Sig);
					for (j=0;j<8;j++)
					{
						Ret = DS1302_ReadByte(0x81);
						//秒
						Num_Silding[7] = LedChar[BCDCode_GetUnit(Ret)];
						Num_Silding[6] = LedChar[BCDCode_GetDecade(Ret)];
						Num_Silding[5] = 0xBF;	//字符'-'，作间隔
						//分
						Ret = DS1302_ReadByte(0x83);
						Num_Silding[4] = LedChar[BCDCode_GetUnit(Ret)];
						Num_Silding[3] = LedChar[BCDCode_GetDecade(Ret)];
						Num_Silding[2] = 0xBF;	//字符'-'，作间隔
						//时
						Ret = DS1302_ReadByte(0x85);
						Num_Silding[1] = LedChar[BCDCode_GetUnit(Ret)];
						Num_Silding[0] = LedChar[BCDCode_GetDecade(Ret)];
						
						Num_Silding[8] = 0xF7;	//字符'_'，作间隔
						
						Ret = DS1302_ReadByte(0x87);
						Num_Silding[16] = LedChar[BCDCode_GetUnit(Ret)];
						Num_Silding[15] = LedChar[BCDCode_GetDecade(Ret)];
						Num_Silding[14] = 0xBF;	//字符'-'，作间隔
						//月
						Ret = DS1302_ReadByte(0x89);
						Num_Silding[13] = LedChar[BCDCode_GetUnit(Ret)];
						Num_Silding[12] = LedChar[BCDCode_GetDecade(Ret)];
						Num_Silding[11] = 0xBF;	//字符'-'，作间隔
						//年
						Ret = DS1302_ReadByte(0x8D);
						Num_Silding[10] = LedChar[BCDCode_GetUnit(Ret)];
						Num_Silding[9] 	= LedChar[BCDCode_GetDecade(Ret)];
						
						Num_Silding[17] = 0xF7; //字符'_'，作间隔
						
						//温度显示
						if(Sig==1)
						{
							Num_Silding[18] = 0xBF;
						}
						else if(Sig==0)
						{
							Num_Silding[18] = 0xB9; //符号-|正号
						}
						Num_Silding[19] = LedChar[text/100];
						Num_Silding[20] = LedChar[((text/10)%10)];
						Num_Silding[21] = LedChar[(text%10)];
						Num_Silding[22] = 0x9C;
						Num_Silding[23] = 0xC6;
						Num_Silding[24] = 0x7F;
						
						Num[j]=Num_Silding[i+j];
					}
					NixieTupe_Static_Display(Num);
					if (SMG_ShiftBit)
					{
						i++;
						SMG_ShiftBit=0;
					}
				}
				else
				{
					break;
				}
			}
		}
		else if (Flag == TIME)
		{
			//秒
			Ret = DS1302_ReadByte(0x81);
			Num[7] = LedChar[BCDCode_GetUnit(Ret)];
			Num[6] = LedChar[BCDCode_GetDecade(Ret)];
			Num[5] = 0xBF;	//字符'-'，作间隔
			//分
			Ret = DS1302_ReadByte(0x83);
			Num[4] = LedChar[BCDCode_GetUnit(Ret)];
			Num[3] = LedChar[BCDCode_GetDecade(Ret)];
			Num[2] = 0xBF;	//字符'-'，作间隔
			//时
			Ret = DS1302_ReadByte(0x85);
			Num[1] = LedChar[BCDCode_GetUnit(Ret)];
			Num[0] = LedChar[BCDCode_GetDecade(Ret)];
			NixieTupe_Static_Display(Num);
		}
		else if (Flag == DATE)
		{
			//日
			Ret = DS1302_ReadByte(0x87);
			Num[7] = LedChar[BCDCode_GetUnit(Ret)];
			Num[6] = LedChar[BCDCode_GetDecade(Ret)];
			Num[5] = 0xBF;	//字符'-'，作间隔
			//月
			Ret = DS1302_ReadByte(0x89);
			Num[4] = LedChar[BCDCode_GetUnit(Ret)];
			Num[3] = LedChar[BCDCode_GetDecade(Ret)];
			Num[2] = 0xBF;	//字符'-'，作间隔
			//年
			Ret = DS1302_ReadByte(0x8D);
			Num[1] = LedChar[BCDCode_GetUnit(Ret)];
			Num[0] = LedChar[BCDCode_GetDecade(Ret)];
			NixieTupe_Static_Display(Num);
		}
		else if (Flag == TEMP)
		{
			text = Read_Temperature(&Sig);
			Num[0] = 0xFF;
			if(Sig==1)
			{
				Num[1] = 0xBF;
			}
			else if(Sig==0)
			{
				Num[1] = 0xB9; //符号-|正号
			}
			Num[2] = LedChar[text/100];
			Num[3] = LedChar[((text/10)%10)];
			Num[4] = LedChar[text%10]; 
			Num[5] = 0x9C;
			Num[6] = 0xC6;
			Num[7] = 0xFF;
			NixieTupe_Static_Display(Num);
			Delay_MS(5);	//确保温度已经转换 而不是在转换途中读取
		}
	}
}

/**
  * @brief  机械按键外部中断服务函数，切换日期模式和时间
  */ 
void Key() interrupt 0
{
	S++;
	if (S == 0) 	//刷屏显示模式
	{	
		Flag = ROLL;
		TimerCount=0;
		TL0 = (65535-50000)%256;
		TH0 = (65535-50000)%256;
		TF0 = 0;				
		TR0 = 1;
		NixieTupe_Mode_Select(0x01);
	}
	else if (S ==  1)	//时间显示模式
	{
		SMG_ShiftBit=0;
		Flag = TIME;
		TR0 = 0;
		NixieTupe_Mode_Select(0x02);

	}
	else if(S == 2)		//日期显示模式
	{

		Flag = DATE;
		TR0 = 0;
		NixieTupe_Mode_Select(0x03);
	}
	else if(S == 3)		//日期显示模式
	{

		Flag = TEMP;
		TR0 = 0;
		NixieTupe_Mode_Select(0x04);
		S = -1;
	}
}
/**
  * @brief  刷屏显示模式下，刷屏时间间隔设置
  */ 
void Timer0() interrupt 1
{
	
	TL0 = (65535-50000)%256;	//设置定时初始值
	TH0 = (65535-50000)%256;	//设置定时初始值
	TimerCount++;
	if (TimerCount == 28)
	{
		TimerCount = 0;
		SMG_ShiftBit = 1;
	}
}



