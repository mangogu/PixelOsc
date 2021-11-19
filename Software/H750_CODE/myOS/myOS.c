#include "CONF.h"

/* isDown = 0:δ�ػ� isDown = 1:�ѹػ� */
uint8_t isDown = 0;

void myOs_DevInit(void)
{
	/* �򿪵�Դ */
	GPIO_DevInit();
	
	/* ������Ļ */
	Lcd_Init();
	
	/* ��ʼ��ϵͳ���� */
	Systick_Init();
	
	/* ��ʼ���ⲿFLASH */
	CONFIG_Init();
	
	/* ��ʼ������ */
	MX_USART2_UART_Init();
	
	/* ��ʼ��FATFS */
	MX_FATFS_Init();
	
	/* ��ʼ��USBHOST */
  MX_USB_HOST_Init();
	
	/* ��ʼ��ģ�ⲿ�� */
	analog_init();
	
	//DemoSpiFlash();
	
	test01();
	
	while(1)
	{
		/* ���ػ� */
		if(isDown)
		{
			/* ��ʾ�ػ���ʾ */
			drawShutDownMsg(1);
			/* �ȴ� */
			while(1);
		}
		
		/* �����Ҫ������ */
		if(rxStatus&0x8000)
		{
			cmdProcess();
		}
	}
	
	
}

/* ��ʱ�жϺ��� */
void myOS_1ms_Func(void)
{
	
}

void myOS_10ms_Func(void)
{
	
}

void myOS_100ms_Func(void)
{
	/* ���ػ� */
	shutDownPower();
}

/* ���ػ� */
void shutDownPower(void)
{
	static uint8_t clickCount = 0;
	/* everRelease = 0:����δ�ͷ� everRelease = 1:�����ͷŹ� */
	static uint8_t everRelease = 0;
	/* ��ȡϵͳ����ʱ�� */
	int32_t runTime = Systick_GetRunTime();
	
	/* ���Ѿ��ػ��򿪻�����OFF_WAIT���򲻽����ж� */
	if(isDown == 1 || runTime <= OFF_WAIT * 1000)
	{
		return;
	}
	
	/* ���onoff�������� �� onoff�������ͷŹ� */
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == GPIO_PIN_SET && everRelease == 1)
	{
		/* ���� */
		clickCount ++;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == GPIO_PIN_RESET && everRelease == 0)
	{
		everRelease = 1;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == GPIO_PIN_RESET && everRelease == 1)
	{
		clickCount = 0;
	}
	
	if(clickCount >= OFF_TIME*10)
	{
		/* �رյ�Դ -> ����IO : PC4 Ϊ�������룬����̬ */
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		GPIO_InitStruct.Pin = GPIO_PIN_4;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		/* �ػ� */
		isDown = 1;
	}
}


