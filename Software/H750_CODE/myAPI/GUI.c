#include "GUI.h"


/* 当前框架 */
uint8_t curFrame;
/* 菜单变更标志位 1：变更 0：未变更 */
uint8_t flagMenuChanged = 1;
struct menuSturctDef* curMenuPage;
/* 菜单打开标志位 1：打开 0：关闭 */
uint8_t flagMenuShow = 1;

extern struct LcdStructDef myLcd;


/* Measure菜单定义 */
struct menuSturctDef measureStruct = 
{
	.name = "<MEASURE>",
	.len = 2,
	.curPage = 1,
	.selected = 1,
	
	/* 配置页面1 */
	.page_1.page = 1,											/* 这第1页 */
	
	.page_1.menuBtn_1.type = BTN_TEXT,		/* 配置按钮属性 */
	.page_1.menuBtn_1.strPtr_1 = "MasterSrc",
	.page_1.menuBtn_1.strPtr_2= "",
	
	.page_1.menuBtn_2.type = BTN_TEXT,		/* 配置按钮属性 */
	.page_1.menuBtn_2.strPtr_1 = "SlaveSrc",
	.page_1.menuBtn_2.strPtr_2 = "",
	
	.page_1.menuBtn_3.type = BTN_TEXT,		/* 配置按钮属性 */
	.page_1.menuBtn_3.strPtr_1 = "All Para",
	.page_1.menuBtn_3.strPtr_2 = "",
	
	.page_1.menuBtn_4.type = BTN_TEXT,		/* 配置按钮属性 */
	.page_1.menuBtn_4.strPtr_1 = "User Def",
	.page_1.menuBtn_4.strPtr_2 = "",
	
	.page_1.menuBtn_5.type = ONLY_BTN,		/* 配置按钮属性 */
	.page_1.menuBtn_5.strPtr_1 = NEXT_PAGE,
	
	/* 配置页面2 */
	.page_2.page = 2,											/* 这第2页 */
	
	.page_2.menuBtn_1.type = BTN_TEXT,		/* 配置按钮属性 */
	.page_2.menuBtn_1.strPtr_1 = "IndicatorSel",
	
	.page_2.menuBtn_2.type = BTN_TEXT,		/* 配置按钮属性 */
	.page_2.menuBtn_2.strPtr_1 = "Indicator",
	
	.page_2.menuBtn_3.type = BTN_TEXT,		/* 配置按钮属性 */
	.page_2.menuBtn_3.strPtr_1 = "Clear",
	
	.page_2.menuBtn_4.type = BTN_TEXT,		/* 配置按钮属性 */
	.page_2.menuBtn_4.strPtr_1 = "measure Stat",
	
	.page_2.menuBtn_5.type = ONLY_BTN,		/* 配置按钮属性 */
	.page_2.menuBtn_5.strPtr_1 = PRE_PAGE,
};

/* 底栏结构体 */
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

struct FontStructDef menuFont = 		/* 定义一个字体结构体变量，用于设置字体参数 */
{
	/* 设置字体属性 */
	.FontCode = FC_ST_16,		/* 字体选择宋体16点阵，高16x宽15) */
	.FrontColor = WHITE,	/* 字体颜色设置为白色 */
	.BackColor = BLACK,	 	/* 文字背景颜色，透明 */
	.Space = 0				/* 字符水平间距, 单位 = 像素 */
};
	

void GUI_drawBtn(	uint16_t x,
									uint16_t y,
									struct menuBtnStructDef* style,
									uint8_t selected,
									uint8_t layer)
{
	/* 边框宽度计数 */
	uint8_t counter = 0;
	
	/* 上半部分颜色 */
	uint8_t color_up = MENU_COLOR_1;
		
	/* 半高 */
	uint16_t halfHeight = MENU_HEIGHT / 2;
	
	/* 载入颜色 */
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
	
	/* 按钮和属性 */
	if(style->type == BTN_TEXT)
	{
		/* 绘制上半部分矩形 */
		fill_By_DMA2D(x, y, MENU_WIDTH,	halfHeight, color_up, layer);
			
		/* 绘制下半部分矩形 */
		fill_By_DMA2D(x, y + halfHeight, MENU_WIDTH,	halfHeight, MENU_COLOR_2, layer);
		
		/* 绘制边框 */
		while(GUI_THICKNESS != counter)
		{
			drawRect(x + counter, y + counter, MENU_WIDTH - counter*2, MENU_HEIGHT - counter*2, color_up, layer);
			counter ++;		
		}
		
		/* 显示上部分文字 */
		dispStrEx(x + GUI_THICKNESS + 2, y + (MENU_HEIGHT / 2 - menuFont.FontCode) / 2, style->strPtr_1, &menuFont, MENU_WIDTH - 2 * (GUI_THICKNESS) - 4, ALIGN_CENTER, 1);
		/* 变更颜色 */
		menuFont.BackColor = MENU_COLOR_2;
		/* 显示下部分文字 */
		dispStrEx(x + GUI_THICKNESS + 2, y + (MENU_HEIGHT / 2 - menuFont.FontCode) / 2 + halfHeight, style->strPtr_2, &menuFont, MENU_WIDTH - 2 * (GUI_THICKNESS) - 4, ALIGN_CENTER, 1);
	}
	/* 只有按钮 */
	else if(style->type == ONLY_BTN)
	{
		/* 绘制矩形部分 */
		fill_By_DMA2D(x, y, MENU_WIDTH,	MENU_HEIGHT, MENU_COLOR_1, layer);
		/* 载入颜色 */
		menuFont.FrontColor = MENU_COLOR_CHAR;
		menuFont.BackColor = MENU_COLOR_1;
		/* 显示文字 */
		dispStrEx(x + GUI_THICKNESS + 2, y +  (MENU_HEIGHT - menuFont.FontCode) / 2, style->strPtr_1, &menuFont, MENU_WIDTH - 2 * (GUI_THICKNESS) - 4, ALIGN_CENTER, 1);
		
	}
}

