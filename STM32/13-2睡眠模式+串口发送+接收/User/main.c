#include "stm32f10x.h"                  // Device head
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t Rx_Data;
uint8_t count = 1;
int main(void)
{	
	OLED_Init();
	Serial_Init();
	OLED_ShowString(1, 1, "RxData:");
	
	while(1)
	{ 
		if (Serial_GetRxFalg() == 1)
		{
			Rx_Data = Serial_GetRxData();
			Serial_SendByte(Rx_Data);
			OLED_ShowHexNum(count, 8, Rx_Data, 2);
			count ++;
		}
		
		OLED_ShowString(2, 1, "Running");
		Delay_ms(100);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(100);
		
		__WFI();
	}
}

