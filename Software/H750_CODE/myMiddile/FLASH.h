#ifndef __FLASH_H
#define __FLASH_H

#include "CONF.h"


#define SF_MAX_PAGE_SIZE	(4 * 1024)

/* ����Flash��ƬѡGPIO�˿ڣ� PA15  */
#define SF_CS_CLK_ENABLE() 			__HAL_RCC_GPIOD_CLK_ENABLE()
#define SF_CS_GPIO							GPIOA
#define SF_CS_PIN								GPIO_PIN_15

#define SF_CS_0()								SF_CS_GPIO->BSRR = ((uint32_t)SF_CS_PIN << 16U) 
#define SF_CS_1()								SF_CS_GPIO->BSRR = SF_CS_PIN
	
#define CMD_AAI       0xAD  	/* AAI �������ָ��(FOR SST25VF016B) */
#define CMD_DISWR	  	0x04		/* ��ֹд, �˳�AAI״̬ */
#define CMD_EWRSR	  	0x50		/* ����д״̬�Ĵ��������� */
#define CMD_WRSR      0x01  	/* д״̬�Ĵ������� */
#define CMD_WREN      0x06		/* дʹ������ */
#define CMD_READ      0x03  	/* ������������ */
#define CMD_RDSR      0x05		/* ��״̬�Ĵ������� */
#define CMD_RDID      0x9F		/* ������ID���� */
#define CMD_SE        0x20		/* ������������ */
#define CMD_BE        0xC7		/* ������������ */
#define DUMMY_BYTE    0xA5		/* ���������Ϊ����ֵ�����ڶ����� */
#define WIP_FLAG      0x01		/* ״̬�Ĵ����е����ڱ�̱�־��WIP) */


/* ���崮��Flash ID */
enum
{
	SST25VF016B_ID = 0xBF2541,
	MX25L1606E_ID  = 0xC22015,
	W25Q64BV_ID    = 0xEF4017, /* BV, JV, FV */
	W25Q128_ID     = 0xEF4018
};

typedef struct
{
	uint32_t ChipID;		/* оƬID */
	char ChipName[16];		/* оƬ�ͺ��ַ�������Ҫ������ʾ */
	uint32_t TotalSize;		/* ������ */
	uint16_t SectorSize;		/* ������С */
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
