#include "stm32f10x.h"                  // Device header
#include "motor.h"

void encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision		= TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode			= TIM_CounterMode_Up; //只有SMS=000时，才有效
	TIM_TimeBaseInitStruct.TIM_Period				= 65536 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler			= 1 - 1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter	= 0; //高级定时器才有效
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICInitStruct.TIM_Channel 		= TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter		= 0xF;
	TIM_ICInitStruct.TIM_ICPolarity		= TIM_ICPolarity_Rising; //根据数据手册该变量，没有双边沿触发
	TIM_ICInitStruct.TIM_ICPrescaler	= TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection	= TIM_ICSelection_DirectTI; //IC映射
	TIM_ICInit(TIM1, &TIM_ICInitStruct);
	TIM_ICInit(TIM2, &TIM_ICInitStruct);
	
	TIM_ICInitStruct.TIM_Channel 		= TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICFilter		= 0xF;
	TIM_ICInitStruct.TIM_ICPolarity		= TIM_ICPolarity_Rising; //TIM_EncoderInterfaceConfig中会重复配置。选择有效边沿，根据数据手册该变量，没有双边沿触发
	TIM_ICInitStruct.TIM_ICPrescaler	= TIM_ICPSC_DIV1; //预分频，但只有2位，4种模式
	TIM_ICInitStruct.TIM_ICSelection	= TIM_ICSelection_DirectTI; //IC映射
	TIM_ICInit(TIM1, &TIM_ICInitStruct);
	TIM_ICInit(TIM2, &TIM_ICInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); 	//在TI1FP1和TI2FP2都计数
	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_SetCounter(TIM1, 0);  //设置计数器值为0
	TIM_SetCounter(TIM2, 0);  //设置计数器值为0
	
	TIM_Cmd(TIM1, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}


// 获取左右轮东总脉冲,一周等于13x4x20=1040个脉冲。
uint16_t encoder_GetCounter(wheel LR)
{
	if (LR == L_Wheel)
	{
		return TIM_GetCounter(TIM1);
	}
	else if(LR == R_Wheel)
	{
		return TIM_GetCounter(TIM2);	
	}
	else
	{
		return 55555;	// pass 错误返回值
	}
}

