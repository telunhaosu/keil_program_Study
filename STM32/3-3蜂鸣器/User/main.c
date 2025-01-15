#include "stm32f10x.h"                  // Device head
#include "Delay.h"

int main(void)
{
	// RCC->APB2ENR = 0X00000010;
	// GPIOC->CRH = 0x00300000;
	// GPIOC->ODR = 0X00002000;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	while(1)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
		Delay_ms(1000);
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
		Delay_ms(300);	
	}
}
