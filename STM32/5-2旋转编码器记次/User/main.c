#include "stm32f10x.h"                  // Device head
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"

int16_t Num;
//中断函数要执行迅速，最好不要执行延时函数和耗时过长的函数
//中断和主函数不要执行同一个函数，否则会报错
//保护现场只在CPU中有效，而对硬件没有这种操作
int main(void)
{	
	OLED_Init();
	Encoder_Init();
	
	OLED_ShowString(1, 1, "Num:");
	while(1)
	{
		Num += Encoder_Get();
		if (Num < 0)
		{
			Num = 0;
		}
		OLED_ShowNum(1, 5, Num, 5);
	}
}

