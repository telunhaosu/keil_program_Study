#include <REGX51.H>
#include <intrins.h>
#include "Sys.h"


sbit DS1302_CE   = P1^0;
sbit DS1302_SCLK = P1^1;
sbit DS1302_IO   = P1^2;



/** --------------------------------------------------------
  *
  *			      秒	分	  时	日    月	周	  年
  * 写命令地址： 0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c 
  * 读命令地址： 0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d
  *	关闭写保护： DS1302_WriteByte(0x8E,0X00);
  * 打开写保护： DS1302_WriteByte(0x8E,0X10);
----------------------------------------------------------- */



/**
  * @brief  DS1302初始化，将使能端口和时钟电平都拉低
  * @param  无
  * @retval 无
  */
void DS1302_Init(void)
{
	DS1302_CE = 0;
	DS1302_SCLK = 0;
}
/**
  * @brief  DS1302写一个字节，此时数据由MCU发出
  * @param  Command 命令字/地址
  * @param  Data 要写入的数据
  * @retval 无
  */
void DS1302_WriteByte(uchar Command, uchar Data)
{
    unsigned char i;
    DS1302_CE=1;	//使能
    for(i=0;i<8;i++)
    {
        DS1302_IO=Command&(0x01<<i);
        DS1302_SCLK=1;	//此时产生上升沿
        DS1302_SCLK=0;	//回退至低电平
    }
    for(i=0;i<8;i++)
    {
        DS1302_IO=Data&(0x01<<i);
        DS1302_SCLK=1;
        DS1302_SCLK=0;
    }
    DS1302_CE=0;	//Disable 
	DS1302_IO=0; 
}

/**
  * @brief  DS1302读一个字节，此时数据由DS1302发出
  * @param  Command 命令字/地址
  * @param  Data 要读取的数据
  * @retval 要读取的一字节数据
  */
uchar DS1302_ReadByte(uchar Command)
{
	uchar i;
	uchar Data=0x00; //sas
	Command|=0x01;
	DS1302_CE = 1;
	for (i = 0; i < 8; i ++)
	{
		DS1302_IO = Command&(0x01<<i);
		DS1302_SCLK=0;	//回退至低电平
		DS1302_SCLK=1;	//此时产生上升沿
	}
	    for(i=0;i<8;i++)
    {
		DS1302_SCLK=1;
        DS1302_SCLK=0;	//产生下降沿，输出数据
		if(DS1302_IO){Data|=(0x01<<i);}
    }
	DS1302_CE=0;
	DS1302_IO=0; 
	return Data;
}
/**
  * @brief  取BCD码的十位
  * @param  BCD 要取位的BCD码
  * @retval 返回BCD码的十位
  */
uchar BCDCode_GetDecade(uchar BCD)
{
	return (BCD / 16);
}

/**
  * @brief  取BCD码的个位
  * @param  BCD 要取位的BCD码
  * @retval 返回BCD码的个位
  */
uchar BCDCode_GetUnit(uchar BCD)
{
	return (BCD % 16);
}
