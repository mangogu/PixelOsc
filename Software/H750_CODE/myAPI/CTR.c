#include "CTR.h"

void analog_init(void)
{
	/* ѡ��ֱ����� */
	CHA_couple(CH_COUPLE_DC);
	
	/* ѡ��У׼ģʽ */
	CHA_calibrate(CH_CALI_NORMAL);
}

void CHA_couple(uint8_t mode)
{
	switch (mode)
	{
		/* ֱ����� */
		case CH_COUPLE_DC:
			{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
				break;
			}
		/* ������� */
		case CH_COUPLE_AC:
			{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
				break;
			}	
	}
}

void CHA_calibrate(uint8_t mode)
{
	switch (mode)
	{
		/* �أ�У׼ģʽ */
		case CH_CALI_GND:
			{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
				break;
			}
		/* ����ģʽ */
		case CH_CALI_NORMAL:
			{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
				break;
			}
	}
}

