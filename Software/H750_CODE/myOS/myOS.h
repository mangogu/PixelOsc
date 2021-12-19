#ifndef __MYOS_H
#define __MYOS_H

#include "CONF.h"

/* 函数定义 */
void myOs_DevInit(void);
void myOS_1ms_Func(void);
void myOS_10ms_Func(void);
void myOS_100ms_Func(void);
void myOS_ProcessTasks(void);
void myOS_RegisterTask(void (*func)(void), uint8_t *flag, uint8_t id);
void myOS_InitTasks(void);

#define ACTIVATE_TASK(X) taskFlags = 0X01<<X

//#define EVENT(X)	myFLAG &= (0X01<<X)

/* 任务结构体 */
struct taskStructDef
{
	uint8_t id;
	uint8_t *flag;
	void (*taskFuncs)(void);
};


#endif



