#include "CONF.h"

uint8_t FiveDirKeys[4];

void KEY_Init(void)
{
	/* ��ʼ��ADC */
	MX_ADC_Init();
	
}

void KEY_ScanKeys(void)
{
	float val;
	/* ��ȡ4��ͨ�� */
	for (int i = 0; i < 5; i++)
	{
		HAL_ADC_Start(&hadc);  
		HAL_ADC_PollForConversion(&hadc, 100);
		val = (float)HAL_ADC_GetValue(&hadc)/4096*3.3;
		
		/* ��һ������ */
		if(i == 3)
		{
			if(val >= KEY_THRESHOLD_1L && val < KEY_THRESHOLD_1H)
			{
				printf("��\n\r");
			}
			else if(val >= KEY_THRESHOLD_2L && val < KEY_THRESHOLD_2H)
			{
				printf("��\n\r");
			}
			else if(val >= KEY_THRESHOLD_3L && val < KEY_THRESHOLD_3H)
			{
				printf("��\n\r");
			}
			else if(val >= KEY_THRESHOLD_4L && val < KEY_THRESHOLD_4H)
			{
				printf("��\n\r");
			}
			else if(val >= KEY_THRESHOLD_5L && val < KEY_THRESHOLD_5H)
			{
				printf("��\n\r");
			}
			else if(val >= KEY_THRESHOLD_6L && val < KEY_THRESHOLD_6H)
			{
				printf("����\n\r");
			}
			printf("%2.1f\n\r",val);
		}
	}
	
	//HAL_ADC_Stop(&hadc);
}

