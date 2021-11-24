#include "CONF.h"

/* HAL���еĴ��ڽ��ջ��� */
uint8_t rxBuffer[RX_BUFF_SIZE];

/* �������ݻ��壬��󻺴�DATA_BUFF_SIZE���ֽ� */
uint8_t dataBuffer[DATA_BUFF_SIZE];

/* ����״̬��־
	����״̬
	bit15��	������ɱ�־
	bit14��	���յ�0x0d
	bit13~0��	���յ�����Ч�ֽ���Ŀ */
uint16_t rxStatus = 0;

/* USART2 ��ʼ���ṹ�� */
UART_HandleTypeDef huart2;

/* printf �ض��� */
	int fputc(int ch,FILE *f)
	{
			uint8_t temp[1]={ch};
			HAL_UART_Transmit(&huart2,temp,1,100);
			return ch;
}

/* USART2��ʼ�� */
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

/* USART2�жϺ��� */
void USART2_IRQHandler(void)
{
	/* ����USART2�ص������� */
  HAL_UART_IRQHandler(&huart2);

	/* ���������ɣ���ʱ�رս��գ����δ�����꣬��������� */
	if(!(rxStatus & 0x80))
	{
		HAL_UART_Receive_IT(&huart2, (uint8_t*)rxBuffer, RX_BUFF_SIZE);
	}
}

/* USART2�ص����� */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/* USART2���� */
	if(huart->Instance==USART2)
	{
		/* �������δ��� */
		if((rxStatus&0x8000)==0)
		{
			/* ���յ���0x0d */
			if(rxStatus&0x4000)
			{
				/* ���մ���,���¿�ʼ */
				if(rxBuffer[0]!=0x0a)
				{
					rxStatus=0;
				}
				/* ��������� */
				else
				{
					rxStatus|=0x8000;
				}
			}
			/* ��û�յ�0X0D */
			else
			{	
				if(rxBuffer[0]==0x0d)rxStatus|=0x4000;
				else
				{
					dataBuffer[rxStatus&0X3FFF]=rxBuffer[0];
					rxStatus++;
					/* �������ݴ���,���¿�ʼ���� */
					if(rxStatus>(DATA_BUFF_SIZE-1))rxStatus=0;
				}		 
			}
		}
	}
}


