#include "stm32f10x.h" // Device header
#include "Delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	// GPIO_SetBits(GPIOA, GPIO_Pin_0);

	while (1)
	{
		GPIO_Write(GPIOA, ~0x00000001);
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x00000002);
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x00000004);
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x00000008);
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x00000010);
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x00000020);
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x00000040);
		Delay_ms(500);
		GPIO_Write(GPIOA, ~0x00000080);
		Delay_ms(500);
	}


}
