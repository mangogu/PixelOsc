#include "SPI.h"

/* 定义变量 */
static SPI_HandleTypeDef hspi = {0};
static DMA_HandleTypeDef hdma_tx;
static DMA_HandleTypeDef hdma_rx;
static uint32_t s_BaudRatePrescaler;
static uint32_t s_CLKPhase;
static uint32_t s_CLKPolarity;
uint32_t g_spiLen;	
uint8_t  g_spi_busy; /* SPI忙状态，0表示空闲，1表示忙 */
__IO uint32_t wTransferState = TRANSFER_WAIT;


/* 查询模式 */
#if defined (USE_SPI_POLL)

uint8_t g_spiTxBuf[SPI_BUFFER_SIZE];  
uint8_t g_spiRxBuf[SPI_BUFFER_SIZE];

/* 中断模式 */
#elif defined (USE_SPI_INT)

uint8_t g_spiTxBuf[SPI_BUFFER_SIZE];   
uint8_t g_spiRxBuf[SPI_BUFFER_SIZE];

/* DMA模式使用的SRAM4 */
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
*	函 数 名: SPI_BusInit
*	功能说明: 配置SPI总线。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void SPI_BusInit(void)
{	
	/* 将SPI置为空闲 */
	/* SPI忙状态，0表示空闲，1表示忙 */
	g_spi_busy = 0;
	
	SPI_Init(SPI_BAUDRATEPRESCALER_8, SPI_PHASE_1EDGE, SPI_POLARITY_LOW);
}

/*
*********************************************************************************************************
*	函 数 名: SPI_Init
*	功能说明: 配置SPI总线参数，时钟分频，时钟相位和时钟极性。
*	形    参: _BaudRatePrescaler  SPI总线时钟分频设置，支持的参数如下：
*                                 SPI_BAUDRATEPRESCALER_2    2分频
*                                 SPI_BAUDRATEPRESCALER_4    4分频
*                                 SPI_BAUDRATEPRESCALER_8    8分频
*                                 SPI_BAUDRATEPRESCALER_16   16分频
*                                 SPI_BAUDRATEPRESCALER_32   32分频
*                                 SPI_BAUDRATEPRESCALER_64   64分频
*                                 SPI_BAUDRATEPRESCALER_128  128分频
*                                 SPI_BAUDRATEPRESCALER_256  256分频
*                                                        
*             _CLKPhase           时钟相位，支持的参数如下：
*                                 SPI_PHASE_1EDGE     SCK引脚的第1个边沿捕获传输的第1个数据
*                                 SPI_PHASE_2EDGE     SCK引脚的第2个边沿捕获传输的第1个数据
*                                 
*             _CLKPolarity        时钟极性，支持的参数如下：
*                                 SPI_POLARITY_LOW    SCK引脚在空闲状态处于低电平
*                                 SPI_POLARITY_HIGH   SCK引脚在空闲状态处于高电平
*
*	返 回 值: 无
*********************************************************************************************************
*/
void SPI_Init(uint32_t _BaudRatePrescaler, uint32_t _CLKPhase, uint32_t _CLKPolarity)
{
	/* 提高执行效率，只有在SPI硬件参数发生变化时，才执行HAL_Init */
	if (s_BaudRatePrescaler == _BaudRatePrescaler && s_CLKPhase == _CLKPhase && s_CLKPolarity == _CLKPolarity)
	{		
		return;
	}

	s_BaudRatePrescaler = _BaudRatePrescaler;	
	s_CLKPhase = _CLKPhase;
	s_CLKPolarity = _CLKPolarity;
	
	/* 设置SPI参数 */
	hspi.Instance               = SPI1;                   /* 例化SPI */
	hspi.Init.BaudRatePrescaler = _BaudRatePrescaler;     /* 设置波特率 */
	hspi.Init.Direction         = SPI_DIRECTION_2LINES;   /* 全双工 */
	hspi.Init.CLKPhase          = _CLKPhase;              /* 配置时钟相位 */
	hspi.Init.CLKPolarity       = _CLKPolarity;           /* 配置时钟极性 */
	hspi.Init.DataSize          = SPI_DATASIZE_8BIT;      /* 设置数据宽度 */
	hspi.Init.FirstBit          = SPI_FIRSTBIT_MSB;       /* 数据传输先传高位 */
	hspi.Init.TIMode            = SPI_TIMODE_DISABLE;     /* 禁止TI模式  */
	hspi.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE; /* 禁止CRC */
	hspi.Init.CRCPolynomial     = 7;                       /* 禁止CRC后，此位无效 */
	hspi.Init.CRCLength         = SPI_CRC_LENGTH_8BIT;     /* 禁止CRC后，此位无效 */
	hspi.Init.NSS               = SPI_NSS_SOFT;               /* 使用软件方式管理片选引脚 */
	hspi.Init.FifoThreshold     = SPI_FIFO_THRESHOLD_01DATA;  /* 设置FIFO大小是一个数据项 */
	hspi.Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;      /* 禁止脉冲输出 */
	hspi.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE; /* 禁止SPI后，SPI相关引脚保持当前状态 */  
	hspi.Init.Mode 			 	= SPI_MODE_MASTER;            /* SPI工作在主控模式 */

	/* 复位配置 */
	if (HAL_SPI_DeInit(&hspi) != HAL_OK)
	{
		Error_Handler();
	}	

	/* 初始化配置 */
	if (HAL_SPI_Init(&hspi) != HAL_OK)
	{
		Error_Handler();
	}	
}

