#ifndef __LTDC_H
#define __LTDC_H

/*Include Files
	����ͷ�ļ�*/
#include "stm32h7xx_hal.h"
#include "main.h"
#include "LCD.h"

/*Func declaration
	��������*/
void MX_LTDC_Init(void);
void LTDC_ConfigColorCHA(uint8_t startBrightness);

#endif

