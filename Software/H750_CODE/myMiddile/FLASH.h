#ifndef __FLASH_H
#define __FLASH_H

#include "CONF.h"


#define SF_MAX_PAGE_SIZE	(4 * 1024)

/* 串行Flash的片选GPIO端口， PA15  */
#define SF_CS_CLK_ENABLE() 			__HAL_RCC_GPIOD_CLK_ENABLE()
#define SF_CS_GPIO							GPIOA
#define SF_CS_PIN								GPIO_PIN_15

#define SF_CS_0()								SF_CS_GPIO->BSRR = ((uint32_t)SF_CS_PIN << 16U) 
#define SF_CS_1()								SF_CS_GPIO->BSRR = SF_CS_PIN
	
#define CMD_AAI       0xAD  	/* AAI 连续编程指令(FOR SST25VF016B) */
#define CMD_DISWR	  	0x04		/* 禁止写, 退出AAI状态 */
#define CMD_EWRSR	  	0x50		/* 允许写状态寄存器的命令 */
#define CMD_WRSR      0x01  	/* 写状态寄存器命令 */
#define CMD_WREN      0x06		/* 写使能命令 */
#define CMD_READ      0x03  	/* 读数据区命令 */
#define CMD_RDSR      0x05		/* 读状态寄存器命令 */
#define CMD_RDID      0x9F		/* 读器件ID命令 */
#define CMD_SE        0x20		/* 擦除扇区命令 */
#define CMD_BE        0xC7		/* 批量擦除命令 */
#define DUMMY_BYTE    0xA5		/* 哑命令，可以为任意值，用于读操作 */
#define WIP_FLAG      0x01		/* 状态寄存器中的正在编程标志（WIP) */


/* 定义串行Flash ID */
enum
{
	SST25VF016B_ID = 0xBF2541,
	MX25L1606E_ID  = 0xC22015,
	W25Q64BV_ID    = 0xEF4017, /* BV, JV, FV */
	W25Q128_ID     = 0xEF4018
};

typedef struct
{
	uint32_t ChipID;		/* 芯片ID */
	char ChipName[16];		/* 芯片型号字符串，主要用于显示 */
	uint32_t TotalSize;		/* 总容量 */
	uint16_t SectorSize;		/* 扇区大小 */
}FlashStruct;

void Flash_Init(void);
uint32_t Flash_ReadID(void);
void Flash_EraseChip(void);
void Flash_EraseSector(uint32_t _uiSectorAddr);
void Flash_PageWrite(uint8_t * _pBuf, uint32_t _uiWriteAddr, uint16_t _usSize);
uint8_t Flash_WriteBuffer(uint8_t* _pBuf, uint32_t _uiWriteAddr, uint32_t _usWriteSize);
void Flash_ReadBuffer(uint8_t * _pBuf, uint32_t _uiReadAddr, uint32_t _uiSize);
void Flash_ReadInfo(void);

static void Flash_WriteEnable(void);
static void Flash_WaitForWriteEnd(void);
static uint8_t Flash_NeedErase(uint8_t * _ucpOldBuf, uint8_t *_ucpNewBuf, uint16_t _uiLen);
static uint8_t Flash_CmpData(uint32_t _uiSrcAddr, uint8_t *_ucpTar, uint32_t _uiSize);
static uint8_t Flash_AutoWriteSector(uint8_t *_ucpSrc, uint32_t _uiWrAddr, uint16_t _usWrLen);

extern FlashStruct FlashInfo;

#endif
