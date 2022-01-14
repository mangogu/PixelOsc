#include "CONF.h"

/* 定时中断函数 */
void myOS_1ms_Func(void)
{
}

void myOS_5ms_Func(void)
{
	SWITCH_Scan();
	SWITCH_CheckStatus();
}

void myOS_10ms_Func(void)
{
	
}

void myOS_100ms_Func(void)
{
	
}

