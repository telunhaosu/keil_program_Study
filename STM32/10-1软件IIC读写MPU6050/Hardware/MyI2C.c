#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void MyI2C_W_SCL(uint8_t BitValue)	//写时钟
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)BitValue);
	Delay_us(10);  //保证足够的低电平
}

void MyI2C_W_SDA(uint8_t BitValue)  //写数据
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)BitValue);
	Delay_us(10);  //保证足够的低电平
}

uint8_t MyI2C_R_SDA(void)	//读时序
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
	Delay_us(10);  //保证足够的低电平
	return BitValue;
}

void MyI2C_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
}

void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}

void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		MyI2C_W_SDA(Byte & (0x80 >> i));  //具体可goto至源代码
		MyI2C_W_SCL(1);		//释放总线，读出数据
		MyI2C_W_SCL(0);		//拉低总线，为下一次写入数据做准备
	}
}

uint8_t MyI2C_ReceiveByte(void)
{
	uint8_t Byte = 0x00, i;
	MyI2C_W_SDA(1);		//释放SDA，防止SDA的低电平出现
	for (i = 0; i < 8; i++)
	{
		MyI2C_W_SCL(1);		//将时钟信号拉至高电平，为读取数据做准备
		if (MyI2C_R_SDA() == 1)
		{
			//Byte |= MyI2C_R_SDA() & (0x80 >> i);
			Byte |= (0x80 >> i);
		}
		MyI2C_W_SCL(0);
	}
	return Byte;
}

void MyI2C_SendAck(uint8_t AckBit)
{
	MyI2C_W_SDA(AckBit);
	MyI2C_W_SCL(1);		//从机读取应答
	MyI2C_W_SCL(0);		//为下一个时序做准备
}

uint8_t MyI2C_ReceiveAck(void)
{
	uint8_t AckBit;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	return AckBit;
}





