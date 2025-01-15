/*************************************************
File name: LCD1602.h
Author: Dong
Date: 2023.4.18 22:04
**************************************************/

#ifndef __LCD1602_H__ 
#define __LCD1602_H__
#include <reg51.h>


#define LCD1602_DB P0


//IO接口声明 LCD1602_DB P0
sbit LCD1602_RS = P2^6;
sbit LCD1602_RW = P2^5;
sbit LCD1602_EN = P2^7;

//LCD1602指令

//显示模式设置指令
#define LCD_MODE_PIN8 	0x38	//8位数据口，两行，5*8点阵
#define LCD_MODE_PIN4 	0x28	//4位数据位，两行，5*8点阵
#define LCD_SCREEN_CLR 	0x01	//清屏
#define LCD_SCREEN_RST 	0x02	//光标复位

//显示开关指令
#define LCD_DIS_CUR_BLK_ON 0x0F	//显示开，显示光标，光标闪烁
#define LCD_DIS_CUR_ON		 0x0E //显示开，显示光标，光标不闪烁
#define LCD_DIS_ON				 0x0C	//显示开，不显示光标，光标不闪烁
#define LCD_DIS_OFF				 0x08	//显示关，光标关，光标不闪烁

//显示模式控制(输入方式设置)
#define LCD_CUR_RIGHT			 0x06	//光标右移，显示不移动
#define LCD_CUR_LEFT			 0x04	//光标左移，且显示不移动、
#define LCD_DIS_MODE_ADD	 0x07 //操作后，AC(地址指针)加1，画面平移
#define LCD_DIS_MODE_DECADE  0x05	//操作后，AC自减，画面平移

//光标移位指令
#define	LCD_CUR_MOVE_LEFT  0x10	//光标左移
#define	LCD_CUR_MOVE_RIGHT 0x14	//光标右移
#define LCD_DIS_MOVE_LEFT	 0x18	//显示左移
#define LCD_DIS_MOVE_RIGHT 0x1C	//光标右移

//函数声明
void DelayMS(unsigned char x);
//写入指令(忙检测)
void LCDWriteCmd(unsigned char cmd);
void LCDWriteDate(unsigned char date);
void LCDInit();
void LCDShowStr(unsigned char x, unsigned char y, unsigned char *Str);
#endif