#include "CONF.h"

uint8_t FiveDirKeys[4];

void KEY_Init(void)
{
	/* ��ʼ��ADC */
	MX_ADC_Init();
	
}

void KEY_ScanKeys(void)
{
	uint8_t val;
	/* ��ȡ4��ͨ�� */
	for (int i = 0; i < 5; i++)
	{
		HAL_ADC_Start(&hadc);  
		HAL_ADC_PollForConversion(&hadc, 100);
		val = HAL_ADC_GetValue(&hadc);
		
		/* ��һ������ */
		if(i == 4)
	}
	printf("\n\r");
	HAL_ADC_Stop(&hadc);
}