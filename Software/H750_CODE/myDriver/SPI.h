#ifndef __SPI_H
#define __SPI_H

/* 包含头文件 */
#include "stm32h7xx_hal.h"
#include "main.h"

/* 选择DMA，中断或者查询方式 */
//#define USE_SPI_DMA    /* DMA方式  */
//#define USE_SPI_INT    /* 中断方式 */
#define USE_SPI_POLL   /* 查询方式 */


/* 时钟，引脚，DMA，中断等宏定义 */
#define SPI1_CLK_ENABLE()				__HAL_RCC_SPI1_CLK_ENABLE()
#define DMAx_CLK_ENABLE()				__HAL_RCC_DMA2_CLK_ENABLE()

#define SPI1_FORCE_RESET()				__HAL_RCC_SPI1_FORCE_RESET()
#define SPI1_RELEASE_RESET()			__HAL_RCC_SPI1_RELEASE_RESET()

#define SPI1_SCK_CLK_ENABLE()				__HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI1_SCK_GPIO								GPIOB
#define SPI1_SCK_PIN								GPIO_PIN_3
#define SPI1_SCK_AF									GPIO_AF5_SPI1

#define SPI1_MISO_CLK_ENABLE()			__HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI1_MISO_GPIO							GPIOB
#define SPI1_MISO_PIN 							GPIO_PIN_4
#define SPI1_MISO_AF								GPIO_AF5_SPI1

#define SPI1_MOSI_CLK_ENABLE()			__HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI1_MOSI_GPIO							GPIOA
#define SPI1_MOSI_PIN 							GPIO_PIN_7
#define SPI1_MOSI_AF								GPIO_AF5_SPI1

#define SPI1_TX_DMA_STREAM               DMA2_Stream3
#define SPI1_RX_DMA_STREAM               DMA2_Stream2

#define SPI1_TX_DMA_REQUEST              DMA_REQUEST_SPI1_TX
#define SPI1_RX_DMA_REQUEST              DMA_REQUEST_SPI1_RX

#define SPI1_DMA_TX_IRQn                 DMA2_Stream3_IRQn
#define SPI1_DMA_RX_IRQn                 DMA2_Stream2_IRQn

#define SPI1_DMA_TX_IRQHandler           DMA2_Stream3_IRQHandler
#define SPI1_DMA_RX_IRQHandler           DMA2_Stream2_IRQHandler

#define SPI1_IRQn                        SPI1_IRQn
#define SPI1_IRQHandler                  SPI1_IRQHandler

/* 重定义下SPI SCK时钟，方便移植 */
#define SPI_BAUDRATEPRESCALER_100M      SPI_BAUDRATEPRESCALER_2			/* 100M */
#define SPI_BAUDRATEPRESCALER_50M       SPI_BAUDRATEPRESCALER_4			/* 50M */
#define SPI_BAUDRATEPRESCALER_12_5M     SPI_BAUDRATEPRESCALER_8			/* 12.5M */
#define SPI_BAUDRATEPRESCALER_6_25M     SPI_BAUDRATEPRESCALER_16		/* 6.25M */
#define SPI_BAUDRATEPRESCALER_3_125M    SPI_BAUDRATEPRESCALER_32		/* 3.125M */
#define SPI_BAUDRATEPRESCALER_1_5625M   SPI_BAUDRATEPRESCALER_64		/* 1.5625M */
#define SPI_BAUDRATEPRESCALER_781_25K   SPI_BAUDRATEPRESCALER_128		/* 781.25K */
#define SPI_BAUDRATEPRESCALER_390_625K  SPI_BAUDRATEPRESCALER_256		/* 390.625K */

/* 缓存区大小 */
#define	SPI_BUFFER_SIZE		(4 * 1024)


extern uint8_t g_spiTxBuf[SPI_BUFFER_SIZE];
extern uint8_t g_spiRxBuf[SPI_BUFFER_SIZE];
extern uint32_t g_spiLen;
extern uint8_t g_spi_busy;

/* 函数声明 */
void SPI_BusInit(void);
void bsp_spiTransfer(void);
void SPI_Init(uint32_t _BaudRatePrescaler, uint32_t _CLKPhase, uint32_t _CLKPolarity);
void SPIBusEnter(void);
void SPIBusExit(void);
uint8_t SPIBusBusy(void);

enum {
	TRANSFER_WAIT,
	TRANSFER_COMPLETE,
	TRANSFER_ERROR
};

#endif









