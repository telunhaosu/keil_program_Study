#include <REGX51.H>
#include <intrins.h>
#include "Delay.h"
#include "Sys.h"
sbit BUS = P2^3;

uchar code DS18B20_ROM_0[]= {0x28,0x30,0xc5,0xb8,0x00,0x00,0x00,0x8e};
uchar code DS18B20_ROM_1[]= {0x28,0x31,0xc5,0xb8,0x00,0x00,0x00,0xb9};

void Delay500us();
void Delay80us();
void Delay58us();
void Delay10us();
void Delay50us();

/**
  * @brief  DS18B20初始化函数
  * @param  无
  * @retval 返回0初始化成功，返回1初始化化失败
  */
uchar DS18B20_Init(void)
{
	uchar Ack;
	BUS = 1;			//确保总线起始时为高
	BUS = 0;			//拉低总线
	Delay500us();		//持续 > 480us
	BUS = 1;			//释放总线
	Delay80us();
	Ack = BUS;
	Delay500us();
	return Ack;
}

/**
  * @brief  DS18B20按位写函数
  * @param  DataBit：要写入的数据位
  * @retval 无返回值
  */
void DS18B20_WriteBit(uchar DataBit)
{
	uchar i;
	BUS = 0; 			//拉低
	_nop_();_nop_();	//大于2us
	BUS = DataBit;		//写入1位
	Delay58us();		//使写时隙时间大于60us
	BUS = 1;			//释放总线
	_nop_();_nop_();	//>1us
}

/**
  * @brief  DS18B20按位读函数
  * @param  无
  * @retval 返回读取的数据位
  */
uchar DS18B20_ReadBit(void)
{
	uchar DataBit;
	BUS=1;
	BUS = 0;
	_nop_();_nop_();
	BUS = 1;
	Delay10us();
	DataBit = BUS;
	Delay50us();
	return DataBit;
}
/**
  * @brief  DS18B20按字节写函数
  * @param  DataBit：要写入的数据字节
  * @retval 无返回值
  */
void DS18B20_WriteByte(uchar DataByte)
{
	uchar i;
	for (i=0; i < 8; i++)
	{
		DS18B20_WriteBit(DataByte&(0x01<<i));
	}
}

/**
  * @brief  DS18B20按字节读函数
  * @param  无
  * @retval 返回读取的字节数据
  */
uchar DS18B20_ReadByte(void)
{
	uchar i, DataByte=0x00;
	for (i=0; i < 8; i++)
	{
		if (DS18B20_ReadBit())
		{
			DataByte |= (0x01<<i);
		}
	}
	return DataByte; 
}
/**
  * @brief  使DS18B20进行温度转换
  * @param  无
  * @retval 无
  */
void DS18B20_ConvertT(void)
{
	DS18B20_Init();
	DS18B20_WriteByte(0xCC); //SKIP ROM
	DS18B20_WriteByte(0x44); //Convert Temp
}

/**
  * @brief  读取DS18B20温度
  * @param  无
  * @retval 返回有符号温度值
  */
float DS18B20_ReadT(void)
{
	uchar LSB, MSB;
	int MLSB;
	float T;
	DS18B20_Init();
	DS18B20_WriteByte(0xCC);	//SKIP ROM
	DS18B20_WriteByte(0xBE);	//读暂存器
	LSB = DS18B20_ReadByte();
	MSB = DS18B20_ReadByte();
	MLSB = (MSB<<8)|LSB;
	T = MLSB/16.0;
	return T;
}

/**
  * @brief  DS18B20精度配置函数。默认为12位精度。
  * @param  Resolution: 配置精度参数
  *			参数 精度 转换时间(ms)
  *			0x1f  9	    93.75
  *			0x3f  10    187.5
  *			0x5f  11    375
  *			0x7f  12    750
  * @retval 无
  */
