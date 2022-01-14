#include "SPI.h"

/* ������� */
static SPI_HandleTypeDef hspi = {0};
static DMA_HandleTypeDef hdma_tx;
static DMA_HandleTypeDef hdma_rx;
static uint32_t s_BaudRatePrescaler;
static uint32_t s_CLKPhase;
static uint32_t s_CLKPolarity;
uint32_t g_spiLen;	
uint8_t  g_spi_busy; /* SPIæ״̬��0��ʾ���У�1��ʾæ */
__IO uint32_t wTransferState = TRANSFER_WAIT;


/* ��ѯģʽ */
#if defined (USE_SPI_POLL)

uint8_t g_spiTxBuf[SPI_BUFFER_SIZE];  
uint8_t g_spiRxBuf[SPI_BUFFER_SIZE];

/* �ж�ģʽ */
#elif defined (USE_SPI_INT)

uint8_t g_spiTxBuf[SPI_BUFFER_SIZE];   
uint8_t g_spiRxBuf[SPI_BUFFER_SIZE];

/* DMAģʽʹ�õ�SRAM4 */
#elif defined (USE_SPI_DMA)
    #if defined ( __CC_ARM )    /* IAR *******/
        __attribute__((section (".RAM_D3"))) uint8_t g_spiTxBuf[SPI_BUFFER_SIZE];   
        __attribute__((section (".RAM_D3"))) uint8_t g_spiRxBuf[SPI_BUFFER_SIZE];
    #elif defined (__ICCARM__)   /* MDK ********/
        #pragma location = ".RAM_D3"
        uint8_t g_spiTxBuf[SPI_BUFFER_SIZE];   
        #pragma location = ".RAM_D3"
        uint8_t g_spiRxBuf[SPI_BUFFER_SIZE];
    #endif
#endif


/*
*********************************************************************************************************
*	�� �� ��: SPI_BusInit
*	����˵��: ����SPI���ߡ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void SPI_BusInit(void)
{	
	/* ��SPI��Ϊ���� */
	/* SPIæ״̬��0��ʾ���У�1��ʾæ */
	g_spi_busy = 0;
	
	SPI_Init(SPI_BAUDRATEPRESCALER_8, SPI_PHASE_1EDGE, SPI_POLARITY_LOW);
}

