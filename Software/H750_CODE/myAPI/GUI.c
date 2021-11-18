#include "GUI.h"


/* ��ǰ��� */
uint8_t curFrame;
/* �˵������־λ 1����� 0��δ��� */
uint8_t flagMenuChanged = 1;
struct menuSturctDef* curMenuPage;
/* �˵��򿪱�־λ 1���� 0���ر� */
uint8_t flagMenuShow = 1;

extern struct LcdStructDef myLcd;


/* Measure�˵����� */
struct menuSturctDef measureStruct = 
{
	.name = "<MEASURE>",
	.len = 2,
	.curPage = 1,
	.selected = 1,
	
	/* ����ҳ��1 */
	.page_1.page = 1,											/* ���1ҳ */
	
	.page_1.menuBtn_1.type = BTN_TEXT,		/* ���ð�ť���� */
	.page_1.menuBtn_1.strPtr_1 = "MasterSrc",
	.page_1.menuBtn_1.strPtr_2= "",
	
	.page_1.menuBtn_2.type = BTN_TEXT,		/* ���ð�ť���� */
	.page_1.menuBtn_2.strPtr_1 = "SlaveSrc",
	.page_1.menuBtn_2.strPtr_2 = "",
	
	.page_1.menuBtn_3.type = BTN_TEXT,		/* ���ð�ť���� */
	.page_1.menuBtn_3.strPtr_1 = "All Para",
	.page_1.menuBtn_3.strPtr_2 = "",
	
	.page_1.menuBtn_4.type = BTN_TEXT,		/* ���ð�ť���� */
	.page_1.menuBtn_4.strPtr_1 = "User Def",
	.page_1.menuBtn_4.strPtr_2 = "",
	
	.page_1.menuBtn_5.type = ONLY_BTN,		/* ���ð�ť���� */
	.page_1.menuBtn_5.strPtr_1 = NEXT_PAGE,
	
	/* ����ҳ��2 */
	.page_2.page = 2,											/* ���2ҳ */
	
	.page_2.menuBtn_1.type = BTN_TEXT,		/* ���ð�ť���� */
	.page_2.menuBtn_1.strPtr_1 = "IndicatorSel",
	
	.page_2.menuBtn_2.type = BTN_TEXT,		/* ���ð�ť���� */
	.page_2.menuBtn_2.strPtr_1 = "Indicator",
	
	.page_2.menuBtn_3.type = BTN_TEXT,		/* ���ð�ť���� */
	.page_2.menuBtn_3.strPtr_1 = "Clear",
	
	.page_2.menuBtn_4.type = BTN_TEXT,		/* ���ð�ť���� */
	.page_2.menuBtn_4.strPtr_1 = "measure Stat",
	
	.page_2.menuBtn_5.type = ONLY_BTN,		/* ���ð�ť���� */
	.page_2.menuBtn_5.strPtr_1 = PRE_PAGE,
};

/* �����ṹ�� */
struct bottomStructDef bottomStruct = 
{
	.selected = 3,
	
	.label_1.id = 1,
	.label_1.strPtr_1 = "1",
	.label_1.strPtr_2 = "xxxx",
	
	.label_2.id = 2,
	.label_2.strPtr_1 = "2",
	.label_2.strPtr_2 = "xxxx",
	
	.label_3.id = 3,
	.label_3.strPtr_1 = "M",
	.label_3.strPtr_2 = "xxxx",
	
	.label_4.id = 4,
	.label_4.strPtr_1 = "T",
	.label_4.strPtr_2 = "xxxx"
};

struct FontStructDef menuFont = 		/* ����һ������ṹ���������������������� */
{
	/* ������������ */
	.FontCode = FC_ST_16,		/* ����ѡ������16���󣬸�16x��15) */
	.FrontColor = WHITE,	/* ������ɫ����Ϊ��ɫ */
	.BackColor = BLACK,	 	/* ���ֱ�����ɫ��͸�� */
	.Space = 0				/* �ַ�ˮƽ���, ��λ = ���� */
};
	

