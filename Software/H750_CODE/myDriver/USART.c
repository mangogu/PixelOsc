#include "CONF.h"

/* HAL库中的串口接收缓冲 */
uint8_t rxBuffer[RX_BUFF_SIZE];

/* 接收数据缓冲，最大缓存DATA_BUFF_SIZE个字节 */
uint8_t dataBuffer[DATA_BUFF_SIZE];

/* 接收状态标志
	接收状态
	bit15，	接收完成标志
	bit14，	接收到0x0d
	bit13~0，	接收到的有效字节数目 */
uint16_t rxStatus = 0;

/* USART2 初始化结构体 */
UART_HandleTypeDef huart2;

/* printf 重定向 */
	int fputc(int ch,FILE *f)
	{
			uint8_t temp[1]={ch};
			HAL_UART_Transmit(&huart2,temp,1,100);
			return ch;
}

/* USART2初始化 */
void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
	
	HAL_UART_Receive_IT(&huart2, (uint8_t*)rxBuffer, RX_BUFF_SIZE);
}

/* USART2中断函数 */
void USART2_IRQHandler(void)
{
	/* 处理USART2回调函数等 */
  HAL_UART_IRQHandler(&huart2);

	/* 如果接收完成，暂时关闭接收，如果未接收完，则继续接收 */
	if(!(rxStatus & 0x80))
	{
		HAL_UART_Receive_IT(&huart2, (uint8_t*)rxBuffer, RX_BUFF_SIZE);
	}
}

/* USART2回调函数 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/* USART2接收 */
	if(huart->Instance==USART2)
	{
		/* 如果接收未完成 */
		if((rxStatus&0x8000)==0)
		{
			/* 接收到了0x0d */
			if(rxStatus&0x4000)
			{
				/* 接收错误,重新开始 */
				if(rxBuffer[0]!=0x0a)
				{
					rxStatus=0;
				}
				/* 接收完成了 */
				else
				{
					rxStatus|=0x8000;
				}
			}
			/* 还没收到0X0D */
			else
			{	
				if(rxBuffer[0]==0x0d)rxStatus|=0x4000;
				else
				{
					dataBuffer[rxStatus&0X3FFF]=rxBuffer[0];
					rxStatus++;
					/* 接收数据错误,重新开始接收 */
					if(rxStatus>(DATA_BUFF_SIZE-1))rxStatus=0;
				}		 
			}
		}
	}
}


