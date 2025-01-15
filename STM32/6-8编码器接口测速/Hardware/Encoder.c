#include "stm32f10x.h"                  // Device header

void Encoder_Init(void)
{
	//开启TIM3和GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//配置GPIOA
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;
	TIM_TimBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimBaseInitStructure.TIM_Period = 65536 - 1;//ARR
	TIM_TimBaseInitStructure.TIM_Prescaler = 1 - 1; //PSC不分频
	TIM_TimBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimBaseInitStructure);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4 | TIM_Channel_4;
	TIM_ICInitStructure.TIM_ICFilter = 0x0F;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//上升沿极性不返向，下降沿极性反向
	// TIM_ICInitStructure.TIM_ICPrescaler = 不用
	// TIM_ICInitStructure.TIM_ICSelection = 不用
	TIM_ICInit(TIM3, &TIM_ICInitStructure);	//初始化不用的部分
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0x0F;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//上升沿极性不返向，下降沿极性反向
	// TIM_ICInitStructure.TIM_ICPrescaler = 不用
	// TIM_ICInitStructure.TIM_ICSelection = 不用
	TIM_ICInit(TIM3, &TIM_ICInitStructure);	//初始化不用的部分
	
	//配置编码器接口
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	//开启定时器
	TIM_Cmd(TIM3, ENABLE);
}

int16_t Encoder_Get(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3, 0);	//清理计数器
	return Temp;
}
