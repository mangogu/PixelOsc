#include "CONF.h"

/* ���������ṹ�� */
struct swtichSturctDef switchStruct[] = 
{
	/* CHA */
	{.GPIO = GPIOA, .GPIO_Pin = GPIO_PIN_12, .record = 0, .record_times = 0, .abstractStatus = RELEASE, .StatusChanged = UNCHANGED,
	 .clickCMD = "button -c cha", .pressCMD = NULL},
	/* CHB */
	{.GPIO = GPIOA, .GPIO_Pin = GPIO_PIN_15, .record = 0, .record_times = 0, .abstractStatus = RELEASE, .StatusChanged = UNCHANGED,
	 .clickCMD = "button -c chb", .pressCMD = NULL},
	/* MATH */
	{.GPIO = GPIOA, .GPIO_Pin = GPIO_PIN_11, .record = 0, .record_times = 0, .abstractStatus = RELEASE, .StatusChanged = UNCHANGED,
	 .clickCMD = "button -c math", .pressCMD = NULL},
	/* TRIGGER */
	{.GPIO = GPIOB, .GPIO_Pin = GPIO_PIN_1, .record = 0, .record_times = 0, .abstractStatus = RELEASE, .StatusChanged = UNCHANGED,
	 .clickCMD = "button -c trig", .pressCMD = NULL},
	/* CONTROL */
	{.GPIO = GPIOB, .GPIO_Pin = GPIO_PIN_0, .record = 0, .record_times = 0, .abstractStatus = RELEASE, .StatusChanged = UNCHANGED,
	 .clickCMD = "button -c ctr", .pressCMD = NULL},
	/* MENU */
	{.GPIO = GPIOA, .GPIO_Pin = GPIO_PIN_7, .record = 0, .record_times = 0, .abstractStatus = RELEASE, .StatusChanged = UNCHANGED,
	 .clickCMD = "button -c menu", .pressCMD = NULL},
	/* AUTO */
	{.GPIO = GPIOA, .GPIO_Pin = GPIO_PIN_4, .record = 0, .record_times = 0, .abstractStatus = RELEASE, .StatusChanged = UNCHANGED,
	 .clickCMD = "button -c auto", .pressCMD = NULL},
	/* RUNSTOP */
	{.GPIO = GPIOA, .GPIO_Pin = GPIO_PIN_5, .record = 0, .record_times = 0, .abstractStatus = RELEASE, .StatusChanged = UNCHANGED,
	 .clickCMD = "button -c rs", .pressCMD = NULL},
};

/* ���򰴼��ṹ�� */
struct swtich5DSturctDef switch5DStruct[] = 
{
	/* CHA 5D */
	{.GPIO = GPIOA, .GPIO_Pin = GPIO_PIN_11, .upRecord = 0, .downRecord = 0, .leftRecord = 0, .rightRecord = 0, .middleRecord = 0,
	 .upRecord_times = 0, .downRecord_times = 0, .leftRecord_times = 0, .rightRecord_times = 0, .middleRecord_times = 0,
	 .upAbstractStatus = RELEASE, .downAbstractStatus = RELEASE, .leftAbstractStatus = RELEASE, .rightAbstractStatus = RELEASE, .middleAbstractStatus = RELEASE,
	 .upStatusChanged = UNCHANGED, .downStatusChanged = UNCHANGED, .leftStatusChanged = UNCHANGED, .rightStatusChanged = UNCHANGED, .middleStatusChanged = UNCHANGED,
	 .upClickCMD = "cha -m up",
	 .downClickCMD = "cha -m down",
	 .leftClickCMD = "cha -m left",
	 .rightClickCMD = "cha -m right",
	 .middleClickCMD = "cha -m middle",
		
	 .upPressCMD = "cha -m up",
	 .downPressCMD = "cha -m down",
	 .leftPressCMD = "cha -m left",
	 .rightPressCMD = "cha -m right",
	 .middlePressCMD = "cha -m middle"},
	
