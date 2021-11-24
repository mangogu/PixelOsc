#ifndef __LED_H
#define __LED_H

#include "CONF.h"

void LED_Init(void);
void LED_SwitchOn(void);
void LED_SwitchOFF(void);


#define ON 		1
#define OFF 	0

#define RUN		1
#define STOP 	0

#define LED_RSOFF				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);\
												HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET)

#define LED_RUN			 		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);\
												HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET)
												
#define LED_STOP			 	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);\
												HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET)

#define LED_CHA(S) 			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, S?GPIO_PIN_SET:GPIO_PIN_RESET)
#define LED_CHB(S)			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, S?GPIO_PIN_SET:GPIO_PIN_RESET)
#define LED_MATH(S) 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, S?GPIO_PIN_SET:GPIO_PIN_RESET)
#define LED_TRIG(S) 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, S?GPIO_PIN_SET:GPIO_PIN_RESET)
#define LED_CTR(S) 			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, S?GPIO_PIN_SET:GPIO_PIN_RESET)


#endif

