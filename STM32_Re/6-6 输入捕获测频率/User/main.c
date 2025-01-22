#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	PWM_Init();
	IC_Init();

	PWM_SetPrescaler(720 - 1);	//Freq = 72M / (PSC+1) / 100
	PWM_SetCompre1(50);			//Duty = CCR / 100
	OLED_ShowString(1, 1, "Freq:00000Hz");

	while (1)
	{
		OLED_ShowNum(1, 6, IC_GetFreq(), 5);
		Delay_ms(300);
	}
}
