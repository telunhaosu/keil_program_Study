#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"

uint8_t i;

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	PWM_Init();
	while (1)
	{
		for (i = 0; i <= 100; i++)
		{
			PWM_SetCompre1(i);
			Delay_ms(10);
		}
		for (i = 0; i <= 100; i++)
		{
			PWM_SetCompre1(100 - i);
			Delay_ms(10);
		}
	}
}
