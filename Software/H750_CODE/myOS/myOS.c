#include "CONF.h"


void myOs_DevInit(void)
{
	/* 打开电源 */
	GPIO_DevInit();
	
	CONFIG_Init();
	
	/* 初始化模拟部分 */
	analog_init();
	
	/* 点亮屏幕 */
	Lcd_Init();
	
	/* 初始化系统节拍 */
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

