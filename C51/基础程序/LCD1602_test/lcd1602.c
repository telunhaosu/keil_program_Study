#include <lcd1602.h>
void DelayMS(unsigned char x)
{
	unsigned char i;
	while(x--)
	{
		for (i = 0; i <250; i++);
	}
}
void LCDReadBF()
{
	unsigned char state;
	unsigned char i;
	LCD1602_DB = 0xFF; //IO¿ÚÖÃ1
	LCD1602_RS = 0;
	LCD1602_RW = 1;
do
{
		LCD1602_EN = 1;
	state = LCD1602_DB;
	LCD1602_EN = 0;
	i++;
	
}
while(state & 0x80);
}

//Ð´ÈëÖ¸Áî(Ã¦¼ì²â)
void LCDWriteCmd(unsigned char cmd)
{
	LCDReadBF();//busy check
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	LCD1602_DB = cmd;
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}

//Ð´Ö¸Áî£¨²»Ã¦¼ì²â£©
void LCDWriteCmd_NoBF(unsigned char cmd)
{
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	LCD1602_DB = cmd;
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}

void LCDWriteDate(unsigned char date)
{
	LCDReadBF();
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	LCD1602_EN = 0;
	LCD1602_DB = date;
	LCD1602_EN = 1; 
	LCD1602_EN = 0;
}
void LCDInit()
{
	DelayMS(15);
	LCDWriteCmd_NoBF(LCD_MODE_PIN8); //0x38
	DelayMS(5);
	LCDWriteCmd_NoBF(LCD_MODE_PIN8);
	DelayMS(5);
	LCDWriteCmd_NoBF(LCD_MODE_PIN8);
	LCDWriteCmd(LCD_MODE_PIN8);
	LCDWriteCmd(LCD_DIS_OFF); //0x08
	LCDWriteCmd(LCD_DIS_ON);	//0x0c
	LCDWriteCmd(LCD_CUR_RIGHT);	//0x06
	LCDWriteCmd(LCD_SCREEN_CLR);	//0x01
}

//×Ö·û´®ÊäÈë
void LCDShowStr(unsigned char x, unsigned char y, unsigned char *Str)
{
	if (y == 0)
	{
		LCDWriteCmd(0x80 | x);
	}
	else if (y == 1)
	{
		LCDWriteCmd(0x80 | (0x40+x));
	}
	while(*Str != '\0')
	{
		LCDWriteDate(*Str++);
	}
}