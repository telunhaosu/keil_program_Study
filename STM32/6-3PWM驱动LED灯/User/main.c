#include "stm32f10x.h"                  // Device head
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"

uint8_t i;
int main(void)
{	
	PWM_Init();
	
	
	while(1)
	{
		for (i=0; i<100;i++)
		{
			PWM_SetCompare1(i);
			Delay_ms(20);
		}
		for (i=0; i<100;i++)
		{
			PWM_SetCompare1(100-i);
			Delay_ms(20);
		}
		
	}
}

