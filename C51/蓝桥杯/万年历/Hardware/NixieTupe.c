#include <REGX51.H>
#include "Sys.h"
#include "Delay.h"
#include "intrins.h"
// Mode display control pins
sbit Mode_P36 = P3^6;
sbit Mode_P37 = P3^7;


// 数码管共阳极编码
const uchar LedChar[]={
	0xC0,  //"0"
    0xF9,  //"1"
    0xA4,  //"2"
    0xB0,  //"3"
    0x99,  //"4"
    0x92,  //"5"
    0x82,  //"6"
    0xF8,  //"7"
    0x80,  //"8"
    0x90,  //"9"
    0x88,  //"A"
    0x83,  //"B"
    0xC6,  //"C"
    0xA1,  //"D"
    0x86,  //"E"
    0x8E,  //"F"
	0x7F   //"."
};

// 38译码器字段
uchar code ABC[] = {

	0x00,	
	0x01,
	0x02,
	0x03,
	0x04,
	0x05,
	0x06,
	0x07
};

/**
  * @brief  八位数码管日期，时间显示输入
  * @param  Num[] 需要显示输入的八位16进制数组
  * @retval 无
  */
void NixieTupe_Static_Display(uchar* Num) //Num
{
	unsigned char i;
	for (i = 0; i < 8; i++)
	{
		
		P2 &= 0xf8;
		P2 |= ABC[i];
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
void NixieTupe_Mode_Select(uchar Mode)
{
	switch(Mode)
	{
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
		case 0x04:
			Mode_P36 = 0;
            Mode_P37 = 0;
			break;		
	}
}