void GUI_drawBtn(	uint16_t x,
									uint16_t y,
									struct menuBtnStructDef* style,
									uint8_t selected,
									uint8_t layer)
{
	/* �߿��ȼ��� */
	uint8_t counter = 0;
	
	/* �ϰ벿����ɫ */
	uint8_t color_up = MENU_COLOR_1;
		
	/* ��� */
	uint16_t halfHeight = MENU_HEIGHT / 2;
	
	/* ������ɫ */
	menuFont.FrontColor = MENU_COLOR_CHAR;
	if(selected == SELECTED)
	{
		color_up = MENU_COLOR_S;
		menuFont.BackColor = MENU_COLOR_S;
	}
	else
	{
		menuFont.BackColor = MENU_COLOR_1;
	}
	
	/* ��ť������ */
	if(style->type == BTN_TEXT)
	{
		/* �����ϰ벿�־��� */
		fill_By_DMA2D(x, y, MENU_WIDTH,	halfHeight, color_up, layer);
			
		/* �����°벿�־��� */
		fill_By_DMA2D(x, y + halfHeight, MENU_WIDTH,	halfHeight, MENU_COLOR_2, layer);
		
		/* ���Ʊ߿� */
		while(GUI_THICKNESS != counter)
		{
			drawRect(x + counter, y + counter, MENU_WIDTH - counter*2, MENU_HEIGHT - counter*2, color_up, layer);
			counter ++;		
		}
		
		/* ��ʾ�ϲ������� */
		dispStrEx(x + GUI_THICKNESS + 2, y + (MENU_HEIGHT / 2 - menuFont.FontCode) / 2, style->strPtr_1, &menuFont, MENU_WIDTH - 2 * (GUI_THICKNESS) - 4, ALIGN_CENTER, 1);
		/* �����ɫ */
		menuFont.BackColor = MENU_COLOR_2;
		/* ��ʾ�²������� */
		dispStrEx(x + GUI_THICKNESS + 2, y + (MENU_HEIGHT / 2 - menuFont.FontCode) / 2 + halfHeight, style->strPtr_2, &menuFont, MENU_WIDTH - 2 * (GUI_THICKNESS) - 4, ALIGN_CENTER, 1);
	}
	/* ֻ�а�ť */
	else if(style->type == ONLY_BTN)
	{
		/* ���ƾ��β��� */
		fill_By_DMA2D(x, y, MENU_WIDTH,	MENU_HEIGHT, MENU_COLOR_1, layer);
		/* ������ɫ */
		menuFont.FrontColor = MENU_COLOR_CHAR;
		menuFont.BackColor = MENU_COLOR_1;
		/* ��ʾ���� */
		dispStrEx(x + GUI_THICKNESS + 2, y +  (MENU_HEIGHT - menuFont.FontCode) / 2, style->strPtr_1, &menuFont, MENU_WIDTH - 2 * (GUI_THICKNESS) - 4, ALIGN_CENTER, 1);
		
	}
}

void drawMenu(uint8_t layer)
{
	uint16_t btnY;
	int16_t gap;
	uint16_t selectBtn = 0x01 << curMenuPage->selected ;
	
	/* �˵��ر�������˵����� */
	if(flagMenuShow == 0)
	{
		fill_By_DMA2D(myLcd.width - 1 - MENU_WIDTH - 2 * GUI_THICKNESS, 0, MENU_WIDTH, myLcd.height - 1, MAIN_BACK_COLOR, 1);
		return;
	}
	
	/* �˵�δ�ı���ˢ�� */
	if(flagMenuChanged == 0)
	{
		return;
	}
	
	/* �������Ƶ�ҳ */
	struct pageSturctDef* pageToDraw;
	
	/* ���ð�ť��y */
	btnY = TOPLINE_HEIGHT + 2 * GUI_THICKNESS;

	/* ���ð�ť��� */
	gap = (myLcd.height - 1 - btnY - 5 * MENU_HEIGHT - GUI_THICKNESS - BOTTOMLINE_HEIGHT) / 5;
	if(gap < 0)
	{
		gap = 0;
	}

	/* ����ָʾ���� */
	menuFont.BackColor = MAIN_BACK_COLOR;
	menuFont.FrontColor = WHITE;
	dispStrEx(myLcd.width - 1 - MENU_WIDTH - 2 * GUI_THICKNESS, (TOPLINE_HEIGHT - menuFont.FontCode)/2, curMenuPage->name, &menuFont, MENU_WIDTH, ALIGN_CENTER, 1);
	
	/* ѡ����Ƶ�ҳ */
	if(curMenuPage->curPage == 1)
	{
		pageToDraw = &(curMenuPage->page_1);
	}
	else if(curMenuPage->curPage == 2)
	{
		pageToDraw = &(curMenuPage->page_2);
	}
	
	/* ���ư�ť1 */
	GUI_drawBtn(	myLcd.width - 1 - MENU_WIDTH - GUI_THICKNESS, btnY, &(pageToDraw->menuBtn_1), (selectBtn>>1)&0x01, layer);
	/* ���ð�ť��y */
	btnY += MENU_HEIGHT + gap;
	/* ���ư�ť2 */
	GUI_drawBtn(	myLcd.width - 1 - MENU_WIDTH - GUI_THICKNESS, btnY, &(pageToDraw->menuBtn_2), (selectBtn>>2)&0x01, layer);
	/* ���ð�ť��y */
	btnY += MENU_HEIGHT + gap;
	/* ���ư�ť2 */
	GUI_drawBtn(	myLcd.width - 1 - MENU_WIDTH - GUI_THICKNESS, btnY, &(pageToDraw->menuBtn_3), (selectBtn>>3)&0x01, layer);
	/* ���ð�ť��y */
	btnY += MENU_HEIGHT + gap;
	/* ���ư�ť2 */
	GUI_drawBtn(	myLcd.width - 1 - MENU_WIDTH - GUI_THICKNESS, btnY, &(pageToDraw->menuBtn_4), (selectBtn>>4)&0x01, layer);
	/* ���ð�ť��y */
	btnY += MENU_HEIGHT + gap;
	/* ���ư�ť2 */
	GUI_drawBtn(	myLcd.width - 1 - MENU_WIDTH - GUI_THICKNESS, btnY, &(pageToDraw->menuBtn_5), (selectBtn>>5)&0x01, layer);
	
	/* ������־λ */	
	flagMenuChanged = 0;
}

