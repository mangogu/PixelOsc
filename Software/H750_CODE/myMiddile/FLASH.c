#include "CONF.h"

FlashStruct FlashInfo;

#if 0
static void sf_WriteStatus(uint8_t _ucValue);
#endif

static uint8_t s_spiBuf[4*1024];	/* ����д�������ȶ��������������޸Ļ�������������������д */

/*
*********************************************************************************************************
*	�� �� ��: Flash_Init
*	����˵��: ����falshӲ����ʼ���� ����CS GPIO�� ��ȡID��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Flash_Init(void)
{
	/* ����CS GPIO */
	{
		GPIO_InitTypeDef gpio_init;

		/* ��GPIOʱ�� */
		SF_CS_CLK_ENABLE();
		
		gpio_init.Mode = GPIO_MODE_OUTPUT_PP;	/* ����������� */
		gpio_init.Pull = GPIO_NOPULL;					/* ���������費ʹ�� */
		gpio_init.Speed = GPIO_SPEED_HIGH;  	/* GPIO�ٶȵȼ� */	
		gpio_init.Pin = SF_CS_PIN;	
		HAL_GPIO_Init(SF_CS_GPIO, &gpio_init);	
	}
	
	/* ��ȡоƬID, �Զ�ʶ��оƬ�ͺ� */
	Flash_ReadInfo();
}	

/*
*********************************************************************************************************
*	�� �� ��: Flash_SetCS
*	����˵��: ����FALSHƬѡ���ƺ���
*	��    ��: level(0Ϊѡ�У�1Ϊ��ѡ��)
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Flash_SetCS(uint8_t level)
{
	if (level == 0)
	{
		SPIBusEnter();	
		SPI_Init(SPI_BAUDRATEPRESCALER_4, SPI_PHASE_1EDGE, SPI_POLARITY_LOW);		
		SF_CS_0();
	}
	else
	{		
		SF_CS_1();	
		SPIBusExit();		
	}
}

/*
*********************************************************************************************************
*	�� �� ��: Flash_EraseSector
*	����˵��: ����ָ��������
*	��    ��: _uiSectorAddr : ������ַ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Flash_EraseSector(uint32_t _uiSectorAddr)
{
	Flash_WriteEnable();								/* ����дʹ������ */

	/* ������������ */
	Flash_SetCS(0);									/* ʹ��Ƭѡ */
	g_spiLen = 0;
	g_spiTxBuf[g_spiLen++] = CMD_SE;				/* ���Ͳ������� */
	g_spiTxBuf[g_spiLen++] = ((_uiSectorAddr & 0xFF0000) >> 16);	/* ����������ַ�ĸ�8bit */
	g_spiTxBuf[g_spiLen++] = ((_uiSectorAddr & 0xFF00) >> 8);		/* ����������ַ�м�8bit */
	g_spiTxBuf[g_spiLen++] = (_uiSectorAddr & 0xFF);				/* ����������ַ��8bit */	
	bsp_spiTransfer();
	Flash_SetCS(1);									/* ����Ƭѡ */

	Flash_WaitForWriteEnd();							/* �ȴ�����Flash�ڲ�д������� */
}

/*
*********************************************************************************************************
*	�� �� ��: Flash_EraseChip
*	����˵��: ��������оƬ
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Flash_EraseChip(void)
{	
	Flash_WriteEnable();								/* ����дʹ������ */

	/* ������������ */
	Flash_SetCS(0);		/* ʹ��Ƭѡ */
	g_spiLen = 0;
	g_spiTxBuf[g_spiLen++] = CMD_BE;				/* ������Ƭ�������� */
	bsp_spiTransfer();
	Flash_SetCS(1);									/* ����Ƭѡ */

	Flash_WaitForWriteEnd();							/* �ȴ�����Flash�ڲ�д������� */
}

