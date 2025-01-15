#include "stm32f10x.h"                  // Device header
#include "MyI2C.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS 0xD0

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);	//匹配从机地址 写模式
	MyI2C_ReceiveAck();					
	MyI2C_SendByte(RegAddress);			//匹配寄存器地址
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Data);				//发送要写入的数据
	MyI2C_ReceiveAck();
	MyI2C_Stop();	
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Byte;
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);	//匹配从机地址，写模式
	MyI2C_ReceiveAck();					
	MyI2C_SendByte(RegAddress);			//匹配寄存器地址
	MyI2C_ReceiveAck();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);	//匹配从机地址，读模式
	MyI2C_ReceiveAck();
	Byte = MyI2C_ReceiveByte();
	MyI2C_SendAck(1);		//应答(0)，继续读取从机地址。反之收回主机控制权
	MyI2C_Stop();
	return Byte;
}


void MPU6050_Init(void)
{
	MyI2C_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);		//解除睡眠，选择陀螺仪时钟
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);		//6轴均不待机
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);		//采样分频为10
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);			//滤波参数给最大
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);	//陀螺仪选择大量程
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);	//加速度计选择大量程
}

void MPU6050_GetData(int16_t *AccX,  int16_t *AccY, int16_t *AccZ,
					 int16_t *GyroX, int16_t *GyroY,int16_t *GyroZ)
{
	uint8_t DataH, DataL;
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8) | DataL; 
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;	
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;
	
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;
}
