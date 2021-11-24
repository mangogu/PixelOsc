#include "CONF.h"

/* HAL库中的串口接收缓冲 */
uint8_t rxBuffer[RX_BUFF_SIZE];

/* 接收数据缓冲，最大缓存DATA_BUFF_SIZE个字节 */
uint8_t dataBuffer[DATA_BUFF_SIZE];

/* 接收状态标志 */
uint16_t rxStatus = 0;

/* USART1 初始化结构体 */
UART_HandleTypeDef huart1;

/* printf 重定向 */
int fputc(int ch,FILE *f)
{
    uint8_t temp[1]={ch};
    HAL_UART_Transmit(&huart1,temp,1,100);
		return ch;
}

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
	HAL_UART_Receive_IT(&huart1, (uint8_t*)rxBuffer, RX_BUFF_SIZE);

}

/* USART中断函数 */
void USART1_IRQHandler(void)
{
	/* 处理USART2回调函数等 */
  HAL_UART_IRQHandler(&huart1);
	HAL_UART_Receive_IT(&huart1, (uint8_t*)rxBuffer, RX_BUFF_SIZE);
}