/*
*********************************************************************************************************
*	�� �� ��: Flash_PageWrite
*	����˵��: ҳ��̡�
*	��    ��: _pBuf : ����Դ��������
*			  _uiWriteAddr ��Ŀ�������׵�ַ��
*			  _usSize �����ݸ�����ҳ��С����������256�ֽڵ���������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Flash_PageWrite(uint8_t * _pBuf, uint32_t _uiWriteAddr, uint16_t _usSize)
{
	uint32_t i, j;

	if (FlashInfo.ChipID == SST25VF016B_ID)
	{
		/* AAIָ��Ҫ��������ݸ�����ż�� */
		if ((_usSize < 2) && (_usSize % 2))
		{
			return ;
		}

		Flash_WriteEnable();								/* ����дʹ������ */

		Flash_SetCS(0);									/* ʹ��Ƭѡ */
		g_spiLen = 0;
		g_spiTxBuf[g_spiLen++] = CMD_AAI;								/* ����AAI����(��ַ�Զ����ӱ��) */
		g_spiTxBuf[g_spiLen++] = ((_uiWriteAddr & 0xFF0000) >> 16);		/* ����������ַ�ĸ�8bit */
		g_spiTxBuf[g_spiLen++] = ((_uiWriteAddr & 0xFF00) >> 8);		/* ����������ַ�м�8bit */
		g_spiTxBuf[g_spiLen++] = (_uiWriteAddr & 0xFF);					/* ����������ַ��8bit */		
		g_spiTxBuf[g_spiLen++] = (*_pBuf++);							/* ���͵�1������ */
		g_spiTxBuf[g_spiLen++] = (*_pBuf++);							/* ���͵�2������ */
		bsp_spiTransfer();
		Flash_SetCS(1);									/* ����Ƭѡ */

		Flash_WaitForWriteEnd();							/* �ȴ�����Flash�ڲ�д������� */

		_usSize -= 2;									/* ����ʣ���ֽ��� */

		for (i = 0; i < _usSize / 2; i++)
		{
			Flash_SetCS(0);	/* ʹ��Ƭѡ */	
			g_spiLen = 0;
			g_spiTxBuf[g_spiLen++] = (CMD_AAI);						/* ����AAI����(��ַ�Զ����ӱ��) */
			g_spiTxBuf[g_spiLen++] = (*_pBuf++);					/* �������� */
			g_spiTxBuf[g_spiLen++] = (*_pBuf++);					/* �������� */
			bsp_spiTransfer();
			Flash_SetCS(1);								/* ����Ƭѡ */
			Flash_WaitForWriteEnd();						/* �ȴ�����Flash�ڲ�д������� */
		}

		/* ����д����״̬ */
		Flash_SetCS(0);
		g_spiLen = 0;
		g_spiTxBuf[g_spiLen++] = (CMD_DISWR);
		bsp_spiTransfer();
		Flash_SetCS(1);

		Flash_WaitForWriteEnd();							/* �ȴ�����Flash�ڲ�д������� */
	}
	else	/* for MX25L1606E �� W25Q64BV */
	{
		for (j = 0; j < _usSize / 256; j++)
		{
			Flash_WriteEnable();								/* ����дʹ������ */

			Flash_SetCS(0);									/* ʹ��Ƭѡ */
			g_spiLen = 0;
			g_spiTxBuf[g_spiLen++] = (0x02);								/* ����AAI����(��ַ�Զ����ӱ��) */
			g_spiTxBuf[g_spiLen++] = ((_uiWriteAddr & 0xFF0000) >> 16);		/* ����������ַ�ĸ�8bit */
			g_spiTxBuf[g_spiLen++] = ((_uiWriteAddr & 0xFF00) >> 8);		/* ����������ַ�м�8bit */
			g_spiTxBuf[g_spiLen++] = (_uiWriteAddr & 0xFF);					/* ����������ַ��8bit */
			for (i = 0; i < 256; i++)
			{
				g_spiTxBuf[g_spiLen++] = (*_pBuf++);		/* �������� */
			}
			bsp_spiTransfer();
			Flash_SetCS(1);								/* ��ֹƬѡ */

			Flash_WaitForWriteEnd();						/* �ȴ�����Flash�ڲ�д������� */

			_uiWriteAddr += 256;
		}

		/* ����д����״̬ */
		Flash_SetCS(0);
		g_spiLen = 0;
		g_spiTxBuf[g_spiLen++] = (CMD_DISWR);
		bsp_spiTransfer();
		Flash_SetCS(1);

		Flash_WaitForWriteEnd();							/* �ȴ�����Flash�ڲ�д������� */
	}
}

