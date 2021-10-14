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

//ɫ�ʱ�
#define COLOR_TABLE_L8         	 \
{                              	 \
	RGB2HEX(255, 255, 255),   /* 0  ��*/\
	RGB2HEX(0, 0, 0),         /* 1  ��*/\
	RGB2HEX(255, 0, 0),     	/* 2  ��*/\
	RGB2HEX(255, 165, 0),     /* 3  ��*/\
	RGB2HEX(255, 255, 0),     /* 4  ��*/\
	RGB2HEX(0, 255, 0),     	/* 5  ��*/\
	RGB2HEX(0, 127, 255),     /* 6  ��*/\
	RGB2HEX(0, 0, 255),       /* 7  ��*/\
	RGB2HEX(139,  0,255),     /* 8  ��*/\
	RGB2HEX(150,150,150),     /* 9  ǳ��*/\
	RGB2HEX(180,85,85),       /* 10 ����*/\
	RGB2HEX(255,255,7),       /* 11 */\
	RGB2HEX(255,255,7),       /* 12 */\
	RGB2HEX(255,255,7),       /* 13 */\
	RGB2HEX(255,255,7),       /* 14 */\
	RGB2HEX(3,227,231),       /* 15 */\
	RGB2HEX(3,227,231),       /* 16 */\
	RGB2HEX(3,227,231),       /* 17 */\
	RGB2HEX(3,227,231),       /* 18 */\
	RGB2HEX(3,227,231),       /* 19 */\
	RGB2HEX(3,227,231),       /* 20 */\
	RGB2HEX(195, 195, 199),   /* 21 */\
	RGB2HEX(3, 3, 7),         /* 22 */\
	RGB2HEX(255,1,1),         /* 23 */\
	RGB2HEX(0,255,0),         /* 24 */\
	RGB2HEX(231,131,87),      /* 25 */\
	RGB2HEX(0,255,0),         /* 26 */\
	RGB2HEX(240,11,205),      /* 27 */\
	RGB2HEX(0,255,0),         /* 28 */\
	RGB2HEX(0,255,0),         /* 29 */\
	RGB2HEX(0,255,0),         /* 30 */\
	RGB2HEX(0,255,0),         /* 31 */\
	RGB2HEX(0,255,0),         /* 32 */\
	RGB2HEX(0,255,0),         /* 33 */\
	RGB2HEX(0,0,255),         /* 34 */\
	RGB2HEX(0,0,255),         /* 35 */\
	RGB2HEX(0,0,255),         /* 36 */\
	RGB2HEX(0,0,255),         /* 37 */\
	RGB2HEX(0,0,255),         /* 38 */\
	RGB2HEX(0,0,255),         /* 39 */\
	RGB2HEX(255,0,0),         /* 40 */\
	RGB2HEX(255,0,0),         /* 41 */\
	RGB2HEX(255,0,0),         /* 42 */\
	RGB2HEX(255,0,0),         /* 43 */\
	RGB2HEX(255,0,0),         /* 44 */\
	RGB2HEX(255,0,0),         /* 45 */\
	RGB2HEX(255,255,0),       /* 46 */\
	RGB2HEX(255,255,0),       /* 47 */\
	RGB2HEX(3,227,231),       /* 48 */\
	RGB2HEX(3,227,231),       /* 49 */\
	RGB2HEX(7, 3, 7),         /* 50 */\
	RGB2HEX(7, 3, 7),         /* 51 */\
	RGB2HEX(25, 206, 12),     /* 52 */\
	RGB2HEX(25, 206, 12),     /* 53 */\
	RGB2HEX(25, 206, 12),     /* 54 */\
	RGB2HEX(25, 206, 12),     /* 55 */\
	RGB2HEX(251, 3, 9),       /* 56 */\
	RGB2HEX(251, 3, 9),       /* 57 */\
	RGB2HEX(251, 3, 9),       /* 58 */\
	RGB2HEX(251, 3, 9),       /* 59 */\
}

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


