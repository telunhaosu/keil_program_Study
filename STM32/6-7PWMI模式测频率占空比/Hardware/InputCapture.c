#include "stm32f10x.h"                  // Device header


/**初始化步骤
  *1.RCC开启时钟，打开TIM和GIPO时钟
  *2.GPIO初始化，配置GPIO输入模式（上拉或浮空）
  *3.配置时基单元，使CNT在内部时钟的驱动下自增运行
  *4.配置输入捕获单元————滤波器，极性，直连通道，交叉通道，分频器
  *5.选择从模式触发源，触发源选择TI1FP1，调用库函数进行配置
  *6.选择触发后执行的操作，Reset操作
  *7.调用TIM_Cmd函数，开启定时器
  *读取最新一个周期的频率时，直接读取CCR寄存器，然后按照fc/N计算即可
  */

void IC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536-1;	//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36-1; //PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_ICInitTypeDef TIM_ICInitTyStructure;
	//通道1
	TIM_ICInitTyStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitTyStructure.TIM_ICFilter = 0xF;
	TIM_ICInitTyStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//交叉配置：Falling
	TIM_ICInitTyStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitTyStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//交叉配置：TIM_ICSelection_IndirectTI
	TIM_ICInit(TIM3, &TIM_ICInitTyStructure);
	//通道2
	//交叉配置总与通道1形成互补
	TIM_PWMIConfig(TIM3, &TIM_ICInitTyStructure);
	
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM3, ENABLE);
}
// 获取频率
uint32_t IC_GetFreq(void)
{
	return 2000000 / (TIM_GetCapture1(TIM3)+1);
}
// 获取占空比
uint32_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM3) + 1) * 100 / TIM_GetCapture1(TIM3);
}