/*
*********************************************************************************************************
*	�� �� ��: Flash_ReadBuffer
*	����˵��: ������ȡ�����ֽڣ��ֽڸ������ܳ���оƬ������
*	��    ��:  	_pBuf : ����Դ��������
*				_uiReadAddr ���׵�ַ
*				_usSize �����ݸ���, ���ܳ���оƬ������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Flash_ReadBuffer(uint8_t * _pBuf, uint32_t _uiReadAddr, uint32_t _uiSize)
{
	uint16_t rem;
	uint16_t i;
	
	/* �����ȡ�����ݳ���Ϊ0���߳�������Flash��ַ�ռ䣬��ֱ�ӷ��� */
	if ((_uiSize == 0) ||(_uiReadAddr + _uiSize) > FlashInfo.TotalSize)
	{
		return;
	}

	/* ������������ */
	Flash_SetCS(0);									/* ʹ��Ƭѡ */
	g_spiLen = 0;
	g_spiTxBuf[g_spiLen++] = (CMD_READ);							/* ���Ͷ����� */
	g_spiTxBuf[g_spiLen++] = ((_uiReadAddr & 0xFF0000) >> 16);	/* ����������ַ�ĸ�8bit */
	g_spiTxBuf[g_spiLen++] = ((_uiReadAddr & 0xFF00) >> 8);		/* ����������ַ�м�8bit */
	g_spiTxBuf[g_spiLen++] = (_uiReadAddr & 0xFF);				/* ����������ַ��8bit */
	bsp_spiTransfer();
	
	/* ��ʼ�����ݣ���Ϊ�ײ�DMA���������ޣ�����ְ��� */
	for (i = 0; i < _uiSize / SPI_BUFFER_SIZE; i++)
	{
		g_spiLen = SPI_BUFFER_SIZE;
		bsp_spiTransfer();
		
		memcpy(_pBuf, g_spiRxBuf, SPI_BUFFER_SIZE);
		_pBuf += SPI_BUFFER_SIZE;
	}
	
	rem = _uiSize % SPI_BUFFER_SIZE;	/* ʣ���ֽ� */
	if (rem > 0)
	{
		g_spiLen = rem;
		bsp_spiTransfer();
		
		memcpy(_pBuf, g_spiRxBuf, rem);
	}
	
	Flash_SetCS(1);									/* ����Ƭѡ */
}

/*
*********************************************************************************************************
*	�� �� ��: Flash_CmpData
*	����˵��: �Ƚ�Flash�����ݡ�
*	��    ��:  	_ucpTar : ���ݻ�������
*				_uiSrcAddr ��Flash��ַ��
*				_uiSize �����ݸ���, ���ܳ���оƬ��������
*	�� �� ֵ: 0 = ���, 1 = ����
*********************************************************************************************************
*/
static uint8_t Flash_CmpData(uint32_t _uiSrcAddr, uint8_t *_ucpTar, uint32_t _uiSize)
{
	uint16_t i, j;
	uint16_t rem;

	/* �����ȡ�����ݳ���Ϊ0���߳�������Flash��ַ�ռ䣬��ֱ�ӷ��� */
	if ((_uiSrcAddr + _uiSize) > FlashInfo.TotalSize)
	{
		return 1;
	}

	if (_uiSize == 0)
	{
		return 0;
	}

	Flash_SetCS(0);									/* ʹ��Ƭѡ */
	g_spiLen = 0;
	g_spiTxBuf[g_spiLen++] = (CMD_READ);							/* ���Ͷ����� */
	g_spiTxBuf[g_spiLen++] = ((_uiSrcAddr & 0xFF0000) >> 16);		/* ����������ַ�ĸ�8bit */
	g_spiTxBuf[g_spiLen++] = ((_uiSrcAddr & 0xFF00) >> 8);			/* ����������ַ�м�8bit */
	g_spiTxBuf[g_spiLen++] = (_uiSrcAddr & 0xFF);					/* ����������ַ��8bit */
	bsp_spiTransfer();
	
	/* ��ʼ�����ݣ���Ϊ�ײ�DMA���������ޣ�����ְ��� */
	for (i = 0; i < _uiSize / SPI_BUFFER_SIZE; i++)
	{
		g_spiLen = SPI_BUFFER_SIZE;
		bsp_spiTransfer();
		
		for (j = 0; j < SPI_BUFFER_SIZE; j++)
		{
			if (g_spiRxBuf[j] != *_ucpTar++)
			{
				goto NOTEQ;		/* ����� */
			}
		}
	}
	
	rem = _uiSize % SPI_BUFFER_SIZE;	/* ʣ���ֽ� */
	if (rem > 0)
	{
		g_spiLen = rem;
		bsp_spiTransfer();
		
		for (j = 0; j < rem; j++)
		{
			if (g_spiRxBuf[j] != *_ucpTar++)
			{
				goto NOTEQ;		/* ����� */
			}
		}
	}
	Flash_SetCS(1);
	return 0;		/* ��� */
	
NOTEQ:	
	Flash_SetCS(1);	/* ����� */
	return 1;
}