void DS18B20_ConfigT(uchar Resolution)
{
	DS18B20_Init();
	DS18B20_WriteByte(0xCC);	//SKIP ROM
	DS18B20_WriteByte(0x4E);	//写寄存器
	DS18B20_WriteByte(0x00);	//过温报警;查询报警命令(0xEC)才能使所配置的报警温度有效
	DS18B20_WriteByte(0x00);	//低温报警;查询报警命令(0xEC)才能使所配置的报警温度有效
	DS18B20_WriteByte(Resolution);	//写配置精度
	DS18B20_Init();				//停止写入
}
/**
  * @brief  读取DS18B20ROM(序列号)，只适用于总线上有单个传感器。
  * @param  ROM：读取ROM后储存的数组
  * @retval 无。
  */
void DS18B20_ReadROM(uchar* ROM)
{
	uchar i;
	DS18B20_Init();
	DS18B20_WriteByte(0x33);	//read rom
	for (i=0; i < 8; i++)
	{
		ROM[i] = DS18B20_ReadByte();
	}
}
/**
  * @brief  匹配DS18B20的ROM
  * @param  ROM_Num：DS18B20编号。可以为ROM_0,ROM_1
  * @retval 无
  */
void DS18B20_MatchROM(uchar ROM_Num)
{
	uchar i;
	DS18B20_WriteByte(0x55);	//match ROM
	switch(ROM_Num)
	{
		case 0:
			for (i = 0; i < 8; i++)
				DS18B20_WriteByte(DS18B20_ROM_0[i]);
			break;
		case 1:
			for (i = 0; i < 8; i++)
				DS18B20_WriteByte(DS18B20_ROM_1[i]);
			break;
		default:
			break;
	}
}

/**
  * @brief  多个DS18B20下，配置温度转换精度
  * @param  Resolution：指定转换精度
  *			ROM_Num：DS18B20序列号。
  * @retval 无。
  */
void DS18B20_Match_ConfigT(uchar Resolution, uchar ROM_Num)
{
	DS18B20_Init();
	DS18B20_MatchROM(ROM_Num);
	DS18B20_WriteByte(0x4E);	//写寄存器
	DS18B20_WriteByte(0x00);	//过温报警;查询报警命令(0xEC)才能使所配置的报警温度有效
	DS18B20_WriteByte(0x00);	//低温报警;查询报警命令(0xEC)才能使所配置的报警温度有效
	DS18B20_WriteByte(Resolution);	//写配置精度
}

/**
  * @brief  多个DS18B20下，进行温度转换
  * @param  ROM_Num：指定要进行转换的DS18B20序列号。
  * @retval 无。
  */
void DS18B20_Match_ConvertT(uchar ROM_Num)
{
	DS18B20_Init();
	DS18B20_MatchROM(ROM_Num);
	DS18B20_WriteByte(0x44); //Convert Temp
}
/**
  * @brief  多个DS18B20下，读取制定DS18B20的温度
  * @param  ROM_Num：指定要进行温度读取的DS18B20序列号。
  * @retval 返回有符号温度值
  */
float DS18B20_Match_ReadT(uchar ROM_Num)
{
	uchar LSB, MSB;
	int MLSB;
	float T;
	DS18B20_Init();
	DS18B20_MatchROM(ROM_Num);
	DS18B20_WriteByte(0xBE);	//读暂存器
	LSB = DS18B20_ReadByte();
	MSB = DS18B20_ReadByte();
	MLSB = (MSB<<8)|LSB;
	T = MLSB/16.0;
	return T;
}

void Delay500us()		//@12.000MHz
{
	unsigned char data i;

	_nop_();
	i = 247;
	while (--i);
}

void Delay80us()		//@12.000MHz
{
	unsigned char data i;

	_nop_();
	i = 37;
	while (--i);
}

void Delay58us()		//@12.000MHz
{
	unsigned char data i;

	_nop_();
	i = 26;
	while (--i);
}

void Delay10us()		//@12.000MHz
{
	unsigned char data i;

	_nop_();
	i = 2;
	while (--i);
}

void Delay50us()		//@12.000MHz
{
	unsigned char data i;

	_nop_();
	i = 22;
	while (--i);
}



