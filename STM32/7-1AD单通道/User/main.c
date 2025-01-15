#include "stm32f10x.h"                  // Device head
#include "Delay.h"
#include "OLED.h"
#include "AD.h"



int main(void)
{	 
	uint16_t ADValue; 
	float ADVoltage;
	
	
	OLED_Init();
	AD_Init();
	
	OLED_ShowString(1, 1, "AD_Value:0000" );
	OLED_ShowString(2, 1, "Voltage:0.00V" );
	
	while(1)
	{
		ADValue = AD_GetValue();
		ADVoltage = (float)ADValue/ 4095 * 3.3;
		
		OLED_ShowNum(1, 10, ADValue, 4);
		OLED_ShowNum(2, 9, ADVoltage, 1);
		OLED_ShowNum(2, 11, ((uint16_t)(ADVoltage*100))% 100, 2);
		
	}
}

