#include "stm32f10x.h"                  // Device head
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "KEY.h"

uint8_t KeyNum;
int8_t Speed;

int main(void)
{
	OLED_Init();
	Motor_Init();
	Key_Init();
	OLED_ShowString(1, 1, "Speed:+000");
	
	while(1)
	{
		if (Key_GetNum() == 1)
		{
			Speed += 20;
			if (Speed > 100)
			{
				Speed = -100;
			}
			Motor_SetSpeed(Speed);
			OLED_ShowSignedNum(1, 7, Speed, 3);
		}
	}
}