void drawMenu(uint8_t layer)
{
	uint16_t btnY;
	int16_t gap;
	uint16_t selectBtn = 0x01 << curMenuPage->selected ;
	
	/* 菜单关闭则清除菜单区域 */
	if(flagMenuShow == 0)
	{
		fill_By_DMA2D(myLcd.width - 1 - MENU_WIDTH - 2 * GUI_THICKNESS, 0, MENU_WIDTH, myLcd.height - 1, MAIN_BACK_COLOR, 1);
		return;
	}
	
	/* 菜单未改变则不刷新 */
	if(flagMenuChanged == 0)
	{
		return;
	}
	
	/* 将被绘制的页 */
	struct pageSturctDef* pageToDraw;
	
	/* 设置按钮的y */
	btnY = TOPLINE_HEIGHT + 2 * GUI_THICKNESS;

	/* 设置按钮间距 */
	gap = (myLcd.height - 1 - btnY - 5 * MENU_HEIGHT - GUI_THICKNESS - BOTTOMLINE_HEIGHT) / 5;
	if(gap < 0)
	{
		gap = 0;
	}

	/* 绘制指示文字 */
	menuFont.BackColor = MAIN_BACK_COLOR;
	menuFont.FrontColor = WHITE;
	dispStrEx(myLcd.width - 1 - MENU_WIDTH - 2 * GUI_THICKNESS, (TOPLINE_HEIGHT - menuFont.FontCode)/2, curMenuPage->name, &menuFont, MENU_WIDTH, ALIGN_CENTER, 1);
	
	/* 选择绘制的页 */
	if(curMenuPage->curPage == 1)
	{
		pageToDraw = &(curMenuPage->page_1);
	}
	else if(curMenuPage->curPage == 2)
	{
		pageToDraw = &(curMenuPage->page_2);
	}
	
	/* 绘制按钮1 */
	GUI_drawBtn(	myLcd.width - 1 - MENU_WIDTH - GUI_THICKNESS, btnY, &(pageToDraw->menuBtn_1), (selectBtn>>1)&0x01, layer);
	/* 设置按钮的y */
	btnY += MENU_HEIGHT + gap;
	/* 绘制按钮2 */
	GUI_drawBtn(	myLcd.width - 1 - MENU_WIDTH - GUI_THICKNESS, btnY, &(pageToDraw->menuBtn_2), (selectBtn>>2)&0x01, layer);
	/* 设置按钮的y */
	btnY += MENU_HEIGHT + gap;
	/* 绘制按钮2 */
	GUI_drawBtn(	myLcd.width - 1 - MENU_WIDTH - GUI_THICKNESS, btnY, &(pageToDraw->menuBtn_3), (selectBtn>>3)&0x01, layer);
	/* 设置按钮的y */
	btnY += MENU_HEIGHT + gap;
	/* 绘制按钮2 */
	GUI_drawBtn(	myLcd.width - 1 - MENU_WIDTH - GUI_THICKNESS, btnY, &(pageToDraw->menuBtn_4), (selectBtn>>4)&0x01, layer);
	/* 设置按钮的y */
	btnY += MENU_HEIGHT + gap;
	/* 绘制按钮2 */
	GUI_drawBtn(	myLcd.width - 1 - MENU_WIDTH - GUI_THICKNESS, btnY, &(pageToDraw->menuBtn_5), (selectBtn>>5)&0x01, layer);
	
	/* 消除标志位 */	
	flagMenuChanged = 0;
}

