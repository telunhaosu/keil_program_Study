#include "stm32f10x.h"                  // Device header

void Timer_Init(void)
{
	//使能TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_InternalClockConfig(TIM2);	//默认使用内部时钟驱动，可写可不写
	
	//初始化时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10000-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;	//只有高级定时器（TIM1，TIM8）才有效
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	//清除刚初始化完中断标志位置1，避免初始化完后就进入中断
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	//优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//初始化NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(& NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);	//启动定时器2
}
/*
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
*/
