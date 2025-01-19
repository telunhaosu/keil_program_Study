#include "stm32f10x.h"

void ConterSensor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    //EXTI时钟由系统自己开启，不需要程序员配置，因为EXTI与各个外设都会关联，关联性很强，默认时钟是开启的
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);

}