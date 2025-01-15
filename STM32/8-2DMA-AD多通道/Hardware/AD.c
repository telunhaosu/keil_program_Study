#include "stm32f10x.h"                  // Device header

//extern uint16_t AD_Value[4];

uint16_t AD_Value[4];

void AD_Init(void)
{
	// 开启ADC和GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//采样频率
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//72MHz / 6 = 12MHz
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  //DAC专属模式。该模式下GPIO无效，单走模拟输入电路
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
	
	//初始化ADC结构体
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  // 独立模式或其他
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //对齐模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //外部触发源选择，此处为软件触发
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  //连续单次扫描模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;//是否扫描
	ADC_InitStructure.ADC_NbrOfChannel = 4; //通道数目，非扫描模式下只有通道一有效
	ADC_Init(ADC1, &ADC_InitStructure);
	//初始化DMA结构体
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 4;//传输计数器
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// 不重装
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//使用软件触发，不使用硬件触发
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	//开启DMA，触发通道，ADC
	DMA_Cmd(DMA1_Channel1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	
	//校准部分
	ADC_ResetCalibration(ADC1); // 复位校准
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);  //判断是否校准完成
	ADC_StartCalibration(ADC1); // 开始校准
	while (ADC_GetCalibrationStatus(ADC1) == SET);  //判断是否校准完成
	
	//ADC软件触发
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

//void AD_GetValue(void)
//{
//	DMA_Cmd(DMA1_Channel1, DISABLE);
//	DMA_SetCurrDataCounter(DMA1_Channel1, 4);
//	DMA_Cmd(DMA1_Channel1, ENABLE);
//	
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);  //开始转换到数据寄存器
//	
//	//因为DMA转换总是在ADC转换完成之后，
//	//所以当ADC或DMA未转换完成前，“转换完成”标志位总是为RESET
//	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
//	DMA_ClearFlag(DMA1_FLAG_TC1);
//}