void GUI_drawLabel(	uint16_t x,
										uint16_t y,
										struct labelStructDef* style,
										uint8_t selected,
										uint8_t layer)
{
	/* 边框宽度计数 */
	uint8_t counter = 0;
	
	/* 左半部分颜色 */
	uint8_t color_up = BOTTOMLINE_COLOR_1;
		
	/* 载入颜色 */
	menuFont.FrontColor = BOTTOMLINE_COLOR_CHAR;
	/* 如果被选中，则根据label号确定颜色 */
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
	/* 如果未被选中，则为默认颜色 */
	else
	{
		color_up = GREY_L;
		menuFont.BackColor = GREY_L;
	}
	
	/* 绘制左半部分矩形 */
	fill_By_DMA2D(x, y, BOTTOMLINE_LEFT_WIDTH,	BOTTOMLINE_HEIGHT, color_up, layer);
		
	/* 绘制右半部分矩形 */
	fill_By_DMA2D(x + BOTTOMLINE_LEFT_WIDTH, y, BOTTOMLINE_WIDTH - BOTTOMLINE_LEFT_WIDTH,
	BOTTOMLINE_HEIGHT, BOTTOMLINE_COLOR_2, layer);
	
	/* 绘制边框 */
	while(GUI_THICKNESS != counter)
	{
		drawRect(x + counter, y + counter, BOTTOMLINE_WIDTH - counter*2, BOTTOMLINE_HEIGHT - counter*2, color_up, layer);
		counter ++;		
	}
	
	/* 显示左部分文字 */
	dispStrEx(x + GUI_THICKNESS + 2, y + (BOTTOMLINE_HEIGHT - menuFont.FontCode) / 2, style->strPtr_1, &menuFont,
	BOTTOMLINE_LEFT_WIDTH - GUI_THICKNESS * 2 - 4, ALIGN_CENTER, 1);
	/* 变更颜色 */
	menuFont.BackColor = BOTTOMLINE_COLOR_2;
	/* 显示右部分文字 */
	dispStrEx(x + BOTTOMLINE_LEFT_WIDTH + GUI_THICKNESS + 2, y + (BOTTOMLINE_HEIGHT - menuFont.FontCode) / 2, style->strPtr_2, &menuFont,
	BOTTOMLINE_WIDTH - BOTTOMLINE_LEFT_WIDTH - GUI_THICKNESS * 2 - 4, ALIGN_CENTER, 1);
}


void drawBottomLine(uint8_t layer)
{
	int16_t gap;
	uint16_t labelX = GUI_THICKNESS;
	uint16_t selectLab = 0x01 << bottomStruct.selected ;
	
	/* 设置标签间距 */
	gap = (myLcd.width - 1 - 2*GUI_THICKNESS - 4 * BOTTOMLINE_WIDTH) / 3;
	
	/* 绘制标签1 */
	GUI_drawLabel(labelX,	myLcd.height - 1 - GUI_THICKNESS - BOTTOMLINE_HEIGHT,	&(bottomStruct.label_1),	(selectLab>>1)&0x01,	1);
	/* 设置x位置 */
	labelX += gap + BOTTOMLINE_WIDTH;
	/* 绘制标签2 */
	GUI_drawLabel(labelX,	myLcd.height - 1 - GUI_THICKNESS - BOTTOMLINE_HEIGHT,	&(bottomStruct.label_2),	(selectLab>>2)&0x01,	1);
	/* 设置x位置 */
	labelX += gap + BOTTOMLINE_WIDTH;
	/* 绘制标签3 */
	GUI_drawLabel(labelX,	myLcd.height - 1 - GUI_THICKNESS - BOTTOMLINE_HEIGHT,	&(bottomStruct.label_3),	(selectLab>>3)&0x01,	1);
	/* 设置x位置 */
	labelX += gap + BOTTOMLINE_WIDTH;
	/* 绘制标签4 */
	GUI_drawLabel(labelX,	myLcd.height - 1 - GUI_THICKNESS - BOTTOMLINE_HEIGHT,	&(bottomStruct.label_4),	(selectLab>>4)&0x01,	1);	
}

void drawWelcomeWin(uint8_t layer)
{
	/* 绘制阴影 */
	fill_By_DMA2D(WELCOME_WINDOW_X + WELCOME_WINDOW_SHADOW_DISTANCE, WELCOME_WINDOW_Y + WELCOME_WINDOW_SHADOW_DISTANCE,
	WELCOME_WINDOW_WIDTH + WELCOME_WINDOW_SHADOW_DISTANCE,	WELCOME_WINDOW_HEIGHT + WELCOME_WINDOW_SHADOW_DISTANCE, WELCOME_WINDOW_COLOR_SHADOW, layer);
	/* 绘制显示区域 */
	fill_By_DMA2D(WELCOME_WINDOW_X, WELCOME_WINDOW_Y,
	WELCOME_WINDOW_WIDTH + WELCOME_WINDOW_SHADOW_DISTANCE,	WELCOME_WINDOW_HEIGHT + WELCOME_WINDOW_SHADOW_DISTANCE, WELCOME_WINDOW_COLOR_TOP, layer);
	/* 显示文字 */
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


