#include "CONF.h"

/* isDown = 0:未关机 isDown = 1:已关机 */
uint8_t isDown = 0;

/* 检测关机 */
void myOS_checkShutDown(void)
{
	static uint8_t clickCount = 0;
	/* everRelease = 0:按键未释放 everRelease = 1:按键释放过 */
	static uint8_t everRelease = 0;
	/* 获取系统运行时长 */
	int32_t runTime = Systick_GetRunTime();
	
	/* 若已经关机或开机不足OFF_WAIT秒则不进行判断 */
	if(isDown == 1 || runTime <= OFF_WAIT * 1000)
	{
		return;
	}
	
	/* 如果onoff键被按下 且 onoff键曾被释放过 */
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == GPIO_PIN_SET && everRelease == 1)
	{
		/* 计数 */
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
		/* 关闭电源 -> 设置IO : PC4 为浮空输入，高阻态 */
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		GPIO_InitStruct.Pin = GPIO_PIN_4;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		/* 关机 */
		isDown = 1;
	}
}

/* 执行关机 */
void myOS_ShutDown(void)
{
	/* 显示关机提示 */
	drawShutDownMsg(1);
	/* 等待 */
	while(1);
}

