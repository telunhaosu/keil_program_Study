#include "stm32f10x.h"                  // Device header
#include "motor.h"

void motor_Init(void)
{
	// 使能RCC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	// 初始化PWM输出口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;		//GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//初始化GPIO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//初始化时基单元 72MHz = 72 000 000Hz
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision 	 = 0; //时钟采样频率
	TIM_TimeBaseInitStruct.TIM_CounterMode   	 = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period		 	 = 100 - 1; //溢出才算结束，所以要减1
	TIM_TimeBaseInitStruct.TIM_Prescaler	 	 = 72 -1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0; //高级定时器
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	
	//配置输出捕获
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;
	TIM_OCInitTypeStruct.TIM_OCMode 	  = TIM_OCMode_PWM1; //PWM模式2 在向上计数时，一旦TIMx_CNT<TIMx_CCR1时通道1为有效电平，否则为无效电平
	TIM_OCInitTypeStruct.TIM_OCPolarity   = TIM_OCPolarity_High; //OC高电平有效
	TIM_OCInitTypeStruct.TIM_OutputState  = TIM_OutputState_Enable; //使能输出比较
	TIM_OCInitTypeStruct.TIM_Pulse 		  = 0;		// CCR
	TIM_OC3Init(TIM3, &TIM_OCInitTypeStruct);
	
	TIM_OCInitTypeStruct.TIM_OCMode 	  = TIM_OCMode_PWM1; //PWM模式2 在向上计数时，一旦TIMx_CNT<TIMx_CCR1时通道1为无效电平，否则为有效电平
	TIM_OCInitTypeStruct.TIM_OCPolarity   = TIM_OCPolarity_High; //OC高电平有效
	TIM_OCInitTypeStruct.TIM_OutputState  = TIM_OutputState_Enable; //使能输出比较
	TIM_OCInitTypeStruct.TIM_Pulse 		  = 0;		// CCR
	TIM_OC4Init(TIM3, &TIM_OCInitTypeStruct);
	
	TIM_Cmd(TIM3, ENABLE);
}


//控制左右轮PWM
void motor_SetPWM(wheel LR, uint16_t Compare)
{
	if (LR == L_Wheel)
	{
		TIM_SetCompare3(TIM3, Compare);
	}
	else if(LR == R_Wheel)
	{
		TIM_SetCompare4(TIM3, Compare);		
	}
	else
	{
		// pass
	}
}

