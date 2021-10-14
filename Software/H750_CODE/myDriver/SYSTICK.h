#ifndef __SYSTICK_H
#define __SYSTICK_H


/*
	�ڴ˶������ɸ������ʱ��ȫ�ֱ���
	ע�⣬��������__IO �� volatile����Ϊ����������жϺ���������ͬʱ�����ʣ��п�����ɱ����������Ż���
*/
#define SYS_TIM_NUM	4		/* �����ʱ���ĸ��� ����ʱ��ID��Χ 0 - 3) */

/* ����ȫ���жϵĺ� */
#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */

/* ��ʱ���ṹ�壬��Ա���������� volatile, ����C�������Ż�ʱ���������� */
typedef enum
{
	TMR_ONCE_MODE = 0,		/* һ�ι���ģʽ */
	TMR_AUTO_MODE = 1		/* �Զ���ʱ����ģʽ */
}TMR_MODE_E;

/* ��ʱ���ṹ�壬��Ա���������� volatile, ����C�������Ż�ʱ���������� */
typedef struct
{
	volatile uint8_t Mode;		/* ������ģʽ��1���� */
	volatile uint8_t Flag;		/* ��ʱ�����־  */
	volatile uint32_t Count;	/* ������ */
	volatile uint32_t PreLoad;	/* ������Ԥװֵ */
}SoftTimerStruct;

/* �ṩ������C�ļ����õĺ��� */
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

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
