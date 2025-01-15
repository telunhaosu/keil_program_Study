#include "stm32f10x.h"                  // Device head
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "KEY.h"

float Angle;
uint8_t KeyNum;

int main(void)
{	
	OLED_Init(); 
	Servo_Init();
	Key_Init();
	
	OLED_ShowString(1, 1, "Angle:");
	
	while(1)
	{
		KeyNum = Key_GetNum();
		if (KeyNum == 1)
		{
			Angle += 30;
			if (Angle>180)
			{
				Angle = 0;
			}
			Servo_SetAngle(Angle);
			OLED_ShowNum(1, 7, Angle, 3);
		}
	}
}

