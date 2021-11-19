#ifndef __USART_H
#define __USART_H

/* 包含头文件 */
#include "CONF.h"

/* HAL库缓存大小 */
#define RX_BUFF_SIZE   		1 		
/* DATA缓存大小 */
#define DATA_BUFF_SIZE  	100

/* 变量声明 */
extern UART_HandleTypeDef huart2;
extern uint16_t rxStatus;
extern uint8_t dataBuffer[DATA_BUFF_SIZE];

/* 函数声明 */
void MX_USART2_UART_Init(void);

#endif

