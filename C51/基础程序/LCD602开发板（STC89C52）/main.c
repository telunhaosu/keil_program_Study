#include <lcd.h>

void main()
{
//	unsigned char str1[] = "   2021032992   ";
	unsigned char str2[] = "6 Hou Run Dong  123456";

//	LCDShowStr(0, 0, str1);
//	LCDWriteCmd(0x06);
		LCDInit();
	LCDShowStr(0, 1, str2);
	LCDWriteCGRAM();
	while(1);
}