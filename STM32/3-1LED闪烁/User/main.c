#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main()
{
	//*操作STM32的GPIO的三个步骤*
	//1.使用RCC开启GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//2.初始化GPIO_Init函数初始化GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//3.使用
	// 初始化函数控制GPIO函数
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	while(1)
	{
		
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
		Delay_ms(100);
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
		Delay_ms(100);
	}
}
