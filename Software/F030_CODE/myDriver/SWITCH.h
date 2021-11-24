#ifndef __SWITCH_H
#define __SWITCH_H

#include "CONF.h"

#define RELEASE				0
#define CLICK					1
#define PRESS					2

#define UNCHANGED			0
#define CHANGED				1

#define PRESS_TIME 		2 	/* 长按时间（单位：秒，精确到10ms） */
#define PRESS_TIME_S	0.1 /* 连续长按时间（单位：秒，精确到10ms） */

/* 按键结构体 */
struct swtichSturctDef
{
	/* GPIO组 */
	GPIO_TypeDef* GPIO;
	/* GPIO号 */
	uint16_t GPIO_Pin;
	/* 按键状态(40ms) */
	uint8_t record;
	/* 按键状态次数 */
	uint16_t record_times;
	/* 按键抽象状态 */
	uint8_t abstractStatus;
	/* 按键抽象状态是否改变 */
	uint8_t StatusChanged;
	/* 按键按下指令 */
	char* clickCMD;
	/* 按键长按指令 */
	char* pressCMD;
}; 

struct swtich5DSturctDef
{
	/* GPIO组 */
	GPIO_TypeDef* GPIO;
	/* GPIO号 */
	uint16_t GPIO_Pin;
	/* 上按键状态(40ms) */
	uint8_t upRecord;
	/* 下按键状态(40ms) */
	uint8_t downRecord;
	/* 左按键状态(40ms) */
	uint8_t leftRecord;
	/* 右按键状态(40ms) */
	uint8_t rightRecord;
	/* 中按键状态(40ms) */
	uint8_t middleRecord;
	
	/* 上按键状态次数 */
	uint16_t upRecord_times;
	/* 下按键状态次数 */
	uint16_t downRecord_times;
	/* 左按键状态次数 */
	uint16_t leftRecord_times;
	/* 右按键状态次数 */
	uint16_t rightRecord_times;
	/* 中按键状态次数 */
	uint16_t middleRecord_times;
	
	/* 上按键抽象状态 */
	uint8_t upAbstractStatus;
	/* 下按键抽象状态 */
	uint8_t downAbstractStatus;
	/* 左按键抽象状态 */
	uint8_t leftAbstractStatus;
	/* 右按键抽象状态 */
	uint8_t rightAbstractStatus;
	/* 中按键抽象状态 */
	uint8_t middleAbstractStatus;
	
	/* 上按键抽象状态是否改变 */
	uint8_t upStatusChanged;
	/* 下按键抽象状态是否改变 */
	uint8_t downStatusChanged;
	/* 左按键抽象状态是否改变 */
	uint8_t leftStatusChanged;
	/* 右按键抽象状态是否改变 */
	uint8_t rightStatusChanged;
	/* 中按键抽象状态是否改变 */
	uint8_t middleStatusChanged;
	
	/* 上按键按下指令 */
	char* upClickCMD;
	/* 上键长按指令 */
	char* upPressCMD;
	
	/* 下按键按下指令 */
	char* downClickCMD;
	/* 下键长按指令 */
	char* downPressCMD;
	
	/* 左按键按下指令 */
	char* leftClickCMD;
	/* 左键长按指令 */
	char* leftPressCMD;
	
	/* 右按键按下指令 */
	char* rightClickCMD;
	/* 右键长按指令 */
	char* rightPressCMD;
	
	/* 中按键按下指令 */
	char* middleClickCMD;
	/* 中键长按指令 */
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

