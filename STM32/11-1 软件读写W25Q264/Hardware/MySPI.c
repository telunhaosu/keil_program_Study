#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void MySPI_W_SS(uint8_t BitVal) //从机选择
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitVal);
	Delay_us(1);
}

void MySPI_W_SCL(uint8_t BitVal) //时钟输入
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitVal);
	Delay_us(1);
}

void MySPI_W_MOSI(uint8_t BitVal) //主机输出，从机输入
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitVal);
	Delay_us(1);
}

uint8_t MySPI_R_MISO(void)	//主机输入，从机输出
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);

}


void MySPI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;		//MISO
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);	
	
	MySPI_W_SS(1); //默认电平
	MySPI_W_SCL(0);
}

void MySPI_Start(void)
{		
	MySPI_W_SS(0);
}

void MySPI_Stop(void)
{
	MySPI_W_SS(1);
}

uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	uint8_t ByteReceive = 0x00, i;

	for (i = 0; i <8; i++)	//下降沿传输数据，上升沿接收数据
	{
		MySPI_W_MOSI(ByteSend & (0x80 >> i));
		MySPI_W_SCL(1);
		if (MySPI_R_MISO() == 1) {ByteReceive |= (0x80 >> i);};
		MySPI_W_SCL(0);
	}
	return ByteReceive;
}

//uint8_t MySPI_SwapByte(uint8_t ByteSend)	//采用移位寄存器方式
//{
//	uint8_t ByteReceive, i;

//	for (i = 0; i <8; i++)	//下降沿传输数据，上升沿接收数据
//	{
//		MySPI_W_MOSI(ByteSend & 0x80);
//		ByteSend <<= 1;
//		MySPI_W_SCL(1);
//		if (MySPI_R_MISO() == 1) {ByteSend |= 0x01;};
//		MySPI_W_SCL(0);
//	}
//	return ByteReceive;
//}

