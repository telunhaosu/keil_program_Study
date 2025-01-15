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
//		//不使用中断，通过状态标志位进行数据的连续传输
//		if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
//		{
//			Rx_Data = USART_ReceiveData(USART1);
//			OLED_ShowHexNum(count, 1, Rx_Data, 2);
//			count ++;
//		}
		
		if (Serial_GetRxFalg() == 1)
		{
			Rx_Data = Serial_GetRxData();
			Serial_SendByte(Rx_Data);
			OLED_ShowHexNum(count, 8, Rx_Data, 2);
			count ++;
		}
	}
}