/*
*********************************************************************************************************
*	�� �� ��: Flash_NeedErase
*	����˵��: �ж�дPAGEǰ�Ƿ���Ҫ�Ȳ�����
*	��    ��:   _ucpOldBuf �� �����ݡ�
*			   _ucpNewBuf �� �����ݡ�
*			   _uiLen �����ݸ�����
*	�� �� ֵ: 0 : ����Ҫ������ 1 ����Ҫ����
*********************************************************************************************************
*/
static uint8_t Flash_NeedErase(uint8_t * _ucpOldBuf, uint8_t *_ucpNewBuf, uint16_t _usLen)
{
	uint16_t i;
	uint8_t ucOld;

	/*
	�㷨��1����old ��, new ����
	      old    new
		  1101   0101
	~     1111
		= 0010   0101

	�㷨��2��: old �󷴵Ľ���� new λ��
		  0010   old
	&	  0101   new
		 =0000

	�㷨��3��: ���Ϊ0,���ʾ�������. �����ʾ��Ҫ����
	*/

	for (i = 0; i < _usLen; i++)
	{
		ucOld = *_ucpOldBuf++;
		ucOld = ~ucOld;

		/* ע������д��: if (ucOld & (*_ucpNewBuf++) != 0) */
		if ((ucOld & (*_ucpNewBuf++)) != 0)
		{
			return 1;
		}
	}
	return 0;
}

