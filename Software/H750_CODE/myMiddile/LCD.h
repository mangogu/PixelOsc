#ifndef LCD_H
#define LCD_H

/**********************����**********************/
#include "stm32h7xx_hal.h"
#include "main.h"
#include "GPIO.h"
#include "LTDC.h"
#include "TIM.h"
#include "FONTS.h"
#include "string.h"

/**********************�궨��**********************/

/* ��Ļ���� */
#define LCD_TYPE_800_480

/* �Դ��ַ */
#define L1_GRAM_ADDR 0x24000000
#define L2_GRAM_ADDR 

/* RGB to HEXת�� */
#define RGB2HEX(r,g,b)  ((r << 16) | (g << 8) | (b))

extern uint32_t osc_color_table[256];
extern uint8_t Layer1Buffer[480*800];

/* ������ɫ */
#define WHITE 	0
#define BLACK 	1
#define RED			2
#define YELLOW	4
#define GREEN		5
#define BLUE		7
#define PURPLE	8
#define GREY_L 	9
#define RED_D		10


#define CL_MASK	0x9999	/* ��ɫ���룬�������ֱ���͸�� */

/* ������� */
typedef enum
{
	FC_ST_12 = 12,		/* ����12x12���� ����x�ߣ� */
	FC_ST_16 = 16,			/* ����15x16���� ����x�ߣ� */
	FC_ST_24 = 24,			/* ����24x24���� ����x�ߣ� -- ��ʱδ֧�� */
	FC_ST_32 = 32,			/* ����32x32���� ����x�ߣ� -- ��ʱδ֧�� */	
	
	FC_RA8875_16,		/* RA8875 �������� 16���� */
	FC_RA8875_24,		/* RA8875 �������� 24���� */
	FC_RA8875_32		/* RA8875 �������� 32���� */	
}FONTcode_E;

/* ���ֶ��뷽ʽ */
enum
{
	ALIGN_LEFT = 0,
	ALIGN_CENTER = 1,
	ALIGN_RIGHT = 2
};


/********************�ṹ������**********************/
struct LayerStructDef
{
	uint16_t width;			//����
	uint16_t height;		//��߶�
	
	uint16_t start_x;		//��x��ʼλ��
	uint16_t start_y;		//��y��ʼλ��
	
	uint8_t* LayerAddr;	//���Դ��ַ
};

struct LcdStructDef
{
	uint16_t width;			//��Ļ���
	uint16_t height;		//��Ļ�߶�
	uint8_t direction;	//��Ļ����
	
	struct LayerStructDef L1;		//��һ��
	struct LayerStructDef L2;		//�ڶ���	
}; 

/* �������Խṹ */
struct FontStructDef
{
	/* ������� FONTcode_E  */
	FONTcode_E FontCode;
	/* ������ɫ */
	uint16_t FrontColor;
	/* ���ֱ�����ɫ��͸�� */
	uint16_t BackColor;	
	/* ���ּ�࣬��λ = ���� */
	uint16_t Space;		
};


/**********************��������**********************/
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


