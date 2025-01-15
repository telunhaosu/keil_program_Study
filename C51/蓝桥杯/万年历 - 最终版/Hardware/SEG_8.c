#include <REGX51.H>
#include "Sys.h"
#include "Delay.h"
#include "intrins.h"
// Mode display control pins
sbit Mode_P36 = P3^6;
sbit Mode_P37 = P3^7;


// 数码管共阳极编码
const uchar SEG_Char[]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, // 0 - 7
					    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, // 8 - F
					    0x7F}; 										   // 0x7E为"."
	
// 38译码器字段
uchar code LS138_ABC[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}; // 0- 7

//初始化数码管为不显示
void SEG_Init(uchar* Num)
{
	uchar i;
	for (i = 0; i < 8; i++)
	{
		Num[i] = 0xff;
	}
}

/**
  * @brief  八位数码管日期，时间显示输入；低位在左，高位在右
  * @param  Num[] 需要显示输入的八位16进制数组
  * @retval 无
  */
void SEG_Display(uchar* Num)
{
	uchar i, j;
	for (i = 0; i < 8; i++)
	{
		P2 &= 0xf8;
		P2 |= LS138_ABC[i];
		P0 = Num[i];
		Delay_MS(1);
	}
}

/**
  * @brief  一位数码管模式显示输入
  * @param  Mode需要呈现的显示模式
  *			(Mode = 0x01,show time;Mode = 0x02,show date;Mode = 0x03,show roll;)
  * @retval	无
  */
void SEG_Mode_Select(uchar Mode)
{
	switch(Mode)
	{
		case 0x00:
			Mode_P36 = 0;	
			Mode_P37 = 0;
			break;
		case 0x01:
			Mode_P36 = 1;
			Mode_P37 = 0;
			break;
		case 0x02:
			Mode_P36 = 0;
            Mode_P37 = 1;
			break;
		case 0x03:
			Mode_P36 = 1;
            Mode_P37 = 1;
			break;		
	}
}
