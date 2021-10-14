/*
*********************************************************************************************************
*
*	模块名称 : 串行Flash读写演示程序。
*	文件名称 : demo_spi_flash.c
*	版    本 : V1.0
*	说    明 : 安富莱STM32-V7开发板标配的串行Flash型号为W25Q64, 8M字节
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2020-03-14 armfly  正式发布
*
*	Copyright (C), 2020-2030, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#include "demo_spi_flash.h"
#include "SPI.h"
#include "FLASH.h"

#define TEST_ADDR		0			/* 读写测试地址 */
#define TEST_SIZE		4096		/* 读写测试数据大小 */

/* 仅允许本文件内调用的函数声明 */



/*
*********************************************************************************************************
*	函 数 名: DemoSpiFlash
*	功能说明: 串行EEPROM读写例程
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void DemoSpiFlash(void)
{
	int i;
	SPI_BusInit();
	Flash_Init();
	
	i = 1;
	
	
	
	/* 检测串行Flash OK */
	//printf("检测到串行Flash, ID = %08X, 型号: %s \r\n", FlashInfo.ChipID , FlashInfo.ChipName);
	//printf("    容量 : %dM字节, 扇区大小 : %d字节\r\n", FlashInfo.TotalSize/(1024*1024), FlashInfo.SectorSize);

}

