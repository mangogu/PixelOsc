#include "CONF.h"

void LED_Init(void)
{
	/* 选通LED */
	LED_SwitchOn();
	/* 关闭所有LED */
	LED_RSOFF;
	LED_CHA(ON);
	LED_CHB(ON);
	LED_MATH(OFF);
	LED_TRIG(OFF);
	LED_CTR(OFF);
	/* 关闭选通LED */
	LED_SwitchOFF();
}

void LED_SwitchOn(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/* 选通通道1 */
	SWITCH_CS(1);

	/* LED端口设置为输出 */
  /* 配置GPIO为输出: PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/* 配置GPIO为输出: PB3 PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void LED_SwitchOFF(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* 设置锁存器为透明模式 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
	/* 等待信号传输 */
	delayus(1);
	/* 设置锁存器为锁存模式 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	
	/* 恢复LED端口为输入 */
  /* 配置GPIO为输入: PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/* 配置GPIO为输入: PB3 PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


