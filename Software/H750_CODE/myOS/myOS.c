#include "CONF.h"

uint8_t sss = 0;
/* 任务结构体定义 */
struct taskStructDef taskStruct[32];
/* 拢共任务量 */
uint8_t taskNum;

void myOs_DevInit(void)
{
	/* 打开电源 */
	GPIO_DevInit();
	
	/* 点亮屏幕 */
	Lcd_Init();
	
	
	
	/* 初始化系统节拍 */
	Systick_Init();
	
	/* 初始化外部FLASH */
	CONFIG_Init();
	
	CONFIG_Default();
	
	/* 初始化串口 */
	MX_USART2_UART_Init();
	
	/* 初始化FATFS */
	MX_FATFS_Init();
	
	/* 初始化USBHOST */
  MX_USB_HOST_Init();
	
	/* 初始化模拟部分 */
	analog_init();
	
	/* GUI初始化 */
	GUI_Init();
	
	/* 初始化系统任务 */
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



/* 初始化系统任务 */
void myOS_InitTasks(void)
{
	uint8_t id = 0;
	myOS_RegisterTask(myOS_ShutDown, &isDown, id++);
	myOS_RegisterTask(cmdProcess, &isReceived, id++);
	myOS_RegisterTask(GUI_MenuRefresh, &isMenuChanged, id++);
	
	taskNum = id;
}								

/* 注册系统任务 */
void myOS_RegisterTask(void (*func)(void), uint8_t *flag, uint8_t id)
{
	taskStruct[id].id = id;
	taskStruct[id].flag = flag;
	taskStruct[id].taskFuncs = func;
}

/* 处理系统任务 */
void myOS_ProcessTasks(void)
{
	uint8_t i;
	/* 遍历任务 */
	for(i = 0;i < taskNum ;i++)
	{
		if(*(taskStruct[i].flag))
		{
			break;
		}
	}
	/* 处理任务 */
	if(i < taskNum)
	{
		taskStruct[i].taskFuncs();
		*(taskStruct[i].flag) = 0;
	}
}

/* 定时中断函数 */
void myOS_1ms_Func(void)
{
	
}

void myOS_10ms_Func(void)
{
	
}
void myOS_100ms_Func(void)
{
	/* 检测关机 */
	myOS_checkShutDown();
	
}




