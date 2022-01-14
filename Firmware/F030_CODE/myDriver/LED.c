#include "CONF.h"

void LED_Init(void)
{
	/* ѡͨLED */
	LED_SwitchOn();
	/* �ر�����LED */
	LED_RSOFF;
	LED_CHA(ON);
	LED_CHB(ON);
	LED_MATH(OFF);
	LED_TRIG(OFF);
	LED_CTR(OFF);
	/* �ر�ѡͨLED */
	LED_SwitchOFF();
}

void LED_SwitchOn(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/* ѡͨͨ��1 */
	SWITCH_CS(1);

	/* LED�˿�����Ϊ��� */
  /* ����GPIOΪ���: PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/* ����GPIOΪ���: PB3 PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void LED_SwitchOFF(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* ����������Ϊ͸��ģʽ */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
	/* �ȴ��źŴ��� */
	delayus(1);
	/* ����������Ϊ����ģʽ */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	
	/* �ָ�LED�˿�Ϊ���� */
  /* ����GPIOΪ����: PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/* ����GPIOΪ����: PB3 PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


