#ifndef __USART_H
#define __USART_H

/* ����ͷ�ļ� */
#include "CONF.h"

/* HAL�⻺���С */
#define RX_BUFF_SIZE   		1 		
/* DATA�����С */
#define DATA_BUFF_SIZE  	100

/* �������� */
extern UART_HandleTypeDef huart2;
extern uint16_t rxStatus;
extern uint8_t dataBuffer[DATA_BUFF_SIZE];

/* �������� */
void MX_USART2_UART_Init(void);

#endif

