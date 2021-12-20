#include "CONF.h"

uint8_t sss = 0;
/* ����ṹ�嶨�� */
struct taskStructDef taskStruct[32];
/* £�������� */
uint8_t taskNum;

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
	
	CONFIG_Default();
	
	/* ��ʼ������ */
	MX_USART2_UART_Init();
	
	/* ��ʼ��FATFS */
	MX_FATFS_Init();
	
	/* ��ʼ��USBHOST */
  MX_USB_HOST_Init();
	
	/* ��ʼ��ģ�ⲿ�� */
	analog_init();
	
	/* GUI��ʼ�� */
	GUI_Init();
	
	/* ��ʼ��ϵͳ���� */
	myOS_InitTasks();
	
	//DemoSpiFlash();
	
	test01();
	
	while(1)
	{
		myOS_ProcessTasks();
		GUI_DrawWave();
		delayms(10);
		
		volatile  int time2;
	volatile int time = Systick_GetRunTime();
	
	clearLcd(BLACK, 1);
	time2 = Systick_GetRunTime();
	int time3 = time2-time;
	
	}
	
	
}



/* ��ʼ��ϵͳ���� */
void myOS_InitTasks(void)
{
	uint8_t id = 0;
	myOS_RegisterTask(myOS_ShutDown, &isDown, id++);
	myOS_RegisterTask(cmdProcess, &isReceived, id++);
	myOS_RegisterTask(GUI_MenuRefresh, &isMenuChanged, id++);
	
	taskNum = id;
}								

/* ע��ϵͳ���� */
void myOS_RegisterTask(void (*func)(void), uint8_t *flag, uint8_t id)
{
	taskStruct[id].id = id;
	taskStruct[id].flag = flag;
	taskStruct[id].taskFuncs = func;
}

/* ����ϵͳ���� */
void myOS_ProcessTasks(void)
{
	uint8_t i;
	/* �������� */
	for(i = 0;i < taskNum ;i++)
	{
		if(*(taskStruct[i].flag))
		{
			break;
		}
	}
	/* �������� */
	if(i < taskNum)
	{
		taskStruct[i].taskFuncs();
		*(taskStruct[i].flag) = 0;
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
	myOS_checkShutDown();
	
}