void GUI_drawLabel(	uint16_t x,
										uint16_t y,
										struct labelStructDef* style,
										uint8_t selected,
										uint8_t layer)
{
	/* �߿��ȼ��� */
	uint8_t counter = 0;
	
	/* ��벿����ɫ */
	uint8_t color_up = BOTTOMLINE_COLOR_1;
		
	/* ������ɫ */
	menuFont.FrontColor = BOTTOMLINE_COLOR_CHAR;
	/* �����ѡ�У������label��ȷ����ɫ */
	if(selected)
	{
		if(style->id == 1)
		{
			color_up = BOTTOMLINE_COLOR_S1;
			menuFont.BackColor = BOTTOMLINE_COLOR_S1;
		}
		else if(style->id == 2)
		{
			color_up = BOTTOMLINE_COLOR_S2;
			menuFont.BackColor = BOTTOMLINE_COLOR_S2;
		}
		else if(style->id == 3)
		{
			color_up = BOTTOMLINE_COLOR_S3;
			menuFont.BackColor = BOTTOMLINE_COLOR_S3;
		}
		else if(style->id == 4)
		{
			color_up = BOTTOMLINE_COLOR_S4;
			menuFont.BackColor = BOTTOMLINE_COLOR_S4;
		}
	}
	/* ���δ��ѡ�У���ΪĬ����ɫ */
	else
	{
		color_up = GREY_L;
		menuFont.BackColor = GREY_L;
	}
	
	/* ������벿�־��� */
	fill_By_DMA2D(x, y, BOTTOMLINE_LEFT_WIDTH,	BOTTOMLINE_HEIGHT, color_up, layer);
		
	/* �����Ұ벿�־��� */
	fill_By_DMA2D(x + BOTTOMLINE_LEFT_WIDTH, y, BOTTOMLINE_WIDTH - BOTTOMLINE_LEFT_WIDTH,
	BOTTOMLINE_HEIGHT, BOTTOMLINE_COLOR_2, layer);
	
	/* ���Ʊ߿� */
	while(GUI_THICKNESS != counter)
	{
		drawRect(x + counter, y + counter, BOTTOMLINE_WIDTH - counter*2, BOTTOMLINE_HEIGHT - counter*2, color_up, layer);
		counter ++;		
	}
	
	/* ��ʾ�󲿷����� */
	dispStrEx(x + GUI_THICKNESS + 2, y + (BOTTOMLINE_HEIGHT - menuFont.FontCode) / 2, style->strPtr_1, &menuFont,
	BOTTOMLINE_LEFT_WIDTH - GUI_THICKNESS * 2 - 4, ALIGN_CENTER, 1);
	/* �����ɫ */
	menuFont.BackColor = BOTTOMLINE_COLOR_2;
	/* ��ʾ�Ҳ������� */
	dispStrEx(x + BOTTOMLINE_LEFT_WIDTH + GUI_THICKNESS + 2, y + (BOTTOMLINE_HEIGHT - menuFont.FontCode) / 2, style->strPtr_2, &menuFont,
	BOTTOMLINE_WIDTH - BOTTOMLINE_LEFT_WIDTH - GUI_THICKNESS * 2 - 4, ALIGN_CENTER, 1);
}


