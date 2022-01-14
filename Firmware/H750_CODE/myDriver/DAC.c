#include "CONF.h"

void DAC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* 打开IO时钟 */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	
	/* DA选择A0 -> 设置IO : PE8 */
	GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
	
	/* DA选择A1 -> 设置IO : PE9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
	
	/* DA选择A2 -> 设置IO : PE10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
	
	DAC_SelectChip(CHB_VGA_CTR_EN);
	
//	__HAL_RCC_GPIOB_CLK_ENABLE();
//	
//	 GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//	
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7|GPIO_PIN_6, GPIO_PIN_SET);
//	
	/* 初始化I2C */
	I2C_Init();
	
	while(1)
	{
			uint8_t dat[2];
	dat[0] = 0x0F;
	dat[1] = 0xFF;
	
	HAL_I2C_Master_Transmit(&hi2c1, MCP4725_ADDR, dat, 2, 10);
	}
	

}

void DAC_SelectChip(uint8_t id)
{
	/* A */
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, (id&0x01)?GPIO_PIN_SET:GPIO_PIN_RESET);
	/* B */
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, ((id>>1)&0x01)?GPIO_PIN_SET:GPIO_PIN_RESET);
	/* C */
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, ((id>>2)&0x01)?GPIO_PIN_SET:GPIO_PIN_RESET);
}


