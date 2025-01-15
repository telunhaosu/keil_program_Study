#include "stm32f10x.h"                  // Device header
#define LED_1 1
#define LED_2 2
#define LED_OFF 0
#define LED_ON 1

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
	
}

void LED_Set(uint8_t LED, uint8_t Mode)
{
	if(LED == LED_1)
	{
		if (Mode == LED_OFF)
			GPIO_SetBits(GPIOA, GPIO_Pin_1);
		else if(Mode == LED_ON)
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
	if(LED == LED_2)
	{
		if (Mode == LED_OFF)
			GPIO_SetBits(GPIOA, GPIO_Pin_2);
		else if(Mode == LED_ON)
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}
}

void LED_Turn(uint8_t LED)
{
	if (LED == LED_1)
	{
		if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0)
			GPIO_SetBits(GPIOA, GPIO_Pin_1);
		else
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
	if (LED == LED_2)
	{
		if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0)
			GPIO_SetBits(GPIOA, GPIO_Pin_2);
		else
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}
}