	/* MATH 5D */
	{.GPIO = GPIOB, .GPIO_Pin = GPIO_PIN_1, .upRecord = 0, .downRecord = 0, .leftRecord = 0, .rightRecord = 0, .middleRecord = 0,
	 .upRecord_times = 0, .downRecord_times = 0, .leftRecord_times = 0, .rightRecord_times = 0, .middleRecord_times = 0,
	 .upAbstractStatus = RELEASE, .downAbstractStatus = RELEASE, .leftAbstractStatus = RELEASE, .rightAbstractStatus = RELEASE, .middleAbstractStatus = RELEASE,
	 .upStatusChanged = UNCHANGED, .downStatusChanged = UNCHANGED, .leftStatusChanged = UNCHANGED, .rightStatusChanged = UNCHANGED, .middleStatusChanged = UNCHANGED,
	 .upClickCMD = "cha -m up",
	 .downClickCMD = "cha -m down",
	 .leftClickCMD = "cha -m left",
	 .rightClickCMD = "cha -m right",
	 .middleClickCMD = "cha -m middle",
		
	 .upPressCMD = "cha -m up",
	 .downPressCMD = "cha -m down",
	 .leftPressCMD = "cha -m left",
	 .rightPressCMD = "cha -m right",
	 .middlePressCMD = "cha -m middle"},
	
	/* TRIGGER 5D */
	{.GPIO = GPIOB, .GPIO_Pin = GPIO_PIN_0, .upRecord = 0, .downRecord = 0, .leftRecord = 0, .rightRecord = 0, .middleRecord = 0,
	 .upRecord_times = 0, .downRecord_times = 0, .leftRecord_times = 0, .rightRecord_times = 0, .middleRecord_times = 0,
	 .upAbstractStatus = RELEASE, .downAbstractStatus = RELEASE, .leftAbstractStatus = RELEASE, .rightAbstractStatus = RELEASE, .middleAbstractStatus = RELEASE,
	 .upStatusChanged = UNCHANGED, .downStatusChanged = UNCHANGED, .leftStatusChanged = UNCHANGED, .rightStatusChanged = UNCHANGED, .middleStatusChanged = UNCHANGED,
	 .upClickCMD = "cha -m up",
	 .downClickCMD = "cha -m down",
	 .leftClickCMD = "cha -m left",
	 .rightClickCMD = "cha -m right",
	 .middleClickCMD = "cha -m middle",
		
	 .upPressCMD = "cha -m up",
	 .downPressCMD = "cha -m down",
	 .leftPressCMD = "cha -m left",
	 .rightPressCMD = "cha -m right",
	 .middlePressCMD = "cha -m middle"},
	
	 /* CONTROL 5D */
	{.GPIO = GPIOA, .GPIO_Pin = GPIO_PIN_6, .upRecord = 0, .downRecord = 0, .leftRecord = 0, .rightRecord = 0, .middleRecord = 0,
	 .upRecord_times = 0, .downRecord_times = 0, .leftRecord_times = 0, .rightRecord_times = 0, .middleRecord_times = 0,
	 .upAbstractStatus = RELEASE, .downAbstractStatus = RELEASE, .leftAbstractStatus = RELEASE, .rightAbstractStatus = RELEASE, .middleAbstractStatus = RELEASE,
	 .upStatusChanged = UNCHANGED, .downStatusChanged = UNCHANGED, .leftStatusChanged = UNCHANGED, .rightStatusChanged = UNCHANGED, .middleStatusChanged = UNCHANGED,
	 .upClickCMD = "menu -b b",
	 .downClickCMD = "menu -b f",
	 .leftClickCMD = "menu -o b",
	 .rightClickCMD = "menu -o f",
	 .middleClickCMD = "cha -m middle",
		
	 .upPressCMD = "menu -b b",
	 .downPressCMD = "menu -b f",
	 .leftPressCMD = "cha -m left",
	 .rightPressCMD = "cha -m right",
	 .middlePressCMD = "cha -m middle"}
};

/* ͨ��ѡ�� */
void SWITCH_CS(uint8_t cs)
{
	if(cs == 1)
	{
		/* ѡͨͨ��1 */
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	}
	else if(cs == 2)
	{
		/* ѡͨͨ��2 */
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
	}
}

