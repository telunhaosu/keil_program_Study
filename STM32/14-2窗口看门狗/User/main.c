#include "stm32f10x.h"                  // Device head
#include "Delay.h"
#include "OLED.h"
#include "KEY.h"

int main(void)
{	
	OLED_Init();
	Key_Init();
	
	OLED_ShowString(1, 1, "IWDG TEST");
	
	if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET)
	{
		OLED_ShowString(2, 1, "WWDGRST");
		Delay_ms(500);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(100);
		RCC_ClearFlag(); //必须手动清零，按下复位键也不会清零
	}
	else
	{
		OLED_ShowString(2, 1, "RST");
		Delay_ms(500);
		OLED_ShowString(2, 1, "   ");
		Delay_ms(100);
	}
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	WWDG_SetWindowValue(0x40 | 21);
	WWDG_Enable(0x40 | 54);
	
	
	while(1)
	{
		Key_GetNum();
		


//		OLED_ShowString(4, 1, "FEED");
//		Delay_ms(5);
//		OLED_ShowString(4, 1, "    ");
		Delay_ms(30);
		WWDG_SetCounter(0x40 | 54);	
	}
}

