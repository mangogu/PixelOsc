#ifndef GUI_H
#define GUI_H

#include "CONF.h"

/* ������ɫ */
#define WHITE 	0
#define BLACK 	1
#define GREY_L 	9


/********************�ṹ�嶨��**********************/
/* �˵���ť�ṹ�� */
struct menuBtnStructDef
{
	/* �ؼ����� */
	uint8_t type;
	/* �ؼ��ϲ����� */
	char strPtr_1[TEXT_LEN];		
	char chnPtr_1[TEXT_LEN];		/* ���� */
	/* �ؼ��²����� */
	char strPtr_2[TEXT_LEN];		/* Ӣ�� */
	char chnPtr_2[TEXT_LEN];		/* ���� */
	char* (*recallFunc)(uint8_t, char*);
}; 

/* �˵�ҳ�ṹ�� */
struct pageSturctDef
{
	/* ʶ��� */
	uint8_t page;
	uint8_t btnNum;
	/* �˵���ťx5 */
	struct menuBtnStructDef menuBtn[5];
};

/* �˵��ṹ�� */
struct menuSturctDef
{
	/* ʶ��� */
	char* name;
	/* �˵�ҳ�� */
	uint8_t pageNum;
	/* �˵�ҳ�� */
	uint8_t curPage;
	/* �˵�ҳ */
	uint8_t selected;
	/* �˵�ҳ */
	struct pageSturctDef page[2];
}; 

/* ������ǩ�ṹ�� */
struct labelStructDef
{
	/* id�� */
	uint8_t id;		
	/* ��ǩ������ */
	char strPtr_1[TEXT_LEN];		
	/* ��ǩ�Ҳ����� */
	char strPtr_2[TEXT_LEN];		
}; 

/* �����ṹ�� */
struct bottomStructDef
{
	/* ѡ�� */
	uint8_t selected;
	/* ��ǩ1 */
	struct labelStructDef label_1;
	/* ��ǩ2*/
	struct labelStructDef label_2;
	/* ��ǩ3 */
	struct labelStructDef label_3;
	/* ��ǩ4 */
	struct labelStructDef label_4;
}; 

/* ��� */
#define	NO_FRAME			0x00
#define	NORMAL_FRAME	0x01
#define	SETUP_FRAME		0x02

/* ��� */
#define PAGE1 		0x00
#define PAGE2			0x01

/* ��ҳ���� */
#define	NEXT_PAGE "Next"
#define	PRE_PAGE "Previous"

/* �˵����� */
#define NO_MENU "XXXX";

/* �˵���ʽ */
#define	ONLY_BTN 0
#define	BTN_TEXT 1
#define	NO_BTN 	 2

/* ѡ�� */
#define NOT_SELECTED 	0x00
#define SELECTED			0x01

void GUI_drawBtn(	uint16_t x,
									uint16_t y,
									struct menuBtnStructDef* style,
									uint8_t selected,
									uint8_t layer);

void test01(void);
void drawMenu(uint8_t layer);
									void GUI_drawLabel(	uint16_t x,
										uint16_t y,
										struct labelStructDef* style,
										uint8_t selected,
										uint8_t layer);
void drawBottomLine(uint8_t layer);
void drawWelcomeWin(uint8_t layer);
void drawShutDownMsg(uint8_t layer);

extern uint8_t flagMenuChanged;
extern uint8_t flagMenuShow;
extern struct menuSturctDef* curMenu;
extern struct menuSturctDef menu[2];

#endif
