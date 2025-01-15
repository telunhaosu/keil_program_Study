#ifndef __DS1302_H
#define __DS1302_H

#include "Sys.h"

void DS1302_Init(void);
void DS1302_WriteByte(uchar Command, uchar Data);
uchar DS1302_ReadByte(uchar Command);
uchar BCDCode_GetDecade(uchar BCD);
uchar BCDCode_GetUnit(uchar BCD);

#endif
