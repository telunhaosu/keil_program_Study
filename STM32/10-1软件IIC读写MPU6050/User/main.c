#include "stm32f10x.h"                  // Device head
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"

int16_t AX, AY, AZ, GX, GY, GZ;

int main(void)
{	
	OLED_Init();
	MPU6050_Init();
	
	while(1)
	{
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		
		OLED_ShowString(1, 3, "ACCEL");
		OLED_ShowString(1, 10, "GYRO");
		
		OLED_ShowString(2, 1, "X:");
		OLED_ShowSignedNum(2, 3, AX, 5);
		
		OLED_ShowString(3, 1, "Y:");
		OLED_ShowSignedNum(3, 3, AY, 5);
		
		OLED_ShowString(4, 1, "Z:");
		OLED_ShowSignedNum(4, 3, AZ, 5);

		OLED_ShowSignedNum(2, 10, GX, 5);

		OLED_ShowSignedNum(3, 10, GY, 5);
		
		OLED_ShowSignedNum(4, 10, GZ, 5);
	}
}

