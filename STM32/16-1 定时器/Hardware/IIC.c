#include "stm32f10x.h"                  // Device header

#define SCL		GPIO_Pin_10
#define SDA		GPIO_Pin_11

void IIC_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Pin = SCL | SDA;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	

	
}

void IIC_Start(void)
{
	GPIO_SetBits(GPIOB, SDA);
	GPIO_SetBits(GPIOB, SCL);
	GPIO_SetBits(GPIOB, SDA);
	
}