void drawBottomLine(uint8_t layer)
{
	int16_t gap;
	uint16_t labelX = GUI_THICKNESS;
	uint16_t selectLab = 0x01 << bottomStruct.selected ;
	
	/* ���ñ�ǩ��� */
	gap = (myLcd.width - 1 - 2*GUI_THICKNESS - 4 * BOTTOMLINE_WIDTH) / 3;
	
	/* ���Ʊ�ǩ1 */
	GUI_drawLabel(labelX,	myLcd.height - 1 - GUI_THICKNESS - BOTTOMLINE_HEIGHT,	&(bottomStruct.label_1),	(selectLab>>1)&0x01,	1);
	/* ����xλ�� */
	labelX += gap + BOTTOMLINE_WIDTH;
	/* ���Ʊ�ǩ2 */
	GUI_drawLabel(labelX,	myLcd.height - 1 - GUI_THICKNESS - BOTTOMLINE_HEIGHT,	&(bottomStruct.label_2),	(selectLab>>2)&0x01,	1);
	/* ����xλ�� */
	labelX += gap + BOTTOMLINE_WIDTH;
	/* ���Ʊ�ǩ3 */
	GUI_drawLabel(labelX,	myLcd.height - 1 - GUI_THICKNESS - BOTTOMLINE_HEIGHT,	&(bottomStruct.label_3),	(selectLab>>3)&0x01,	1);
	/* ����xλ�� */
	labelX += gap + BOTTOMLINE_WIDTH;
	/* ���Ʊ�ǩ4 */
	GUI_drawLabel(labelX,	myLcd.height - 1 - GUI_THICKNESS - BOTTOMLINE_HEIGHT,	&(bottomStruct.label_4),	(selectLab>>4)&0x01,	1);	
}

void drawWelcomeWin(uint8_t layer)
{
	/* ������Ӱ */
	fill_By_DMA2D(WELCOME_WINDOW_X + WELCOME_WINDOW_SHADOW_DISTANCE, WELCOME_WINDOW_Y + WELCOME_WINDOW_SHADOW_DISTANCE,
	WELCOME_WINDOW_WIDTH + WELCOME_WINDOW_SHADOW_DISTANCE,	WELCOME_WINDOW_HEIGHT + WELCOME_WINDOW_SHADOW_DISTANCE, WELCOME_WINDOW_COLOR_SHADOW, layer);
	/* ������ʾ���� */
	fill_By_DMA2D(WELCOME_WINDOW_X, WELCOME_WINDOW_Y,
	WELCOME_WINDOW_WIDTH + WELCOME_WINDOW_SHADOW_DISTANCE,	WELCOME_WINDOW_HEIGHT + WELCOME_WINDOW_SHADOW_DISTANCE, WELCOME_WINDOW_COLOR_TOP, layer);
	/* ��ʾ���� */
	menuFont.BackColor = WELCOME_WINDOW_COLOR_TOP;
	menuFont.FrontColor = WELCOME_WINDOW_COLOR_CHAR;
	dispStrEx(WELCOME_WINDOW_X, WELCOME_WINDOW_Y, "111222333", &menuFont,	0, ALIGN_LEFT, 1);
}
	

void test01(void)
{
	
	clearLcd(MAIN_BACK_COLOR, 1);
	
	curMenuPage = &measureStruct;
	
	drawMenu(1);
	
	drawWelcomeWin(1);
	HAL_Delay(500);
	measureStruct.curPage = 2;
	
	flagMenuChanged = 1;
	drawMenu(1);
	
	
	bottomStruct.selected = 1;
	drawBottomLine(1);
	HAL_Delay(500);
	
	bottomStruct.selected = 2;
	drawBottomLine(1);
	HAL_Delay(500);
	
	bottomStruct.selected = 3;
	drawBottomLine(1);
	HAL_Delay(500);
	
	bottomStruct.selected = 4;
	drawBottomLine(1);
	HAL_Delay(500);
	
	bottomStruct.selected = 0;
	drawBottomLine(1);
	HAL_Delay(500);
	
	drawRect(10,10,4,4,WHITE,1);
	
	 fill_By_DMA2D(	10,
										 10,
										 4, 
										 4,
											WHITE,
										 1);
	
}

void refreshGUI(uint8_t curFrame)
{
	
	//static uint8_t p_frame = NO_FRAME;
	
	
}


