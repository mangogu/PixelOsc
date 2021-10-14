#ifndef GUI_H
#define GUI_H

#include "LCD.h"
#include "CONF.h"

/* 常用颜色 */
#define WHITE 	0
#define BLACK 	1
#define GREY_L 	9


/********************结构体定义**********************/
/* 菜单按钮结构体 */
struct menuBtnStructDef
{
	/* 控件种类 */
	uint8_t type;
	/* 控件上部文字 */
	char strPtr_1[TEXT_LEN];		
	char chnPtr_1[TEXT_LEN];		/* 中文 */
	/* 控件下部文字 */
	char strPtr_2[TEXT_LEN];		/* 英文 */
	char chnPtr_2[TEXT_LEN];		/* 中文 */
}; 

/* 菜单页结构体 */
struct pageSturctDef
{
	/* 识别号 */
	uint8_t page;
	/* 菜单按钮x5 */
	struct menuBtnStructDef menuBtn_1;
	struct menuBtnStructDef menuBtn_2;
	struct menuBtnStructDef menuBtn_3;
	struct menuBtnStructDef menuBtn_4;
	struct menuBtnStructDef menuBtn_5;
};

/* 菜单结构体 */
struct menuSturctDef
{
	/* 识别号 */
	char* name;
	/* 菜单页数 */
	uint8_t len;
	/* 菜单页数 */
	uint8_t curPage;
	/* 菜单页 */
	uint8_t selected;
	/* 菜单页 */
	struct pageSturctDef page_1;
	struct pageSturctDef page_2;
}; 

/* 底栏标签结构体 */
struct labelStructDef
{
	/* id号 */
	uint8_t id;		
	/* 标签左部文字 */
	char strPtr_1[TEXT_LEN];		
	/* 标签右部文字 */
	char strPtr_2[TEXT_LEN];		
}; 

/* 底栏结构体 */
struct bottomStructDef
{
	/* 选中 */
	uint8_t selected;
	/* 标签1 */
	struct labelStructDef label_1;
	/* 标签2*/
	struct labelStructDef label_2;
	/* 标签3 */
	struct labelStructDef label_3;
	/* 标签4 */
	struct labelStructDef label_4;
}; 

/* 框架 */
#define	NO_FRAME			0x00
#define	NORMAL_FRAME	0x01
#define	SETUP_FRAME		0x02

/* 框架 */
#define PAGE1 		0x00
#define PAGE2			0x01

/* 翻页文字 */
#define	NEXT_PAGE "Next"
#define	PRE_PAGE "Previous"

/* 菜单掩码 */
#define NO_MENU "XXXX";

/* 菜单样式 */
#define	ONLY_BTN 0x00
#define	BTN_TEXT 0x01

/* 选中 */
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

#endif
