#ifndef __LTDC_H
#define __LTDC_H

/*Include Files
	包含头文件*/
#include "stm32h7xx_hal.h"
#include "main.h"
#include "LCD.h"

/*Func declaration
	函数声明*/
void MX_LTDC_Init(void);
void LTDC_ConfigColorCHA(uint8_t startBrightness);

#endif

