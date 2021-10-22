#include "CONF.h"

void CONFIG_Init(void)
{
	uint8_t dat = 0x01;
	uint8_t mydat;
	
	/* 初始化SPI1总线 */
	SPI_BusInit();
	/* 初始化FLASH */
	Flash_Init();
	
	
	
	if (Flash_WriteBuffer(&dat, 0, 1) == 0)
	{
		return;
	}
	
	Flash_ReadBuffer(&mydat, 0, 1);
	
}

