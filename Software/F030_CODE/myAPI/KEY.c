#include "CONF.h"

uint8_t FiveDirKeys[4];

void KEY_Init(void)
{
	/* 初始化ADC */
	MX_ADC_Init();
	
}

void KEY_ScanKeys(void)
{
	uint8_t val;
	/* 读取4个通道 */
	for (int i = 0; i < 5; i++)
	{
		HAL_ADC_Start(&hadc);  
		HAL_ADC_PollForConversion(&hadc, 100);
		val = HAL_ADC_GetValue(&hadc);
		
		/* 第一个按键 */
		if(i == 4)
	}
	printf("\n\r");
	HAL_ADC_Stop(&hadc);
}