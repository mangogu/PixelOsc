#include "CTR.h"

void analog_init(void)
{
	/* 选择直流耦合 */
	CHA_couple(CH_COUPLE_DC);
	
	/* 选择校准模式 */
	CHA_calibrate(CH_CALI_NORMAL);
}

void CHA_couple(uint8_t mode)
{
	switch (mode)
	{
		/* 直流耦合 */
		case CH_COUPLE_DC:
			{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
				break;
			}
		/* 交流耦合 */
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
		/* 地：校准模式 */
		case CH_CALI_GND:
			{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
				break;
			}
		/* 正常模式 */
		case CH_CALI_NORMAL:
			{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
				break;
			}
	}
}

