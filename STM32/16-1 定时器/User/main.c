#include "stm32f10x.h"                  // Device head
#include "Delay.h"
#include "OLED.h"
#include "motor.h"
#include "encoder.h"

int main(void)
{	
	OLED_Init();
	motor_Init();
	encoder_Init();
	
	motor_SetPWM(L_Wheel, 100);
	motor_SetPWM(R_Wheel, 30);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_ResetBits(GPIOB, GPIO_Pin_15);
	
	while(1)
	{
		OLED_ShowNum(1, 1, encoder_GetCounter(R_Wheel), 5);
		OLED_ShowNum(2, 1, encoder_GetCounter(L_Wheel), 5);
	}
}