/*
*********************************************************************************************************
*	�� �� ��: Flash_AutoWriteSector
*	����˵��: д1��������У��,�������ȷ������д���Σ��������Զ���ɲ���������
*	��    ��:  	_pBuf : ����Դ��������
*				_uiWriteAddr ��Ŀ�������׵�ַ
*				_usSize �����ݸ��������ܳ���������С��
*	�� �� ֵ: 0 : ���� 1 �� �ɹ�
*********************************************************************************************************
*/
static uint8_t Flash_AutoWriteSector(uint8_t *_ucpSrc, uint32_t _uiWrAddr, uint16_t _usWrLen)
{
	uint16_t i;
	uint16_t j;					/* ������ʱ */
	uint32_t uiFirstAddr;		/* ������ַ */
	uint8_t ucNeedErase;		/* 1��ʾ��Ҫ���� */
	uint8_t cRet;

	/* ����Ϊ0ʱ����������,ֱ����Ϊ�ɹ� */
	if (_usWrLen == 0)
	{
		return 1;
	}

	/* ���ƫ�Ƶ�ַ����оƬ�������˳� */
	if (_uiWrAddr >= FlashInfo.TotalSize)
	{
		return 0;
	}

	/* ������ݳ��ȴ����������������˳� */
	if (_usWrLen > FlashInfo.SectorSize)
	{
		return 0;
	}

	/* ���FLASH�е�����û�б仯,��дFLASH */
	Flash_ReadBuffer(s_spiBuf, _uiWrAddr, _usWrLen);
	if (memcmp(s_spiBuf, _ucpSrc, _usWrLen) == 0)
	{
		return 1;
	}

	/* �ж��Ƿ���Ҫ�Ȳ������� */
	/* ����������޸�Ϊ�����ݣ�����λ���� 1->0 ���� 0->0, ���������,���Flash���� */
	ucNeedErase = 0;
	if (Flash_NeedErase(s_spiBuf, _ucpSrc, _usWrLen))
	{
		ucNeedErase = 1;
	}

	uiFirstAddr = _uiWrAddr & (~(FlashInfo.SectorSize - 1));

	if (_usWrLen == FlashInfo.SectorSize)		/* ������������д */
	{
		for	(i = 0; i < FlashInfo.SectorSize; i++)
		{
			s_spiBuf[i] = _ucpSrc[i];
		}
	}
	else						/* ��д�������� */
	{
		/* �Ƚ��������������ݶ��� */
		Flash_ReadBuffer(s_spiBuf, uiFirstAddr, FlashInfo.SectorSize);

		/* ���������ݸ��� */
		i = _uiWrAddr & (FlashInfo.SectorSize - 1);
		memcpy(&s_spiBuf[i], _ucpSrc, _usWrLen);
	}

	/* д��֮�����У�飬�������ȷ����д�����3�� */
	cRet = 0;
	for (i = 0; i < 3; i++)
	{

		/* ����������޸�Ϊ�����ݣ�����λ���� 1->0 ���� 0->0, ���������,���Flash���� */
		if (ucNeedErase == 1)
		{
			Flash_EraseSector(uiFirstAddr);		/* ����1������ */
		}

		/* ���һ������ */
		Flash_PageWrite(s_spiBuf, uiFirstAddr, FlashInfo.SectorSize);

		if (Flash_CmpData(_uiWrAddr, _ucpSrc, _usWrLen) == 0)
		{
			cRet = 1;
			break;
		}
		else
		{
			if (Flash_CmpData(_uiWrAddr, _ucpSrc, _usWrLen) == 0)
			{
				cRet = 1;
				break;
			}

			/* ʧ�ܺ��ӳ�һ��ʱ�������� */
			for (j = 0; j < 10000; j++);
		}
	}

	return cRet;
}

/*
*********************************************************************************************************
*	�� �� ��: Flash_WriteBuffer
*	����˵��: д1��������У��,�������ȷ������д���Σ��������Զ���ɲ���������
*	��    ��:  _pBuf : ����Դ��������
*			   _uiWrAddr ��Ŀ�������׵�ַ
*			   _usSize �����ݸ����������С�������ܳ���оƬ������
*	�� �� ֵ: 1 : �ɹ��� 0 �� ʧ��
*********************************************************************************************************
*/
uint8_t Flash_WriteBuffer(uint8_t* _pBuf, uint32_t _uiWriteAddr, uint32_t _usWriteSize)
{
	uint32_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

	Addr = _uiWriteAddr % FlashInfo.SectorSize;
	count = FlashInfo.SectorSize - Addr;
	NumOfPage =  _usWriteSize / FlashInfo.SectorSize;
	NumOfSingle = _usWriteSize % FlashInfo.SectorSize;

	if (Addr == 0) /* ��ʼ��ַ�������׵�ַ  */
	{
		if (NumOfPage == 0) /* ���ݳ���С��������С */
		{
			if (Flash_AutoWriteSector(_pBuf, _uiWriteAddr, _usWriteSize) == 0)
			{
				return 0;
			}
		}
		else 	/* ���ݳ��ȴ��ڵ���������С */
		{
			while (NumOfPage--)
			{
				if (Flash_AutoWriteSector(_pBuf, _uiWriteAddr, FlashInfo.SectorSize) == 0)
				{
					return 0;
				}
				_uiWriteAddr +=  FlashInfo.SectorSize;
				_pBuf += FlashInfo.SectorSize;
			}
			if (Flash_AutoWriteSector(_pBuf, _uiWriteAddr, NumOfSingle) == 0)
			{
				return 0;
			}
		}
	}
	else  /* ��ʼ��ַ���������׵�ַ  */
	{
		if (NumOfPage == 0) /* ���ݳ���С��������С */
		{
			if (NumOfSingle > count)  /* (_usWriteSize + _uiWriteAddr) > SPI_FLASH_PAGESIZE */
			{
				temp = NumOfSingle - count;

				if (Flash_AutoWriteSector(_pBuf, _uiWriteAddr, count) == 0)
				{
					return 0;
				}

				_uiWriteAddr +=  count;
				_pBuf += count;

				if (Flash_AutoWriteSector(_pBuf, _uiWriteAddr, temp) == 0)
				{
					return 0;
				}
			}
			else
			{
				if (Flash_AutoWriteSector(_pBuf, _uiWriteAddr, _usWriteSize) == 0)
				{
					return 0;
				}
			}
		}
		else	/* ���ݳ��ȴ��ڵ���������С */
		{
			_usWriteSize -= count;
			NumOfPage =  _usWriteSize / FlashInfo.SectorSize;
			NumOfSingle = _usWriteSize % FlashInfo.SectorSize;
			if (Flash_AutoWriteSector(_pBuf, _uiWriteAddr, count) == 0)
			{
				return 0;
			}

			_uiWriteAddr +=  count;
			_pBuf += count;

			while (NumOfPage--)
			{
				if (Flash_AutoWriteSector(_pBuf, _uiWriteAddr, FlashInfo.SectorSize) == 0)
				{
					return 0;
				}
				_uiWriteAddr +=  FlashInfo.SectorSize;
				_pBuf += FlashInfo.SectorSize;
			}

			if (NumOfSingle != 0)
			{
				if (Flash_AutoWriteSector(_pBuf, _uiWriteAddr, NumOfSingle) == 0)
				{
					return 0;
				}
			}
		}
	}
	return 1;	/* �ɹ� */
}

