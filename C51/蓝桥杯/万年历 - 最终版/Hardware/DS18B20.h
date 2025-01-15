#ifndef __DS18B20_H
#define __DS18B20_H

void DS18B20_Init(void);
void DS18B20_WriteBit(uchar DataBit);
uchar DS18B20_ReadBit(void);
void DS18B20_WriteByte(uchar DataByte);
uchar DS18B20_ReadByte(void);
void DS18B20_ConvertT(void);
float DS18B20_ReadT(void);
void DS18B20_ConfigT(uchar Resolution);

void DS18B20_ReadROM(uchar* ROM);
void DS18B20_MatchROM(uchar* ROM);
void DS18B20_Match_ConfigT(uchar Resolution, uchar ROM_Num);
void DS18B20_Match_ConvertT(uchar ROM_Num);
float DS18B20_Match_ReadT(uchar ROM_Num);

#endif
