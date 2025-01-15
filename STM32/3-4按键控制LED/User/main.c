#include "stm32f10x.h"                  // Device head
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
#include "BUZZER.h"
#include "LIGHTSENSOR.h"

int main(void)
{
	Buzzer_Init();
	while(1)
	{
		if (LightSensor_Get() == 1)
		{
			Buzzer_ON();
		}
		else
		{
			Buzzer_OFF();
		}
	}
	
}
