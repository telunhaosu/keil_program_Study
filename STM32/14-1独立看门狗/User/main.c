#include "stm32f10x.h"                  // Device head
#include "Delay.h"
#include "OLED.h"
#include "KEY.h"

int main(void)
{	
	OLED_Init();
	Key_Init();
	
	OLED_ShowString(1, 1, "IWDG TEST");
	
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET)
	{
		OLED_ShowString(2, 1, "IWDGRST");
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
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //关闭写保护后，会自动开启LSI时钟
	IWDG_SetPrescaler(IWDG_Prescaler_16);
	IWDG_SetReload(2499);						//1000ms
	IWDG_ReloadCounter();						//喂狗
	IWDG_Enable();								//启动看门狗
	
	
	while(1)
	{
		Key_GetNum();
		
		IWDG_ReloadCounter();
		
		OLED_ShowString(4, 1, "FEED");
		Delay_ms(200);
		OLED_ShowString(4, 1, "    ");
		Delay_ms(600);
	}
}

