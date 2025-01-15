#include "stm32f10x.h"                  // Device head
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"


int main(void)
{	
	OLED_Init();
	Serial_Init();
	
//	Serial_SendByte(0x41); 
	

//	Serial_SendString("Hello World!\r\n");
	
//	Serial_SendNumber(123460, 6);
	
//	printf("Num = %d\r\n", 7654351);
	
//	//格式化输出
//	char String[100];
//	sprintf(String, "sprintf Num = %d\r\n", 666);
//	Serial_SendString(String);
	
	Serial_Printf("你好世界");
	printf("你好世界压！");
	
	while(1)
	{
	}
}

