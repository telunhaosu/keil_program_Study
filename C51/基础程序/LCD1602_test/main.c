#include <LCD1602.h>

void main()
{
	unsigned char str1[] = "   2021032992   ";
	unsigned char str2[] = "Hou Run Dong";
	LCDInit();
	LCDShowStr(0, 0, str1);
	LCDShowStr(0, 1, str2);
	while(1);
}