#include "CONF.h"


void myOs_DevInit(void)
{
	/* �򿪵�Դ */
	GPIO_DevInit();
	
	/* ��ʼ������ */
	MX_USART2_UART_Init();
	
	/* ��ʼ��FATFS */
	MX_FATFS_Init();
	
	/* ��ʼ��USBHOST */
  MX_USB_HOST_Init();
	
	/* ��ʼ��У׼�����ź� */
	TIM_Wave_InitThenRun(1000);
	
	CONFIG_Init();
	
	/* ��ʼ��ģ�ⲿ�� */
	analog_init();
	
	/* ������Ļ */
	Lcd_Init();
	
	/* ��ʼ��ϵͳ���� */
	Systick_Init();
	
	DemoSpiFlash();
	
	test01();
}

void myOS_1ms_Func(void)
{
	
}

void myOS_10ms_Func(void)
{
	
}

void myOS_100ms_Func(void)
{
	static uint8_t clickCount = 0;
	/* isDown = 0:δ�ػ� isDown = 1:�ѹػ� */
	static uint8_t isDown = 0;
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
		/* �ػ� */
		isDown = 1;
		
		/* �رյ�Դ -> ����IO : PC4 Ϊ�������룬����̬ */
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		GPIO_InitStruct.Pin = GPIO_PIN_4;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	}
}


