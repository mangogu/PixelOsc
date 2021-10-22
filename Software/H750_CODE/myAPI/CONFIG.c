#include "CONF.h"

void CONFIG_Init(void)
{
	uint8_t dat = 0x01;
	uint8_t mydat;
	
	/* ��ʼ��SPI1���� */
	SPI_BusInit();
	/* ��ʼ��FLASH */
	Flash_Init();
	
	
	
	if (Flash_WriteBuffer(&dat, 0, 1) == 0)
	{
		return;
	}
	
	Flash_ReadBuffer(&mydat, 0, 1);
	
}