/*
*********************************************************************************************************
*	函 数 名: SPI_Init
*	功能说明: 配置SPI总线时钟，GPIO，中断，DMA等
*	形    参: SPI_HandleTypeDef 类型指针变量
*	返 回 值: 无
*********************************************************************************************************
*/
void HAL_SPI_MspInit(SPI_HandleTypeDef *_hspi)
{
	/* 配置 SPI总线GPIO : SCK MOSI MISO */
	{
		GPIO_InitTypeDef  GPIO_InitStruct;
			
		/* 开启GPIO时钟 */
		SPI1_SCK_CLK_ENABLE();
		SPI1_MISO_CLK_ENABLE();
		SPI1_MOSI_CLK_ENABLE();
		/* 开启SPI1时钟 */
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

	/* 配置DMA和NVIC */
	#ifdef USE_SPI_DMA
	{
		/* 使能DMA时钟 */
		DMAx_CLK_ENABLE();      

		/* SPI DMA发送配置 */		
		hdma_tx.Instance                 = SPI1_TX_DMA_STREAM;      /* 例化使用的DMA数据流 */
		hdma_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;    /* 禁止FIFO*/
		hdma_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL; /* 禁止FIFO此位不起作用，用于设置阀值 */
		hdma_tx.Init.MemBurst            = DMA_MBURST_SINGLE;	    /* 禁止FIFO此位不起作用，用于存储器突发 */
		hdma_tx.Init.PeriphBurst         = DMA_PBURST_SINGLE;	    /* 禁止FIFO此位不起作用，用于外设突发 */
		hdma_tx.Init.Request             = SPI1_TX_DMA_REQUEST;     /* 请求类型 */  
		hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;    /* 传输方向是从存储器到外设 */  
		hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;        /* 外设地址自增禁止 */ 
		hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;         /* 存储器地址自增使能 */  
		hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;     /* 外设数据传输位宽选择字节，即8bit */ 
		hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;     /* 存储器数据传输位宽选择字节，即8bit */    
		hdma_tx.Init.Mode                = DMA_NORMAL;              /* 正常模式 */
		hdma_tx.Init.Priority            = DMA_PRIORITY_LOW;        /* 优先级低 */

		 /* 复位DMA */
		if(HAL_DMA_DeInit(&hdma_tx) != HAL_OK)
		{
			Error_Handler(__FILE__, __LINE__);     
		}
		
		 /* 初始化DMA */
		if(HAL_DMA_Init(&hdma_tx) != HAL_OK)
		{
			Error_Handler(__FILE__, __LINE__);     
		}

		/* 关联DMA句柄到SPI */
		__HAL_LINKDMA(_hspi, hdmatx, hdma_tx);	

		/* SPI DMA接收配置 */	
		hdma_rx.Instance                 = SPI1_RX_DMA_STREAM;     /* 例化使用的DMA数据流 */
		hdma_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;   /* 禁止FIFO*/
		hdma_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;/* 禁止FIFO此位不起作用，用于设置阀值 */
		hdma_rx.Init.MemBurst            = DMA_MBURST_SINGLE;	   /* 禁止FIFO此位不起作用，用于存储器突发 */
		hdma_rx.Init.PeriphBurst         = DMA_PBURST_SINGLE;	   /* 禁止FIFO此位不起作用，用于外设突发 */
		hdma_rx.Init.Request             = SPI1_RX_DMA_REQUEST;    /* 请求类型 */  
		hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;   /* 传输方向从外设到存储器 */  
		hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;       /* 外设地址自增禁止 */   
		hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;        /* 存储器地址自增使能 */   
		hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;    /* 外设数据传输位宽选择字节，即8bit */ 
		hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;    /* 存储器数据传输位宽选择字节，即8bit */   
		hdma_rx.Init.Mode                = DMA_NORMAL;             /* 正常模式 */
		hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;      /* 优先级低 */

		 /* 复位DMA */
		if(HAL_DMA_DeInit(&hdma_rx) != HAL_OK)
		{
			Error_Handler(__FILE__, __LINE__);     
		}
		
		 /* 初始化DMA */
		if(HAL_DMA_Init(&hdma_rx) != HAL_OK)
		{
			Error_Handler(__FILE__, __LINE__);     
		}

		/* 关联DMA句柄到SPI */
	   __HAL_LINKDMA(_hspi, hdmarx, hdma_rx);	

		/* 配置DMA发送中断 */
		HAL_NVIC_SetPriority(SPI1_DMA_TX_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(SPI1_DMA_TX_IRQn);
		
		/* 配置DMA接收中断 */
		HAL_NVIC_SetPriority(SPI1_DMA_RX_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(SPI1_DMA_RX_IRQn);
		
		/* 配置SPI中断 */
		HAL_NVIC_SetPriority(SPI1_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(SPI1_IRQn);
	}
	#endif
	
	#ifdef USE_SPI_INT
		/* 配置SPI中断优先级并使能中断 */
		HAL_NVIC_SetPriority(SPI1_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(SPI1_IRQn);
	#endif
}
	
/*
*********************************************************************************************************
*	函 数 名: bsp_spiTransfer
*	功能说明: 启动数据传输
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_spiTransfer(void)
{
	if (g_spiLen > SPI_BUFFER_SIZE)
	{
		return;
	}
	
	/* DMA方式传输 */
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

	/* 中断方式传输 */	
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

	/* 查询方式传输 */	
#ifdef USE_SPI_POLL
	if(HAL_SPI_TransmitReceive(&hspi, (uint8_t*)g_spiTxBuf, (uint8_t *)g_spiRxBuf, g_spiLen, 1000000) != HAL_OK)	
	{
		Error_Handler();
	}	
#endif
}

/*
*********************************************************************************************************
*	函 数 名: HAL_SPI_TxRxCpltCallback，HAL_SPI_ErrorCallback
*	功能说明: SPI数据传输完成回调和传输错误回调
*	形    参: SPI_HandleTypeDef 类型指针变量
*	返 回 值: 无
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
*	函 数 名: SPIBusEnter
*	功能说明: 占用SPI总线
*	形    参: 无
*	返 回 值: 0 表示不忙  1表示忙
*********************************************************************************************************
*/
void SPIBusEnter(void)
{
	g_spi_busy = 1;
}

/*
*********************************************************************************************************
*	函 数 名: SPIBusExit
*	功能说明: 释放占用的SPI总线
*	形    参: 无
*	返 回 值: 0 表示不忙  1表示忙
*********************************************************************************************************
*/
void SPIBusExit(void)
{
	g_spi_busy = 0;
}

/*
*********************************************************************************************************
*	函 数 名: SPIBusBusy
*	功能说明: 判断SPI总线忙，方法是检测其他SPI芯片的片选信号是否为1
*	形    参: 无
*	返 回 值: 0 表示不忙  1表示忙
*********************************************************************************************************
*/
uint8_t SPIBusBusy(void)
{
	return g_spi_busy;
}

/*
*********************************************************************************************************
*	函 数 名: SPI1_IRQHandler，SPI1_DMA_RX_IRQHandler，SPI1_DMA_TX_IRQHandler
*	功能说明: 中断服务程序
*	形    参: 无
*	返 回 值: 无
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


