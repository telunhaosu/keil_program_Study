#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

int main(void) 
{
	/*模块初始化*/
	OLED_Init();

	OLED_ShowChar(1, 1, 'B');
	OLED_ShowString(1, 3, "HelloWord!");
	OLED_ShowNum(2, 1, 12345, 4);
	OLED_ShowSignedNum(2, 1, -12345, 5);

	// OLED_ShowChar();
	while (1)
	{
		
	}
}
