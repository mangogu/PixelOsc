#ifndef CONF_H
#define CONF_H

/* 全局常量 */
#define KEY_THRESHOLD_1L		0
#define KEY_THRESHOLD_1H 		0.275
#define KEY_THRESHOLD_2L 		0.275
#define KEY_THRESHOLD_2H 		0.825
#define KEY_THRESHOLD_3L 		0.825
#define KEY_THRESHOLD_3H 		1.375
#define KEY_THRESHOLD_4L 		1.375
#define KEY_THRESHOLD_4H 		1.925
#define KEY_THRESHOLD_5L 		1.925
#define KEY_THRESHOLD_5H		2.75
#define KEY_THRESHOLD_6L 		2.75
#define KEY_THRESHOLD_6H		3.3

/* 包含头文件 */
/* 库头文件 */
#include "stm32f0xx_hal.h"
#include "main.h"
#include "stdio.h"
/* 驱动层头文件 */
#include "ADC.h"
#include "GPIO.h"
#include "USART.h"
#include "SYSTICK.h"
/* 中间层头文件 */

/* 应用层头文件 */
#include "KEY.h"
/* 系统层头文件 */
#include "myOS.h"


#endif