/*
*********************************************************************************************************
*	�� �� ��: Flash_ReadID
*	����˵��: ��ȡ����ID
*	��    ��:  ��
*	�� �� ֵ: 32bit������ID (���8bit��0����ЧIDλ��Ϊ24bit��
*********************************************************************************************************
*/
uint32_t Flash_ReadID(void)
{
	uint32_t uiID;
	uint8_t id1, id2, id3;

	Flash_SetCS(0);							/* ʹ��Ƭѡ */
	g_spiLen = 0;
	g_spiTxBuf[0] = (CMD_RDID);				/* ���Ͷ�ID���� */
	g_spiLen = 4;
	bsp_spiTransfer();
	
	id1 = g_spiRxBuf[1];					/* ��ID�ĵ�1���ֽ� */
	id2 = g_spiRxBuf[2];					/* ��ID�ĵ�2���ֽ� */
	id3 = g_spiRxBuf[3];					/* ��ID�ĵ�3���ֽ� */
	Flash_SetCS(1);							/* ����Ƭѡ */

	uiID = ((uint32_t)id1 << 16) | ((uint32_t)id2 << 8) | id3;

	return uiID;
}

/*
*********************************************************************************************************
*	�� �� ��: Flash_ReadInfo
*	����˵��: ��ȡ����ID,�������������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Flash_ReadInfo(void)
{
	/* �Զ�ʶ����Flash�ͺ� */
	{
		FlashInfo.ChipID = Flash_ReadID();	/* оƬID */

		switch (FlashInfo.ChipID)
		{
			case SST25VF016B_ID:
				strcpy(FlashInfo.ChipName, "SST25VF016B");
				FlashInfo.TotalSize = 2 * 1024 * 1024;	/* ������ = 2M */
				FlashInfo.SectorSize = 4 * 1024;		/* ������С = 4K */
				break;

			case MX25L1606E_ID:
				strcpy(FlashInfo.ChipName, "MX25L1606E");
				FlashInfo.TotalSize = 2 * 1024 * 1024;	/* ������ = 2M */
				FlashInfo.SectorSize = 4 * 1024;		/* ������С = 4K */
				break;

			case W25Q64BV_ID:
				strcpy(FlashInfo.ChipName, "W25Q64");
				FlashInfo.TotalSize = 8 * 1024 * 1024;	/* ������ = 8M */
				FlashInfo.SectorSize = 4 * 1024;		/* ������С = 4K */
				break;
			
			case W25Q128_ID:
				strcpy(FlashInfo.ChipName, "W25Q128");
				FlashInfo.TotalSize = 16 * 1024 * 1024;	/* ������ = 8M */
				FlashInfo.SectorSize = 4 * 1024;		/* ������С = 4K */
				break;			

			default:
				strcpy(FlashInfo.ChipName, "Unknow Flash");
				FlashInfo.TotalSize = 2 * 1024 * 1024;
				FlashInfo.SectorSize = 4 * 1024;
				break;
		}
	}
}

