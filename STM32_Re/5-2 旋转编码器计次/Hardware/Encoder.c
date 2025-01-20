#include "stm32f10x.h"

int16_t Encode_Count;

void Encoder_Init(void)
{
    /*开启时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 开启GPIOB的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  // 开启AFIO的时钟，外部中断必须开启AFIO的时钟

    /*GPIO初始化*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure); // 将PB14引脚初始化为上拉输入

    /*AFIO选择中断引脚*/
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

    /*EXTI初始化*/
    EXTI_InitTypeDef EXTI_InitStructure; // 定义结构体变量
    EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;               // 指定外部中断线使能
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     // 指定外部中断线为中断模式
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // 指定外部中断线为下降沿触发
    EXTI_Init(&EXTI_InitStructure);                         // 将结构体变量交给EXTI_Init，配置EXTI外设

    /*NVIC中断分组*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 配置NVIC为分组2
                                                    // 即抢占优先级范围：0~3，响应优先级范围：0~3
                                                    // 此分组配置在整个工程中仅需调用一次
                                                    // 若有多个中断，可以把此代码放在main函数内，while循环之前
                                                    // 若调用多次配置分组的代码，则后执行的配置会覆盖先执行的配置

    /*NVIC配置*/
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);
}

uint16_t Encoder_Get(void)
{
    uint16_t Temp;
    Temp = Encode_Count;
    Encode_Count = 0;
    return Temp;
}

void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) == SET)
    {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
        {
            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
            {
                Encode_Count--;
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
void EXTI1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) == SET)
    {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
        {
            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
            {
                Encode_Count++;
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}
