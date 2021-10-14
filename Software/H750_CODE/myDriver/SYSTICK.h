#ifndef __SYSTICK_H
#define __SYSTICK_H


/*
	在此定义若干个软件定时器全局变量
	注意，必须增加__IO 即 volatile，因为这个变量在中断和主程序中同时被访问，有可能造成编译器错误优化。
*/
#define SYS_TIM_NUM	4		/* 软件定时器的个数 （定时器ID范围 0 - 3) */

/* 开关全局中断的宏 */
#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */

/* 定时器结构体，成员变量必须是 volatile, 否则C编译器优化时可能有问题 */
typedef enum
{
	TMR_ONCE_MODE = 0,		/* 一次工作模式 */
	TMR_AUTO_MODE = 1		/* 自动定时工作模式 */
}TMR_MODE_E;

/* 定时器结构体，成员变量必须是 volatile, 否则C编译器优化时可能有问题 */
typedef struct
{
	volatile uint8_t Mode;		/* 计数器模式，1次性 */
	volatile uint8_t Flag;		/* 定时到达标志  */
	volatile uint32_t Count;	/* 计数器 */
	volatile uint32_t PreLoad;	/* 计数器预装值 */
}SoftTimerStruct;

/* 提供给其他C文件调用的函数 */
void Systick_Init(void);
void delayms(uint32_t n);
void delayus(uint32_t n);
void Systick_StartTimer(uint8_t _id, uint32_t _period);
void Systick_StartAutoTimer(uint8_t _id, uint32_t _period);
void Systick_StopTimer(uint8_t _id);
uint8_t Systick_CheckTimer(uint8_t _id);
int32_t Systick_GetRunTime(void);
int32_t Systick_CheckRunTime(int32_t _LastTime);
void bsp_Idle(void);

static void Systick_CounterDec(SoftTimerStruct *_tmr);

#endif

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
