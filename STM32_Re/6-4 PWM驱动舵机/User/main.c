#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "SG90.h"
uint8_t i;

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	SG90_Init();
	SG90_SetAngle(0);
	while (1)
	{
	}
}
