#include "CONF.h"


void myOs_DevInit(void)
{
	/* �򿪵�Դ */
	GPIO_DevInit();
	
	CONFIG_Init();
	
	/* ��ʼ��ģ�ⲿ�� */
	analog_init();
	
	/* ������Ļ */
	Lcd_Init();
	
	/* ��ʼ��ϵͳ���� */
	Systick_Init();
	
	//DemoSpiFlash();
	
	test01();
}

void myOS_1ms_Func(void)
{
	
}

void myOS_10ms_Func(void)
{
	
}

