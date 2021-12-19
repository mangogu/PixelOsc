#ifndef LCD_H
#define LCD_H

/**********************包含**********************/
#include "stm32h7xx_hal.h"
#include "main.h"
#include "GPIO.h"
#include "LTDC.h"
#include "TIM.h"
#include "FONTS.h"
#include "string.h"

/**********************宏定义**********************/

/* 屏幕种类 */
#define LCD_TYPE_800_480

/* 显存地址 */
#define L1_GRAM_ADDR 0x24000000
#define L2_GRAM_ADDR 

/* RGB to HEX转换 */
#define RGB2HEX(r,g,b)  ((r << 16) | (g << 8) | (b))

extern uint32_t osc_color_table[256];
extern uint8_t Layer1Buffer[480*800];

/* 常用颜色 */
#define WHITE 	0
#define BLACK 	1
#define RED			2
#define YELLOW	4
#define GREEN		5
#define BLUE		7
#define PURPLE	8
#define GREY_L 	9
#define RED_D		10


#define CL_MASK	0x9999	/* 颜色掩码，用于文字背景透明 */

/* 字体代码 */
typedef enum
{
	FC_ST_12 = 12,		/* 宋体12x12点阵 （宽x高） */
	FC_ST_16 = 16,			/* 宋体15x16点阵 （宽x高） */
	FC_ST_24 = 24,			/* 宋体24x24点阵 （宽x高） -- 暂时未支持 */
	FC_ST_32 = 32,			/* 宋体32x32点阵 （宽x高） -- 暂时未支持 */	
	
	FC_RA8875_16,		/* RA8875 内置字体 16点阵 */
	FC_RA8875_24,		/* RA8875 内置字体 24点阵 */
	FC_RA8875_32		/* RA8875 内置字体 32点阵 */	
}FONTcode_E;

/* 文字对齐方式 */
enum
{
	ALIGN_LEFT = 0,
	ALIGN_CENTER = 1,
	ALIGN_RIGHT = 2
};


/********************结构体声明**********************/
struct LayerStructDef
{
	uint16_t width;			//层宽度
	uint16_t height;		//层高度
	
	uint16_t start_x;		//层x起始位置
	uint16_t start_y;		//层y起始位置
	
	uint8_t* LayerAddr;	//层显存地址
};

struct LcdStructDef
{
	uint16_t width;			//屏幕宽度
	uint16_t height;		//屏幕高度
	uint8_t direction;	//屏幕方向
	
	struct LayerStructDef L1;		//第一层
	struct LayerStructDef L2;		//第二层	
}; 

/* 字体属性结构 */
struct FontStructDef
{
	/* 字体代码 FONTcode_E  */
	FONTcode_E FontCode;
	/* 字体颜色 */
	uint16_t FrontColor;
	/* 文字背景颜色，透明 */
	uint16_t BackColor;	
	/* 文字间距，单位 = 像素 */
	uint16_t Space;		
};


/**********************函数声明**********************/
void Lcd_Init(void);
void setPixel(uint16_t x, 		
							uint16_t y, 	
							uint8_t color, 
							uint8_t layer);			
void drawLine(uint16_t start_x , 
							uint16_t start_y , 
							uint16_t end_x , 
							uint16_t end_y , 
							uint8_t color,
							uint8_t layer);
void fill_By_DMA2D(	uint16_t x,
										uint16_t y,
										uint16_t xSize, 
										uint16_t ySize,  
										uint8_t color,
										uint8_t layer);
void drawCircle(uint16_t x, uint16_t y, uint16_t radius, uint8_t color, uint8_t layer);
void setLcdDirection(uint8_t dir);
void drawPoints(uint16_t *x, uint16_t *y, uint16_t size, uint8_t color, uint8_t layer);	
void drawHLine(uint16_t x, uint16_t y, uint16_t _usLen , uint8_t color, uint8_t layer);
void drawVLine(uint16_t x , uint16_t y , uint16_t _usLen , uint8_t color, uint8_t layer);
void drawRect(uint16_t x, uint16_t y,  uint16_t width, uint16_t height, uint8_t color, uint8_t layer);
void clearLcd(uint8_t color, uint8_t layer);
void dispStrEx(uint16_t x, uint16_t y, char *strPtr, struct FontStructDef *fontStruct, uint16_t _Width,
        uint8_t _Align, uint8_t layer);
static void readHZDot(uint8_t code1, uint8_t code2,  uint8_t fontCode, uint8_t *strBuff);
static void readAsciiDot(uint8_t code, uint8_t fontCode, uint8_t *strBuff);
uint16_t getStrWidth(char *strPtr, struct FontStructDef *fontStruct);
uint16_t getFontHeight(struct FontStructDef *fontStruct);
uint16_t getFontWidth(struct FontStructDef *fontStruct);

#endif