/*
*********************************************************************************************************
*	�� �� ��: Flash_WriteEnable
*	����˵��: ����������дʹ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void Flash_WriteEnable(void)
{
	Flash_SetCS(0);									/* ʹ��Ƭѡ */
	g_spiLen = 0;
	g_spiTxBuf[g_spiLen++] = (CMD_WREN);			/* �������� */
	bsp_spiTransfer();
	Flash_SetCS(1);									/* ����Ƭѡ */
}

#if 0
/*
*********************************************************************************************************
*	�� �� ��: sf_WriteStatus
*	����˵��: д״̬�Ĵ���
*	��    ��:  _ucValue : ״̬�Ĵ�����ֵ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void sf_WriteStatus(uint8_t _ucValue)
{
	if (FlashInfo.ChipID == SST25VF016B_ID)
	{
		/* ��1������ʹ��д״̬�Ĵ��� */
		Flash_SetCS(0);									/* ʹ��Ƭѡ */
		g_spiLen = 0;
		g_spiTxBuf[g_spiLen++] = (CMD_EWRSR);							/* ������� ����д״̬�Ĵ��� */
		bsp_spiTransfer();
		Flash_SetCS(1);									/* ����Ƭѡ */

		/* ��2������д״̬�Ĵ��� */
		Flash_SetCS(0);									/* ʹ��Ƭѡ */
		g_spiLen = 0;
		g_spiTxBuf[g_spiLen++] = (CMD_WRSR);							/* ������� д״̬�Ĵ��� */
		g_spiTxBuf[g_spiLen++] = (_ucValue);							/* �������ݣ�״̬�Ĵ�����ֵ */
		bsp_spiTransfer();
		Flash_SetCS(1);									/* ����Ƭѡ */
	}
	else
	{
		Flash_SetCS(0);									/* ʹ��Ƭѡ */
		g_spiLen = 0;
		g_spiTxBuf[g_spiLen++] = (CMD_WRSR);							/* ������� д״̬�Ĵ��� */
		g_spiTxBuf[g_spiLen++] = (_ucValue);							/* �������ݣ�״̬�Ĵ�����ֵ */
		bsp_spiTransfer();
		Flash_SetCS(1);									/* ����Ƭѡ */
	}
}
#endif

/*
*********************************************************************************************************
*	�� �� ��: Flash_WaitForWriteEnd
*	����˵��: ����ѭ����ѯ�ķ�ʽ�ȴ������ڲ�д�������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void Flash_WaitForWriteEnd(void)
{
	Flash_SetCS(0);									/* ʹ��Ƭѡ */
	g_spiTxBuf[0] = (CMD_RDSR);						/* ������� ��״̬�Ĵ��� */
	g_spiLen = 2;
	bsp_spiTransfer();	
	Flash_SetCS(1);									/* ����Ƭѡ */
	
	while(1)
	{
		Flash_SetCS(0);									/* ʹ��Ƭѡ */
		g_spiTxBuf[0] = (CMD_RDSR);						/* ������� ��״̬�Ĵ��� */
		g_spiTxBuf[1] = 0;								/* �޹����� */
		g_spiLen = 2;
		bsp_spiTransfer();	
		Flash_SetCS(1);									/* ����Ƭѡ */
		
		if ((g_spiRxBuf[1] & WIP_FLAG) != SET)			/* �ж�״̬�Ĵ�����æ��־λ */
		{
			break;
		}		
	}	
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