/*
*********************************************************************************************************
*	�� �� ��: SPI_Init
*	����˵��: ����SPI���߲�����ʱ�ӷ�Ƶ��ʱ����λ��ʱ�Ӽ��ԡ�
*	��    ��: _BaudRatePrescaler  SPI����ʱ�ӷ�Ƶ���ã�֧�ֵĲ������£�
*                                 SPI_BAUDRATEPRESCALER_2    2��Ƶ
*                                 SPI_BAUDRATEPRESCALER_4    4��Ƶ
*                                 SPI_BAUDRATEPRESCALER_8    8��Ƶ
*                                 SPI_BAUDRATEPRESCALER_16   16��Ƶ
*                                 SPI_BAUDRATEPRESCALER_32   32��Ƶ
*                                 SPI_BAUDRATEPRESCALER_64   64��Ƶ
*                                 SPI_BAUDRATEPRESCALER_128  128��Ƶ
*                                 SPI_BAUDRATEPRESCALER_256  256��Ƶ
*                                                        
*             _CLKPhase           ʱ����λ��֧�ֵĲ������£�
*                                 SPI_PHASE_1EDGE     SCK���ŵĵ�1�����ز�����ĵ�1������
*                                 SPI_PHASE_2EDGE     SCK���ŵĵ�2�����ز�����ĵ�1������
*                                 
*             _CLKPolarity        ʱ�Ӽ��ԣ�֧�ֵĲ������£�
*                                 SPI_POLARITY_LOW    SCK�����ڿ���״̬���ڵ͵�ƽ
*                                 SPI_POLARITY_HIGH   SCK�����ڿ���״̬���ڸߵ�ƽ
*
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void SPI_Init(uint32_t _BaudRatePrescaler, uint32_t _CLKPhase, uint32_t _CLKPolarity)
{
	/* ���ִ��Ч�ʣ�ֻ����SPIӲ�����������仯ʱ����ִ��HAL_Init */
	if (s_BaudRatePrescaler == _BaudRatePrescaler && s_CLKPhase == _CLKPhase && s_CLKPolarity == _CLKPolarity)
	{		
		return;
	}

	s_BaudRatePrescaler = _BaudRatePrescaler;	
	s_CLKPhase = _CLKPhase;
	s_CLKPolarity = _CLKPolarity;
	
	/* ����SPI���� */
	hspi.Instance               = SPI1;                   /* ����SPI */
	hspi.Init.BaudRatePrescaler = _BaudRatePrescaler;     /* ���ò����� */
	hspi.Init.Direction         = SPI_DIRECTION_2LINES;   /* ȫ˫�� */
	hspi.Init.CLKPhase          = _CLKPhase;              /* ����ʱ����λ */
	hspi.Init.CLKPolarity       = _CLKPolarity;           /* ����ʱ�Ӽ��� */
	hspi.Init.DataSize          = SPI_DATASIZE_8BIT;      /* �������ݿ�� */
	hspi.Init.FirstBit          = SPI_FIRSTBIT_MSB;       /* ���ݴ����ȴ���λ */
	hspi.Init.TIMode            = SPI_TIMODE_DISABLE;     /* ��ֹTIģʽ  */
	hspi.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE; /* ��ֹCRC */
	hspi.Init.CRCPolynomial     = 7;                       /* ��ֹCRC�󣬴�λ��Ч */
	hspi.Init.CRCLength         = SPI_CRC_LENGTH_8BIT;     /* ��ֹCRC�󣬴�λ��Ч */
	hspi.Init.NSS               = SPI_NSS_SOFT;               /* ʹ�������ʽ����Ƭѡ���� */
	hspi.Init.FifoThreshold     = SPI_FIFO_THRESHOLD_01DATA;  /* ����FIFO��С��һ�������� */
	hspi.Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;      /* ��ֹ������� */
	hspi.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE; /* ��ֹSPI��SPI������ű��ֵ�ǰ״̬ */  
	hspi.Init.Mode 			 	= SPI_MODE_MASTER;            /* SPI����������ģʽ */

	/* ��λ���� */
	if (HAL_SPI_DeInit(&hspi) != HAL_OK)
	{
		Error_Handler();
	}	

	/* ��ʼ������ */
	if (HAL_SPI_Init(&hspi) != HAL_OK)
	{
		Error_Handler();
	}	
}

