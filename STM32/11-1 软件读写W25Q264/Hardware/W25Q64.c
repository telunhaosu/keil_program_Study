#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "W25Q64_Ins.h"

void W25Q64_Init(void)
{
	MySPI_Init();
}

void W25Q64_ReadID(uint8_t *MID, uint16_t *DID) //厂商ID和设备ID
{
	uint8_t tmp1 = 0x00;	uint8_t tmp2 = 0x00;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_JEDEC_ID);	//获取ID指令
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	
//	*DID = MySPI_SwapByte(0xFF);
//	*DID <<= 8;
//	*DID |= MySPI_SwapByte(0xFF);
	tmp1 =MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	tmp2 =MySPI_SwapByte(W25Q64_DUMMY_BYTE);	
	*DID = tmp1 << 8| tmp2;
	MySPI_Stop();
}

void W25Q64_WriteEnable(void)	//写使能
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}

void W25Q64_WaitBusy(void)
{
	uint32_t TimeOut;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
	TimeOut = 10000;
	while ((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01)== 0x01)
	{
		TimeOut--;
		if (TimeOut == 0)
		{
			break;
		}
	};
	MySPI_Stop();
}

void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint8_t Count)
{
	W25Q64_WriteEnable();
	
	uint8_t i;
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
	MySPI_SwapByte(Address >> 16);
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);
	
	for (i = 0; i <= Count; i++)
	{
			MySPI_SwapByte(DataArray[i]);
	}
	MySPI_Stop();
	W25Q64_WaitBusy();
}

void W25Q64_SectorErase(uint32_t Address)
{
	W25Q64_WriteEnable();
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_BLOCK_ERASE_4KB);
	MySPI_SwapByte(Address >> 16);
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);
	MySPI_Stop();	
	W25Q64_WaitBusy();
}

void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
	uint32_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);
	MySPI_SwapByte(Address >> 16);
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);
	
	for (i = 0; i <= Count; i++)
	{
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	MySPI_Stop();

}
