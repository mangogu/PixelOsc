#ifndef __SWITCH_H
#define __SWITCH_H

#include "CONF.h"

#define RELEASE				0
#define CLICK					1
#define PRESS					2

#define UNCHANGED			0
#define CHANGED				1

#define PRESS_TIME 		2 	/* ����ʱ�䣨��λ���룬��ȷ��10ms�� */
#define PRESS_TIME_S	0.1 /* ��������ʱ�䣨��λ���룬��ȷ��10ms�� */

/* �����ṹ�� */
struct swtichSturctDef
{
	/* GPIO�� */
	GPIO_TypeDef* GPIO;
	/* GPIO�� */
	uint16_t GPIO_Pin;
	/* ����״̬(40ms) */
	uint8_t record;
	/* ����״̬���� */
	uint16_t record_times;
	/* ��������״̬ */
	uint8_t abstractStatus;
	/* ��������״̬�Ƿ�ı� */
	uint8_t StatusChanged;
	/* ��������ָ�� */
	char* clickCMD;
	/* ��������ָ�� */
	char* pressCMD;
}; 

struct swtich5DSturctDef
{
	/* GPIO�� */
	GPIO_TypeDef* GPIO;
	/* GPIO�� */
	uint16_t GPIO_Pin;
	/* �ϰ���״̬(40ms) */
	uint8_t upRecord;
	/* �°���״̬(40ms) */
	uint8_t downRecord;
	/* �󰴼�״̬(40ms) */
	uint8_t leftRecord;
	/* �Ұ���״̬(40ms) */
	uint8_t rightRecord;
	/* �а���״̬(40ms) */
	uint8_t middleRecord;
	
	/* �ϰ���״̬���� */
	uint16_t upRecord_times;
	/* �°���״̬���� */
	uint16_t downRecord_times;
	/* �󰴼�״̬���� */
	uint16_t leftRecord_times;
	/* �Ұ���״̬���� */
	uint16_t rightRecord_times;
	/* �а���״̬���� */
	uint16_t middleRecord_times;
	
	/* �ϰ�������״̬ */
	uint8_t upAbstractStatus;
	/* �°�������״̬ */
	uint8_t downAbstractStatus;
	/* �󰴼�����״̬ */
	uint8_t leftAbstractStatus;
	/* �Ұ�������״̬ */
	uint8_t rightAbstractStatus;
	/* �а�������״̬ */
	uint8_t middleAbstractStatus;
	
	/* �ϰ�������״̬�Ƿ�ı� */
	uint8_t upStatusChanged;
	/* �°�������״̬�Ƿ�ı� */
	uint8_t downStatusChanged;
	/* �󰴼�����״̬�Ƿ�ı� */
	uint8_t leftStatusChanged;
	/* �Ұ�������״̬�Ƿ�ı� */
	uint8_t rightStatusChanged;
	/* �а�������״̬�Ƿ�ı� */
	uint8_t middleStatusChanged;
	
	/* �ϰ�������ָ�� */
	char* upClickCMD;
	/* �ϼ�����ָ�� */
	char* upPressCMD;
	
	/* �°�������ָ�� */
	char* downClickCMD;
	/* �¼�����ָ�� */
	char* downPressCMD;
	
	/* �󰴼�����ָ�� */
	char* leftClickCMD;
	/* �������ָ�� */
	char* leftPressCMD;
	
	/* �Ұ�������ָ�� */
	char* rightClickCMD;
	/* �Ҽ�����ָ�� */
	char* rightPressCMD;
	
	/* �а�������ָ�� */
	char* middleClickCMD;
	/* �м�����ָ�� */
	char* middlePressCMD;
}; 

void SWITCH_CS(uint8_t cs);
void SWITCH_Scan(void);
void SWITCH_CheckStatus(void);
void SWITCH_5DSwitchOn(void);
void SWITCH_5DSwitchOFF(void);

extern uint8_t CHA_Record;
extern uint8_t CHB_Record;
extern uint8_t MATH_Record;
extern uint8_t TRIG_Record;
extern uint8_t CTR_Record;

#endif