/* ɨ�谴�� */
void SWITCH_Scan(void)
{
	uint8_t i;
	
	/* ѡͨͨ��1 */
	SWITCH_CS(1);
	
	for(i = 0; i < 5; i++)
	{
		switchStruct[i].record <<= 1;
		switchStruct[i].record |= HAL_GPIO_ReadPin(switchStruct[i].GPIO, switchStruct[i].GPIO_Pin);
	}	
	
	/* ѡͨͨ��2 */
	SWITCH_CS(2);
	
	for(i = 5; i < 8; i++)
	{
		switchStruct[i].record <<= 1;
		switchStruct[i].record |= HAL_GPIO_ReadPin(switchStruct[i].GPIO, switchStruct[i].GPIO_Pin);
	}	
	
	/* ʹ�����򰴼�ɨ��ģʽ */
	SWITCH_5DSwitchOn();
	
	/* ɨ���� */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	for(i = 0; i < (sizeof(switch5DStruct)/sizeof(struct swtich5DSturctDef)); i++)
	{
		switch5DStruct[i].upRecord <<= 1;
		switch5DStruct[i].upRecord |= HAL_GPIO_ReadPin(switch5DStruct[i].GPIO, switch5DStruct[i].GPIO_Pin);
	}
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
	
	/* ɨ���� */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	for(i = 0; i < (sizeof(switch5DStruct)/sizeof(struct swtich5DSturctDef)); i++)
	{
		switch5DStruct[i].downRecord <<= 1;
		switch5DStruct[i].downRecord |= HAL_GPIO_ReadPin(switch5DStruct[i].GPIO, switch5DStruct[i].GPIO_Pin);
	}
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	
	/* ɨ���� */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	for(i = 0; i < (sizeof(switch5DStruct)/sizeof(struct swtich5DSturctDef)); i++)
	{
		switch5DStruct[i].leftRecord <<= 1;
		switch5DStruct[i].leftRecord |= HAL_GPIO_ReadPin(switch5DStruct[i].GPIO, switch5DStruct[i].GPIO_Pin);
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	
	/* ɨ���� */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
	for(i = 0; i < (sizeof(switch5DStruct)/sizeof(struct swtich5DSturctDef)); i++)
	{
		switch5DStruct[i].rightRecord <<= 1;
		switch5DStruct[i].rightRecord |= HAL_GPIO_ReadPin(switch5DStruct[i].GPIO, switch5DStruct[i].GPIO_Pin);
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
	
	/* ɨ���� */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	for(i = 0; i < (sizeof(switch5DStruct)/sizeof(struct swtich5DSturctDef)); i++)
	{
		switch5DStruct[i].middleRecord <<= 1;
		switch5DStruct[i].middleRecord |= HAL_GPIO_ReadPin(switch5DStruct[i].GPIO, switch5DStruct[i].GPIO_Pin);
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);

	/* ʧ�����򰴼�ɨ��ģʽ */
  SWITCH_5DSwitchOFF();
}

/* ��ⰴ��״̬ */
void SWITCH_CheckStatus(void)
{
	uint8_t i;
	/* ɨ�赥������״̬ */
	for(i = 0; i < (sizeof(switchStruct)/sizeof(struct swtichSturctDef)); i++)
	{
		/* ������� */
		if(switchStruct[i].record == 0)
		{
			/* ��һ�ΰ��� */
			if(switchStruct[i].abstractStatus == RELEASE)
			{
				switchStruct[i].abstractStatus = CLICK;
				switchStruct[i].StatusChanged = CHANGED;
			}
			/* ����Ƿ�Ϊ���� */
			else if(switchStruct[i].abstractStatus == CLICK)
			{
				switchStruct[i].record_times++;
				if(switchStruct[i].record_times == 100*PRESS_TIME)
				{
					switchStruct[i].record_times = 0;
					switchStruct[i].abstractStatus = PRESS;
					switchStruct[i].StatusChanged = CHANGED;
				}
			}
			else if(switchStruct[i].abstractStatus == PRESS)
			{
				switchStruct[i].record_times++;
				if(switchStruct[i].record_times == 100*PRESS_TIME_S)
				{
					switchStruct[i].record_times = 0;
					switchStruct[i].StatusChanged = CHANGED;
				}
			}
		}
		/* �ɿ� */
		else
		{
			if(switchStruct[i].abstractStatus != RELEASE)
			{
				switchStruct[i].record_times = 0;
				switchStruct[i].abstractStatus = RELEASE;
				switchStruct[i].StatusChanged = CHANGED;
			}
		}
		/* ����ָ�� */
		if(switchStruct[i].StatusChanged == CHANGED)
		{
			if(switchStruct[i].abstractStatus ==  CLICK && switchStruct[i].clickCMD != NULL)
			{
				printf("%s\r\n",switchStruct[i].clickCMD);
			}
			else if(switchStruct[i].abstractStatus ==  PRESS && switchStruct[i].pressCMD != NULL)
			{
				printf("%s\r\n",switchStruct[i].pressCMD);
			}
			switchStruct[i].StatusChanged = UNCHANGED;
		}
	}	
	
	/* ɨ�����򰴼�״̬ */
	for(i = 0; i < (sizeof(switch5DStruct)/sizeof(struct swtich5DSturctDef)); i++)
	{
		/* ɨ���� */
		/* ������� */
		if(switch5DStruct[i].upRecord == 0)
		{
			/* ��һ�ΰ��� */
			if(switch5DStruct[i].upAbstractStatus == RELEASE)
			{
				switch5DStruct[i].upAbstractStatus = CLICK;
				switch5DStruct[i].upStatusChanged = CHANGED;
			}
			/* ����Ƿ�Ϊ���� */
			else if(switch5DStruct[i].upAbstractStatus == CLICK)
			{
				switch5DStruct[i].upRecord_times++;
				if(switch5DStruct[i].upRecord_times == 100*PRESS_TIME)
				{
					switch5DStruct[i].upRecord_times = 0;
					switch5DStruct[i].upAbstractStatus = PRESS;
					switch5DStruct[i].upStatusChanged = CHANGED;
				}
			}
			else if(switch5DStruct[i].upAbstractStatus == PRESS)
			{
				switch5DStruct[i].upRecord_times++;
				if(switch5DStruct[i].upRecord_times == 100*PRESS_TIME_S)
				{
					switch5DStruct[i].upRecord_times = 0;
					switch5DStruct[i].upStatusChanged = CHANGED;
				}
			}
		}
		/* �ɿ� */
		else
		{
			if(switch5DStruct[i].upAbstractStatus != RELEASE)
			{
				switch5DStruct[i].upRecord_times = 0;
				switch5DStruct[i].upAbstractStatus = RELEASE;
				switch5DStruct[i].upStatusChanged = CHANGED;
			}
		}
		/* ����ָ�� */
		if(switch5DStruct[i].upStatusChanged == CHANGED)
		{
			if(switch5DStruct[i].upAbstractStatus ==  CLICK && switch5DStruct[i].upClickCMD != NULL)
			{
				printf("%s\r\n",switch5DStruct[i].upClickCMD);
			}
			else if(switch5DStruct[i].upAbstractStatus ==  PRESS && switch5DStruct[i].upPressCMD != NULL)
			{
				printf("%s\r\n",switch5DStruct[i].upPressCMD);
			}
			switch5DStruct[i].upStatusChanged = UNCHANGED;
		}
		/* ɨ���� */
		/* ������� */
		if(switch5DStruct[i].downRecord == 0)
		{
			/* ��һ�ΰ��� */
			if(switch5DStruct[i].downAbstractStatus == RELEASE)
			{
				switch5DStruct[i].downAbstractStatus = CLICK;
				switch5DStruct[i].downStatusChanged = CHANGED;
			}
			/* ����Ƿ�Ϊ���� */
			else if(switch5DStruct[i].downAbstractStatus == CLICK)
			{
				switch5DStruct[i].downRecord_times++;
				if(switch5DStruct[i].downRecord_times == 100*PRESS_TIME)
				{
					switch5DStruct[i].downRecord_times = 0;
					switch5DStruct[i].downAbstractStatus = PRESS;
					switch5DStruct[i].downStatusChanged = CHANGED;
				}
			}
			else if(switch5DStruct[i].downAbstractStatus == PRESS)
			{
				switch5DStruct[i].downRecord_times++;
				if(switch5DStruct[i].downRecord_times == 100*PRESS_TIME_S)
				{
					switch5DStruct[i].downRecord_times = 0;
					switch5DStruct[i].downStatusChanged = CHANGED;
				}
			}
		}
		/* �ɿ� */
		else
		{
			if(switch5DStruct[i].downAbstractStatus != RELEASE)
			{
				switch5DStruct[i].downRecord_times = 0;
				switch5DStruct[i].downAbstractStatus = RELEASE;
				switch5DStruct[i].downStatusChanged = CHANGED;
			}
		}
		/* ����ָ�� */
		if(switch5DStruct[i].downStatusChanged == CHANGED)
		{
			if(switch5DStruct[i].downAbstractStatus ==  CLICK && switch5DStruct[i].downClickCMD != NULL)
			{
				printf("%s\r\n",switch5DStruct[i].downClickCMD);
			}
			else if(switch5DStruct[i].downAbstractStatus ==  PRESS && switch5DStruct[i].downPressCMD != NULL)
			{
				printf("%s\r\n",switch5DStruct[i].downPressCMD);
			}
			switch5DStruct[i].downStatusChanged = UNCHANGED;
		}
		/* ɨ���� */
		/* ������� */
		if(switch5DStruct[i].leftRecord == 0)
		{
			/* ��һ�ΰ��� */
			if(switch5DStruct[i].leftAbstractStatus == RELEASE)
			{
				switch5DStruct[i].leftAbstractStatus = CLICK;
				switch5DStruct[i].leftStatusChanged = CHANGED;
			}
			/* ����Ƿ�Ϊ���� */
			else if(switch5DStruct[i].leftAbstractStatus == CLICK)
			{
				switch5DStruct[i].leftRecord_times++;
				if(switch5DStruct[i].leftRecord_times == 100*PRESS_TIME)
				{
					switch5DStruct[i].leftRecord_times = 0;
					switch5DStruct[i].leftAbstractStatus = PRESS;
					switch5DStruct[i].leftStatusChanged = CHANGED;
				}
			}
			else if(switch5DStruct[i].leftAbstractStatus == PRESS)
			{
				switch5DStruct[i].leftRecord_times++;
				if(switch5DStruct[i].leftRecord_times == 100*PRESS_TIME_S)
				{
					switch5DStruct[i].leftRecord_times = 0;
					switch5DStruct[i].leftStatusChanged = CHANGED;
				}
			}
		}
		/* �ɿ� */
		else
		{
			if(switch5DStruct[i].leftAbstractStatus != RELEASE)
			{
				switch5DStruct[i].leftRecord_times = 0;
				switch5DStruct[i].leftAbstractStatus = RELEASE;
				switch5DStruct[i].leftStatusChanged = CHANGED;
			}
		}
		/* ����ָ�� */
		if(switch5DStruct[i].leftStatusChanged == CHANGED)
		{
			if(switch5DStruct[i].leftAbstractStatus ==  CLICK && switch5DStruct[i].leftClickCMD != NULL)
			{
				printf("%s\r\n",switch5DStruct[i].leftClickCMD);
			}
			else if(switch5DStruct[i].leftAbstractStatus ==  PRESS && switch5DStruct[i].leftPressCMD != NULL)
			{
				printf("%s\r\n",switch5DStruct[i].leftPressCMD);
			}
			switch5DStruct[i].leftStatusChanged = UNCHANGED;
		}
		/* ɨ���� */
		/* ������� */
		if(switch5DStruct[i].rightRecord == 0)
		{
			/* ��һ�ΰ��� */
			if(switch5DStruct[i].rightAbstractStatus == RELEASE)
			{
				switch5DStruct[i].rightAbstractStatus = CLICK;
				switch5DStruct[i].rightStatusChanged = CHANGED;
			}
			/* ����Ƿ�Ϊ���� */
			else if(switch5DStruct[i].rightAbstractStatus == CLICK)
			{
				switch5DStruct[i].rightRecord_times++;
				if(switch5DStruct[i].rightRecord_times == 100*PRESS_TIME)
				{
					switch5DStruct[i].rightRecord_times = 0;
					switch5DStruct[i].rightAbstractStatus = PRESS;
					switch5DStruct[i].rightStatusChanged = CHANGED;
				}
			}
			else if(switch5DStruct[i].rightAbstractStatus == PRESS)
			{
				switch5DStruct[i].rightRecord_times++;
				if(switch5DStruct[i].rightRecord_times == 100*PRESS_TIME_S)
				{
					switch5DStruct[i].rightRecord_times = 0;
					switch5DStruct[i].rightStatusChanged = CHANGED;
				}
			}
		}
		/* �ɿ� */
		else
		{
			if(switch5DStruct[i].rightAbstractStatus != RELEASE)
			{
				switch5DStruct[i].rightRecord_times = 0;
				switch5DStruct[i].rightAbstractStatus = RELEASE;
				switch5DStruct[i].rightStatusChanged = CHANGED;
			}
		}
		/* ����ָ�� */
		if(switch5DStruct[i].rightStatusChanged == CHANGED)
		{
			if(switch5DStruct[i].rightAbstractStatus ==  CLICK && switch5DStruct[i].rightClickCMD != NULL)
			{
				printf("%s\r\n",switch5DStruct[i].rightClickCMD);
			}
			else if(switch5DStruct[i].rightAbstractStatus ==  PRESS && switch5DStruct[i].rightPressCMD != NULL)
			{
				printf("%s\r\n",switch5DStruct[i].rightPressCMD);
			}
			switch5DStruct[i].rightStatusChanged = UNCHANGED;
		}
		/* ɨ���� */
		/* ������� */
		if(switch5DStruct[i].middleRecord == 0)
		{
			/* ��һ�ΰ��� */
			if(switch5DStruct[i].middleAbstractStatus == RELEASE)
			{
				switch5DStruct[i].middleAbstractStatus = CLICK;
				switch5DStruct[i].middleStatusChanged = CHANGED;
			}
			/* ����Ƿ�Ϊ���� */
			else if(switch5DStruct[i].middleAbstractStatus == CLICK)
			{
				switch5DStruct[i].middleRecord_times++;
				if(switch5DStruct[i].middleRecord_times == 100*PRESS_TIME)
				{
					switch5DStruct[i].middleRecord_times = 0;
					switch5DStruct[i].middleAbstractStatus = PRESS;
					switch5DStruct[i].middleStatusChanged = CHANGED;
				}
			}
			else if(switch5DStruct[i].middleAbstractStatus == PRESS)
			{
				switch5DStruct[i].middleRecord_times++;
				if(switch5DStruct[i].middleRecord_times == 100*PRESS_TIME_S)
				{
					switch5DStruct[i].middleRecord_times = 0;
					switch5DStruct[i].middleStatusChanged = CHANGED;
				}
			}
		}
		/* �ɿ� */
		else
		{
			if(switch5DStruct[i].middleAbstractStatus != RELEASE)
			{
				switch5DStruct[i].middleRecord_times = 0;
				switch5DStruct[i].middleAbstractStatus = RELEASE;
				switch5DStruct[i].middleStatusChanged = CHANGED;
			}
		}
		/* ����ָ�� */
		if(switch5DStruct[i].middleStatusChanged == CHANGED)
		{
			if(switch5DStruct[i].middleAbstractStatus ==  CLICK && switch5DStruct[i].middleClickCMD != NULL)
			{
				printf("%s\r\n",switch5DStruct[i].middleClickCMD);
			}
			else if(switch5DStruct[i].middleAbstractStatus ==  PRESS && switch5DStruct[i].middlePressCMD != NULL)
			{
				printf("%s\r\n",switch5DStruct[i].middlePressCMD);
			}
			switch5DStruct[i].middleStatusChanged = UNCHANGED;
		}
	}	
}

/* ����ɨ�����򰴼�ģʽ */
void SWITCH_5DSwitchOn(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/* ѡͨͨ��2 */
	SWITCH_CS(2);

	/* ���򰴼�����˿�����Ϊ��� */
  /* ����GPIOΪ���: PA12 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/* ����GPIOΪ���: PB3 PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	/* ���򰴼�����˿�����Ϊ�ߵ�ƽ */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12|GPIO_PIN_15, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_SET);
}

/* �ر����򰴼�ɨ��ģʽ */
void SWITCH_5DSwitchOFF(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* ���򰴼�����˿ڻָ�Ϊ���� */
  /* �ָ�GPIOΪ����: PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/* �ָ�GPIOΪ����: PB3 PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


