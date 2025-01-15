#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
	// 开启ADC和GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//采样频率
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//72MHz / 6 = 12MHz
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  //DAC专属模式。该模式下GPIO无效，单走模拟输入电路
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//选择规则组输入通道，此处选择一个通道。选多个重复执行下列代码
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	
	//初始化ADC结构体
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  //转换模式：单次，持续
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //对齐模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //外部触发源选择，此处为软件触发
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  // 独立模式或其他
	ADC_InitStructure.ADC_NbrOfChannel = 1; //通道数目，非扫描模式下只有通道一有效
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	//...此处可继续配置看门狗模块
	
	//开启ADC，开启电源
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1); // 复位校准
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);  //判断是否校准完成
	ADC_StartCalibration(ADC1); // 开始校准
	while (ADC_GetCalibrationStatus(ADC1) == SET);  //判断是否校准完成

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);  // 连续扫描模式只需要转换一次就可以
}


uint16_t AD_GetValue(void)
{
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);  //开始转换到数据寄存器
//	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); //转换完成置1
	return ADC_GetConversionValue(ADC1);	//读取后由硬件自动清除数据标志位
}
