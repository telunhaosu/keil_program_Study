#include "stm32f10x.h"                  // Device head
#include "Delay.h"
#include "OLED.h"

int main(void)
{	
	OLED_Init();
	OLED_ShowChar(1, 1, 'A');
	OLED_ShowString(1, 3, "HELLO WORLD");
	OLED_ShowNum(2, 1, 12345, 8);
	OLED_ShowHexNum(3, 1, 0xAA55, 10);
	OLED_ShowBinNum(4, 1, 0xAA55, 16);
	OLED_Clear();
	OLED_ShowString(1, 3, "HELLO WORLD");
	while(1)
	{
		
	}
}