/*
*********************************************************************************************************
*	�� �� ��: SPI_Init
*	����˵��: ����SPI����ʱ�ӣ�GPIO���жϣ�DMA��
*	��    ��: SPI_HandleTypeDef ����ָ�����
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void HAL_SPI_MspInit(SPI_HandleTypeDef *_hspi)
{
	/* ���� SPI����GPIO : SCK MOSI MISO */
	{
		GPIO_InitTypeDef  GPIO_InitStruct;
			
		/* ����GPIOʱ�� */
		SPI1_SCK_CLK_ENABLE();
		SPI1_MISO_CLK_ENABLE();
		SPI1_MOSI_CLK_ENABLE();
		/* ����SPI1ʱ�� */
		SPI1_CLK_ENABLE();

		/* SPI SCK */
		GPIO_InitStruct.Pin       = SPI1_SCK_PIN;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_NOPULL;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = SPI1_SCK_AF;
		HAL_GPIO_Init(SPI1_SCK_GPIO, &GPIO_InitStruct);

		/* SPI MISO */
		GPIO_InitStruct.Pin = SPI1_MISO_PIN;
		GPIO_InitStruct.Alternate = SPI1_MISO_AF;
		HAL_GPIO_Init(SPI1_MISO_GPIO, &GPIO_InitStruct);

		/* SPI MOSI */
		GPIO_InitStruct.Pin = SPI1_MOSI_PIN;
		GPIO_InitStruct.Alternate = SPI1_MOSI_AF;
		HAL_GPIO_Init(SPI1_MOSI_GPIO, &GPIO_InitStruct);
	}

	/* ����DMA��NVIC */
	#ifdef USE_SPI_DMA
	{
		/* ʹ��DMAʱ�� */
		DMAx_CLK_ENABLE();      

		/* SPI DMA�������� */		
		hdma_tx.Instance                 = SPI1_TX_DMA_STREAM;      /* ����ʹ�õ�DMA������ */
		hdma_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;    /* ��ֹFIFO*/
		hdma_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL; /* ��ֹFIFO��λ�������ã��������÷�ֵ */
		hdma_tx.Init.MemBurst            = DMA_MBURST_SINGLE;	    /* ��ֹFIFO��λ�������ã����ڴ洢��ͻ�� */
		hdma_tx.Init.PeriphBurst         = DMA_PBURST_SINGLE;	    /* ��ֹFIFO��λ�������ã���������ͻ�� */
		hdma_tx.Init.Request             = SPI1_TX_DMA_REQUEST;     /* �������� */  
		hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;    /* ���䷽���ǴӴ洢�������� */  
		hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;        /* �����ַ������ֹ */ 
		hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;         /* �洢����ַ����ʹ�� */  
		hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;     /* �������ݴ���λ��ѡ���ֽڣ���8bit */ 
		hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;     /* �洢�����ݴ���λ��ѡ���ֽڣ���8bit */    
		hdma_tx.Init.Mode                = DMA_NORMAL;              /* ����ģʽ */
		hdma_tx.Init.Priority            = DMA_PRIORITY_LOW;        /* ���ȼ��� */

		 /* ��λDMA */
		if(HAL_DMA_DeInit(&hdma_tx) != HAL_OK)
		{
			Error_Handler(__FILE__, __LINE__);     
		}
		
		 /* ��ʼ��DMA */
		if(HAL_DMA_Init(&hdma_tx) != HAL_OK)
		{
			Error_Handler(__FILE__, __LINE__);     
		}

		/* ����DMA�����SPI */
		__HAL_LINKDMA(_hspi, hdmatx, hdma_tx);	

		/* SPI DMA�������� */	
		hdma_rx.Instance                 = SPI1_RX_DMA_STREAM;     /* ����ʹ�õ�DMA������ */
		hdma_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;   /* ��ֹFIFO*/
		hdma_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;/* ��ֹFIFO��λ�������ã��������÷�ֵ */
		hdma_rx.Init.MemBurst            = DMA_MBURST_SINGLE;	   /* ��ֹFIFO��λ�������ã����ڴ洢��ͻ�� */
		hdma_rx.Init.PeriphBurst         = DMA_PBURST_SINGLE;	   /* ��ֹFIFO��λ�������ã���������ͻ�� */
		hdma_rx.Init.Request             = SPI1_RX_DMA_REQUEST;    /* �������� */  
		hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;   /* ���䷽������赽�洢�� */  
		hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;       /* �����ַ������ֹ */   
		hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;        /* �洢����ַ����ʹ�� */   
		hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;    /* �������ݴ���λ��ѡ���ֽڣ���8bit */ 
		hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;    /* �洢�����ݴ���λ��ѡ���ֽڣ���8bit */   
		hdma_rx.Init.Mode                = DMA_NORMAL;             /* ����ģʽ */
		hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;      /* ���ȼ��� */

		 /* ��λDMA */
		if(HAL_DMA_DeInit(&hdma_rx) != HAL_OK)
		{
			Error_Handler(__FILE__, __LINE__);     
		}
		
		 /* ��ʼ��DMA */
		if(HAL_DMA_Init(&hdma_rx) != HAL_OK)
		{
			Error_Handler(__FILE__, __LINE__);     
		}

		/* ����DMA�����SPI */
	   __HAL_LINKDMA(_hspi, hdmarx, hdma_rx);	

		/* ����DMA�����ж� */
		HAL_NVIC_SetPriority(SPI1_DMA_TX_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(SPI1_DMA_TX_IRQn);
		
		/* ����DMA�����ж� */
		HAL_NVIC_SetPriority(SPI1_DMA_RX_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(SPI1_DMA_RX_IRQn);
		
		/* ����SPI�ж� */
		HAL_NVIC_SetPriority(SPI1_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(SPI1_IRQn);
	}
	#endif
	
	#ifdef USE_SPI_INT
		/* ����SPI�ж����ȼ���ʹ���ж� */
		HAL_NVIC_SetPriority(SPI1_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(SPI1_IRQn);
	#endif
}
	
/*
*********************************************************************************************************
*	�� �� ��: bsp_spiTransfer
*	����˵��: �������ݴ���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_spiTransfer(void)
{
	if (g_spiLen > SPI_BUFFER_SIZE)
	{
		return;
	}
	
	/* DMA��ʽ���� */
#ifdef USE_SPI_DMA
	wTransferState = TRANSFER_WAIT;
	
if(HAL_SPI_TransmitReceive_DMA(&hspi, (uint8_t*)g_spiTxBuf, (uint8_t *)g_spiRxBuf, g_spiLen) != HAL_OK)	
{
	Error_Handler(__FILE__, __LINE__);
}
	
	while (wTransferState == TRANSFER_WAIT)
	{
		;
	}
#endif

	/* �жϷ�ʽ���� */	
#ifdef USE_SPI_INT
	wTransferState = TRANSFER_WAIT;

if(HAL_SPI_TransmitReceive_IT(&hspi, (uint8_t*)g_spiTxBuf, (uint8_t *)g_spiRxBuf, g_spiLen) != HAL_OK)	
{
	Error_Handler(__FILE__, __LINE__);
}
	
	while (wTransferState == TRANSFER_WAIT)
	{
		;
	}
#endif

	/* ��ѯ��ʽ���� */	
#ifdef USE_SPI_POLL
	if(HAL_SPI_TransmitReceive(&hspi, (uint8_t*)g_spiTxBuf, (uint8_t *)g_spiRxBuf, g_spiLen, 1000000) != HAL_OK)	
	{
		Error_Handler();
	}	
#endif
}

/*
*********************************************************************************************************
*	�� �� ��: HAL_SPI_TxRxCpltCallback��HAL_SPI_ErrorCallback
*	����˵��: SPI���ݴ�����ɻص��ʹ������ص�
*	��    ��: SPI_HandleTypeDef ����ָ�����
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	wTransferState = TRANSFER_COMPLETE;
}


void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
	wTransferState = TRANSFER_ERROR;
}

/*
*********************************************************************************************************
*	�� �� ��: SPIBusEnter
*	����˵��: ռ��SPI����
*	��    ��: ��
*	�� �� ֵ: 0 ��ʾ��æ  1��ʾæ
*********************************************************************************************************
*/
void SPIBusEnter(void)
{
	g_spi_busy = 1;
}

/*
*********************************************************************************************************
*	�� �� ��: SPIBusExit
*	����˵��: �ͷ�ռ�õ�SPI����
*	��    ��: ��
*	�� �� ֵ: 0 ��ʾ��æ  1��ʾæ
*********************************************************************************************************
*/
void SPIBusExit(void)
{
	g_spi_busy = 0;
}

/*
*********************************************************************************************************
*	�� �� ��: SPIBusBusy
*	����˵��: �ж�SPI����æ�������Ǽ������SPIоƬ��Ƭѡ�ź��Ƿ�Ϊ1
*	��    ��: ��
*	�� �� ֵ: 0 ��ʾ��æ  1��ʾæ
*********************************************************************************************************
*/
uint8_t SPIBusBusy(void)
{
	return g_spi_busy;
}

/*
*********************************************************************************************************
*	�� �� ��: SPI1_IRQHandler��SPI1_DMA_RX_IRQHandler��SPI1_DMA_TX_IRQHandler
*	����˵��: �жϷ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
#ifdef USE_SPI_INT
	void SPI1_IRQHandler(void)
	{
		HAL_SPI_IRQHandler(&hspi);
	}	
#endif

#ifdef USE_SPI_DMA
	void SPI1_DMA_RX_IRQHandler(void)
	{
		HAL_DMA_IRQHandler(hspi.hdmarx);
	}

	void SPI1_DMA_TX_IRQHandler(void)
	{
		HAL_DMA_IRQHandler(hspi.hdmatx);
	}
	
	void SPI1_IRQHandler(void)
	{
		HAL_SPI_IRQHandler(&hspi);
	}	
#endif


