#ifndef __DS18B20_H__
#define __DS18B20_H__

void Delay10us(void);
void Delay80us(void);
void Delay680us(void);
void DS18B20_Init(void);
void DS18B20_Write_0(void);
void DS18B20_Write_1(void);
void DS18B20_Write(uchar Data);
uchar DS18B20_Read(void);
uint Read_Temperature(uchar* singed);

#endif
