#ifndef TIM_H
#define TIM_H

//包含
#include "stm32h7xx_hal.h"
#include "main.h"

//宏定义
#define DEFAULT_BRIGHT 	180
#define HIGHEST_BRIGHT 	255
#define HIGH_BRIGHT			200
#define LOW_BRIGHT			150

//函数声明
void TIM_LcdBright_Init(uint8_t val);
void TIM_LcdBright_Config(uint8_t val);
void TIM_Buzzer_Init(uint16_t hz);
void TIM_Buzzer_Run(void);
void TIM_Buzzer_ConfigThenRun(uint16_t hz);
void TIM_Buzzer_Stop(void);
void TIM_Wave_InitThenRun(uint16_t hz);
#endif

