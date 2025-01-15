#include <REGX51.H>
#include <intrins.h>
#include "Sys.h"
#include "Delay.h"

sbit BUS_DQ = P2^3;

void Delay10us(void)		//@12.000MHz
{
	unsigned char data i;

	_nop_();
	i = 2;
	while (--i);
}
void Delay600us(void)		//@12.000MHz
{
	unsigned char data i, j;

	i = 2;
	j = 39;
	do
	{
		while (--j);
	} while (--i);
}

void DS18B20_Init(void)
{
	BUS_DQ = 0;
	Delay600us();
	BUS_DQ = 1;
	while(BUS_DQ);
	while(!BUS_DQ);
	BUS_DQ = 1;
}

/********************************向DS18B20写入一字节***********************/
void DS18B20_Write(uchar com)//从低位开始写入DS18B20_Write
{
	uchar mask;
	for(mask=0x01;mask!=0;mask<<=1)
	{
		//该位为0，先拉低，15us后在拉高，并通过延时使整个周期为60us
	    //该位为1,先拉低并在15us内(此处选择5us)拉高，并通过延时使整个周期为60us	
		BUS_DQ=0;
		_nop_();_nop_();_nop_();_nop_();_nop_();//先拉低5us
		if((com&mask)==0)//该位是0
		{
			BUS_DQ=0;	
		}
		else//该位是1
		{
			BUS_DQ=1;		
		}
		Delay10us();Delay10us();Delay10us();Delay10us();Delay10us();;//延时60us
		_nop_();_nop_();_nop_();_nop_();_nop_();
		BUS_DQ=1;//拉高
		_nop_();_nop_();//写两个位之间至少有1us的间隔（此处选择2us）
	}
}


uchar DS18B20_Read(void)
{
	uchar Data=0, mask;
	for (mask=0x01; mask!=0;mask<<=1)
	{
		BUS_DQ = 0;
		_nop_();_nop_();
		BUS_DQ = 1;
		_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		if (BUS_DQ == 0)
		{
			Data &= (~mask);
		}
		else
		{
			Data |= mask;
		}
			Delay10us(); Delay10us(); Delay10us();
	Delay10us(); Delay10us(); 
	_nop_();_nop_();//60ms
	BUS_DQ = 1;			//释放总线 >1us
	_nop_();_nop_();	//2us
	
	}
return Data;
}

uint Read_Temperature(uchar* Sig)
{
	uint temp=0x00;
	float tp;
	uchar LSB=0,MSB=0;
	Delay_MS(1);//延时10ms度过不稳定期
	
	DS18B20_Init();//Ds18b20初始化
	DS18B20_Write(0xcc);//跳过ROM寻址
	DS18B20_Write(0x44);//启动一次温度转换
	
	DS18B20_Init();//Ds18b20初始化
	DS18B20_Write(0xcc);//跳过ROM寻址
	DS18B20_Write(0xbe);//发送读值命令
	
	LSB=DS18B20_Read();
	MSB=DS18B20_Read();

	temp=MSB;
	temp<<=8;
	temp|=LSB;
	if((temp&0xf000)==0xf000)//判断符号位，负温度
	{
		temp=(~temp)+1; //数据取反再加1
		tp=temp*(0.0625);//乘以精度
		*Sig=1;	
	}
	else //正温度
	{
		tp=temp*0.0625;	
		*Sig=0;
	}
	temp=tp;
	if(tp-temp>=0.5)
	{
		temp+=1;
	}
	return temp;
}

