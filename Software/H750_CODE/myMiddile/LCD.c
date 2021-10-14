/**********************����**********************/
#include "LCD.h"

/********************ȫ�ֱ���********************/

/* ����ɫ�ʱ� */
const uint32_t osc_color_table[256] = COLOR_TABLE_L8;

/* ������ʹ�õĵ���Ļ */
#ifdef LCD_TYPE_800_480
/* �����Դ��ַ */
uint8_t Layer1Buffer[480*800] __attribute__((at(L1_GRAM_ADDR)));
struct LcdStructDef myLcd = 
{
	/* ���ÿ��� */
	.width = 800,
	.height = 480,
	/* ��Ļ���� */
	.direction =  0,
	
	
	.L1.start_x = 0,
	.L1.start_y = 0,
	.L1.width = 800,
	.L1.height = 480,
	.L1.LayerAddr = Layer1Buffer
};
#endif

/********************��������********************/

/* ��ʼ��LCD */
void Lcd_Init(void)
{
	/* ��ʼ��LTDC */
  MX_LTDC_Init();
  
	/* ������Ļ���� */
	TIM_LcdBright_Init(DEFAULT_BRIGHT);
	
	/* ����LCD���� */
	setLcdDirection(1);
	
	/* ʹ��DMA2Dʱ�� */
	__HAL_RCC_DMA2D_CLK_ENABLE();
	
	/* �����Ļ */
	clearLcd(BLACK, 1);
}

/*
*********************************************************************************************************
*	�� �� ��: setLcdDirection
*	����˵��: ����LCD����
*	��    ��:
*			dir			: ���������0:������ 1:������ 2:������ 3:��������
*			�� �� ֵ: ��
*********************************************************************************************************
*/
void setLcdDirection(uint8_t dir)
{
	myLcd.direction = dir;
}

/*
*********************************************************************************************************
*	�� �� ��: setPixel
*	����˵��: ��1������
*	��    ��:
*			x,y 		: ��������
*			color  	: ������ɫ ( RGB = L8 ��ʽ)
*			layer		: ��
*			�� �� ֵ: ��
*********************************************************************************************************
*/
void setPixel(uint16_t x, 		
							uint16_t y, 		
							uint8_t color, 	
							uint8_t layer)	
{
	uint16_t temp;
	if(myLcd.direction == 0)
	{
		
	}
	else if(myLcd.direction == 1)
	{
		x = myLcd.width - x;
		y = myLcd.height -y;
	}
	else if(myLcd.direction == 2)
	{
		temp = y;
		y = myLcd.height - x;
		x = temp;
	}
	else if(myLcd.direction == 3)
	{
		temp = y;
		y = x;
		x = myLcd.width - temp;
	}
		
	if(layer == 1)
	{
		myLcd.L1.LayerAddr[y * myLcd.L1.width + x] = color;
	}
	else if(layer == 2)
	{
		myLcd.L2.LayerAddr[y * myLcd.L2.width + x] = color;
	}
	
}

/*
*********************************************************************************************************
*	�� �� ��: drawLine
*	����˵��: ���� Bresenham �㷨����2��仭һ��ֱ�ߡ�
*	��    ��:
*			start_x, start_y : ��ʼ������
*			end_x, end_y : ��ֹ��Y����
*			color     : ��ɫ
*			layer			:	��
*			�� �� ֵ	: ��
*********************************************************************************************************
*/
void drawLine(uint16_t start_x , 
							uint16_t start_y , 
							uint16_t end_x , 
							uint16_t end_y , 
							uint8_t color,
							uint8_t layer)
{
	int32_t dx , dy ;
	int32_t tx , ty ;
	int32_t inc1 , inc2 ;
	int32_t d , iTag ;
	int32_t x , y ;

	/* ���� Bresenham �㷨����2��仭һ��ֱ�� */

	setPixel(start_x , start_y , color, layer);

	/* ��������غϣ���������Ķ�����*/
	if ( start_x == end_x && start_y == end_y )
	{
		return;
	}

	iTag = 0 ;
	/* dx = abs ( end_x - start_x ); */
	if (end_x >= start_x)
	{
		dx = end_x - start_x;
	}
	else
	{
		dx = start_x - end_x;
	}

	/* dy = abs ( end_y - start_y ); */
	if (end_y >= start_y)
	{
		dy = end_y - start_y;
	}
	else
	{
		dy = start_y - end_y;
	}

	if ( dx < dy )   /*���dyΪ�Ƴ������򽻻��ݺ����ꡣ*/
	{
		uint16_t temp;

		iTag = 1 ;
		temp = start_x; start_x = start_y; start_y = temp;
		temp = end_x; end_x = end_y; end_y = temp;
		temp = dx; dx = dy; dy = temp;
	}
	tx = end_x > start_x ? 1 : -1 ;    /* ȷ������1���Ǽ�1 */
	ty = end_y > start_y ? 1 : -1 ;
	x = start_x ;
	y = start_y ;
	inc1 = 2 * dy ;
	inc2 = 2 * ( dy - dx );
	d = inc1 - dx ;
	while ( x != end_x )     /* ѭ������ */
	{
		if ( d < 0 )
		{
			d += inc1 ;
		}
		else
		{
			y += ty ;
			d += inc2 ;
		}
		if ( iTag )
		{
			setPixel(y , x , color, layer);
		}
		else
		{
			setPixel(x , y , color, layer);
		}
		x += tx ;
	}	
}


/*
*********************************************************************************************************
*	�� �� ��: drawPoints
*	����˵��: ���� Bresenham �㷨������һ��㣬������Щ�����������������ڲ�����ʾ��
*	��    ��:
*			x, y  	: ��������
*			size		: �����С
*			color 	: ��ɫ
*			layer 	: ��
*			�� �� ֵ: ��
*********************************************************************************************************
*/
void drawPoints(uint16_t *x, uint16_t *y, uint16_t size, uint8_t color, uint8_t layer)
{
	uint16_t i;

	for (i = 0 ; i < size - 1; i++)
	{
		drawLine(x[i], y[i], x[i + 1], y[i + 1], color, layer);
	}
}


/*
*********************************************************************************************************
*	�� �� ��: drawHLine
*	����˵��: ����һ��ˮƽ��
*	��    ��:
*			x1, y1 		: ��ʼ������
*			len    		: �ߵĳ���
*			color  		: ��ɫ
*			�� �� ֵ	: ��
*********************************************************************************************************
*/
void drawHLine(uint16_t x, uint16_t y, uint16_t len , uint8_t color, uint8_t layer)
{
	uint16_t i;
	
	for (i = 0; i < len; i++)
	{	
		setPixel(x + i , y , color, layer);
	}
}

/*
*********************************************************************************************************
*	�� �� ��: drawVLine
*	����˵��: ����һ����ֱ��
*	��    ��:
*			x, y : 		 ��ʼ������
*			len  : 		 �ߵĳ���
*			color: 		 ��ɫ
*			�� �� ֵ : ��
*********************************************************************************************************
*/
void drawVLine(uint16_t x , uint16_t y , uint16_t len , uint8_t color, uint8_t layer)
{
	uint16_t i;
	
	for (i = 0; i < len; i++)
	{	
		setPixel(x, y + i, color, layer);
	}	
}

/*
*********************************************************************************************************
*	�� �� ��: drawRect
*	����˵��: ����ˮƽ���õľ��Ρ�
*	��    ��:
*			x,y			: �������Ͻǵ�����
*			height 	: ���εĸ߶�
*			width  	: ���εĿ��
*			�� �� ֵ: ��
*********************************************************************************************************
*/
void drawRect(uint16_t x, uint16_t y,  uint16_t width, uint16_t height, uint8_t color, uint8_t layer)
{
	/*
	 ---------------->---
	|(x��y)        			 |
	V                    V  height
	|                    |
	 ---------------->---
		  width
	*/
	drawHLine(x, y, width, color, layer);
	drawVLine(x + width - 1, y, height, color, layer);
	drawHLine(x, y + height - 1, width, color, layer);
	drawVLine(x, y, height, color, layer);
}

/*
*********************************************************************************************************
*	�� �� ��: drawCircle
*	����˵��: ����һ��Բ���ʿ�Ϊ1������
*	��    ��:
*			x,y  		: Բ�ĵ�����
*			radius  : Բ�İ뾶
*			layer		: ��
*			�� �� ֵ: ��
*********************************************************************************************************
*/
void drawCircle(uint16_t x, uint16_t y, uint16_t radius, uint8_t color, uint8_t layer)
{
	int32_t  D;			/* Decision Variable */
	uint32_t  CurX;		/* ��ǰ X ֵ */
	uint32_t  CurY;		/* ��ǰ Y ֵ */

	D = 3 - (radius << 1);
	CurX = 0;
	CurY = radius;

	while (CurX <= CurY)
	{
		setPixel(x + CurX, y + CurY, color, layer);
		setPixel(x + CurX, y - CurY, color, layer);
		setPixel(x - CurX, y + CurY, color, layer);
		setPixel(x - CurX, y - CurY, color, layer);
		setPixel(x + CurY, y + CurX, color, layer);
		setPixel(x + CurY, y - CurX, color, layer);
		setPixel(x - CurY, y + CurX, color, layer);
		setPixel(x - CurY, y - CurX, color, layer);

		if (D < 0)
		{
			D += (CurX << 2) + 6;
		}
		else
		{
			D += ((CurX - CurY) << 2) + 10;
			CurY--;
		}
		CurX++;
	}
}

/*
*********************************************************************************************************
*	�� �� ��: fill_By_DMA2D
*	����˵��: DMA2D��ɫ��书��
*	��    ��: x, y          ���Ͻ�����
*           xSize         ɫ��X���С����ÿ��������
*           ySize         ɫ��Y���С��������
*           color			    ɫ����ɫֵ����ɫ��ʽ = L8��
*           layer			   	��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void fill_By_DMA2D(	uint16_t x,
										uint16_t y,
										uint16_t xSize, 
										uint16_t ySize,  
										uint8_t color,
										uint8_t layer) 
{
	uint16_t offline;
	uint32_t dstAddr;
	uint16_t color_565 = (color << 8 | color);
	uint16_t temp;
	
	if(x%2 == 1)
	{
		x++;
		xSize--;
	}
	if(xSize%2 == 1)
	{
		xSize--;
	}
	
	/* �ж���Ļ���� */
	if(myLcd.direction == 0)
	{
		
	}
	else if(myLcd.direction == 1)
	{
		x = myLcd.width - x - xSize;
		y = myLcd.height - y - ySize;
	}
	else if(myLcd.direction == 2)
	{
		temp = y;
		y = myLcd.height - x - xSize;
		x = temp;
		
		temp = xSize;
		xSize = ySize;
		ySize = temp;
	}
	else if(myLcd.direction == 3)
	{
		temp = y;
		y = x;
		x = myLcd.width - temp - ySize;
		
		temp = xSize;
		xSize = ySize;
		ySize = temp;
	}
	
	/* ѡ������ */
	if(layer == 1)
	{
		/* L8��ʽ��ɫ��Ҫ/2 */
		offline = (myLcd.L1.width - xSize)/2;
		dstAddr = L1_GRAM_ADDR + y * myLcd.L1.width + x;
		
	}
	else if(layer == 2)
	{
		/* L8��ʽ��ɫ��Ҫ/2 */
		offline = (myLcd.L2.width - xSize)/2;
		dstAddr = L2_GRAM_ADDR + y * myLcd.L2.width + x;
	}
	
	/* DMA2D���üĴ������洢��ģʽ, ����ģʽ�ò���ǰ����ͱ����� */  
	DMA2D->CR      = DMA2D_R2M;
	DMA2D->OCOLR   = color_565;
	DMA2D->OMAR    = (uint32_t)dstAddr;
	DMA2D->OOR     = offline;
	DMA2D->OPFCCR  = LTDC_PIXEL_FORMAT_RGB565;
	DMA2D->NLR     = (uint32_t)((xSize/2) << 16) | (uint16_t)ySize;

	/* �������� */
	DMA2D->CR   |= DMA2D_CR_START;   

	/* �ȴ�DMA2D������� */
	while (DMA2D->CR & DMA2D_CR_START) {} 
}


void clearLcd(uint8_t color, uint8_t layer)
{
	/* �ж���Ļ����Ͳ� */
	if(layer == 1 && (myLcd.direction == 0 ||myLcd.direction == 1))
	{
		fill_By_DMA2D(myLcd.L1.start_x, myLcd.L1.start_y, myLcd.L1.width, myLcd.L1.height, color, layer);
	}
	else if(layer == 1 && (myLcd.direction == 2 ||myLcd.direction == 3))
	{
		fill_By_DMA2D(myLcd.L1.start_x, myLcd.L1.start_y, myLcd.L1.height, myLcd.L1.width, color, layer);
	}
	else if(layer == 2 && (myLcd.direction == 0 ||myLcd.direction == 1))
	{
		fill_By_DMA2D(myLcd.L2.start_x, myLcd.L2.start_y, myLcd.L2.width, myLcd.L2.height, color, layer);
	}
	else if(layer == 2 && (myLcd.direction == 2 ||myLcd.direction == 3))
	{
		fill_By_DMA2D(myLcd.L2.start_x, myLcd.L2.start_y, myLcd.L2.height, myLcd.L2.width, color, layer);
	}
}

/*
*********************************************************************************************************
*	�� �� ��: getFontWidth
*	����˵��: ��ȡ����Ŀ�ȣ����ص�λ)
*	��    ��:
*		fontStruct : ����ṹ�壬������ɫ������ɫ(֧��͸��)��������롢���ּ��Ȳ���
*	�� �� ֵ: ����Ŀ�ȣ����ص�λ)
*********************************************************************************************************
*/
uint16_t getFontWidth(struct FontStructDef *fontStruct)
{
	uint16_t fontWidth = 16;

	switch (fontStruct->FontCode)
	{
		case FC_ST_12:
			fontWidth = 12;
			break;

		case FC_ST_16:
		case FC_RA8875_16:			
			fontWidth = 16;
			break;
			
		case FC_RA8875_24:			
		case FC_ST_24:
			fontWidth = 24;
			break;
			
		case FC_ST_32:
		case FC_RA8875_32:	
			fontWidth = 32;
			break;			
	}
	return fontWidth;
}

/*
*********************************************************************************************************
*	�� �� ��: getFontHeight
*	����˵��: ��ȡ����ĸ߶ȣ����ص�λ)
*	��    ��:
*		fontStruct : ����ṹ�壬������ɫ������ɫ(֧��͸��)��������롢���ּ��Ȳ���
*	�� �� ֵ: ����Ŀ�ȣ����ص�λ)
*********************************************************************************************************
*/
uint16_t getFontHeight(struct FontStructDef *fontStruct)
{
	uint16_t height = 16;

	switch (fontStruct->FontCode)
	{
		case FC_ST_12:
			height = 12;
			break;

		case FC_ST_16:
		case FC_RA8875_16:			
			height = 16;
			break;
			
		case FC_RA8875_24:			
		case FC_ST_24:
			height = 24;
			break;
			
		case FC_ST_32:
		case FC_RA8875_32:	
			height = 32;
			break;			
	}
	return height;
}

/*
*********************************************************************************************************
*	�� �� ��: getStrWidth
*	����˵��: �����ַ������(���ص�λ)
*	��    ��:
*		strPtr  : �ַ���ָ��
*		fontStruct : ����ṹ�壬������ɫ������ɫ(֧��͸��)��������롢���ּ��Ȳ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
uint16_t getStrWidth(char *strPtr, struct FontStructDef *fontStruct)
{
	char *p = strPtr;
	uint16_t width = 0;
	uint8_t code1, code2;
	uint16_t fontWidth;

	fontWidth = getFontWidth(fontStruct);

	while (*p != 0)
	{
		code1 = *p;	/* ��ȡ�ַ������ݣ� �����ݿ�����ascii���룬Ҳ���ܺ��ִ���ĸ��ֽ� */
		if (code1 < 0x80)	/* ASCII */
		{
			switch(fontStruct->FontCode)
			{
				case FC_RA8875_16:
					fontWidth = g_RA8875_Ascii16_width[code1 - 0x20];
					break;
				
				case FC_RA8875_24:
					fontWidth = g_RA8875_Ascii24_width[code1 - 0x20];
					break;
				
				case FC_RA8875_32:
					fontWidth = g_RA8875_Ascii32_width[code1 - 0x20];
					break;
				
				case FC_ST_12:
					fontWidth = 6;
					break;

				case FC_ST_16:		
					fontWidth = 8;
					break;
					
				case FC_ST_24:			
					fontWidth = 12;
					break;
					
				case FC_ST_32:
					fontWidth = 16;
					break;
				
				default:
					fontWidth = 8;
					break;					
			}
			
		}
		else	/* ���� */
		{
			code2 = *++p;
			if (code2 == 0)
			{
				break;
			}
			fontWidth = getFontWidth(fontStruct);
			
		}
		width += fontWidth;
		p++;
	}

	return width;
}

/*
*********************************************************************************************************
*        �� �� ��: readAsciiDot
*        ����˵��: ��ȡ1��ASCII�ַ��ĵ�������
*        ��    ��:
*                code : ASCII�ַ��ı��룬1�ֽڡ�1-128
*                fontCode ���������
*                strBuff : ��Ŷ������ַ���������
*        �� �� ֵ: ���ֿ��
*********************************************************************************************************
*/
static void readAsciiDot(uint8_t code, uint8_t fontCode, uint8_t *strBuff)
{
        const uint8_t *pAscDot;
        uint8_t fontBytes = 0;
        uint16_t m;
        uint16_t address;
        uint8_t fAllHz = 0;        /* 1��ʾ��������Ƕȫ����ASCII�ַ��� */

        pAscDot = 0;
        switch (fontCode)
        {
                case FC_ST_12:                /* 12���� */
                        fontBytes = 24 / 2;
                        pAscDot = g_Ascii12;        
                        fAllHz = 1;
                        break;
               
                case FC_ST_16:
                        /* ȱʡ��16���� */
                        fontBytes = 32 / 2;
                        pAscDot = g_Ascii16;
                        fAllHz = 1;
                        break;
               
                case FC_ST_24:
                        fontBytes = 48;
                        pAscDot = g_Ascii24;
                        break;
               
                case FC_ST_32:
                        fontBytes = 64;
                        pAscDot = g_Ascii32;
                        break;
               
                default:
                        return;
        }        

        if (fAllHz == 1)        /* ��Ƕȫ��ASCII�ַ����� */
        {
                /* ��CPU�ڲ�Flash�е�ascii�ַ������Ƶ�buf */
                memcpy(strBuff, &pAscDot[code * (fontBytes)], (fontBytes));               
        }
        else        /* ��Ƕ�����ַ�����ģ�������ֽ���ASCII�� */
        {
                m = 0;
                while(1)
                {
                   address = m * (fontBytes + 1);
                   m++;
                   if (code == pAscDot[address + 0])
                   {
                          address += 1;
                          memcpy(strBuff, &pAscDot[address], fontBytes);
                          break;
                   }
                   else if ((pAscDot[address + 0] == 0xFF) && (pAscDot[address + 1] == 0xFF))
                   {
                          /* �ֿ�������ϣ�δ�ҵ��������ȫFF */
                          memset(strBuff, 0xFF, fontBytes);
                          break;
                   }           
           }
   }
}

/*
*********************************************************************************************************
*	�� �� ��: readHZDot
*	����˵��: ��ȡ1�����ֵĵ�������
*	��    ��:
*		code1, _cod2 : ��������. GB2312����
*		fontCode ���������
*		strBuff : ��Ŷ������ַ���������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void readHZDot(uint8_t code1, uint8_t code2,  uint8_t fontCode, uint8_t *strBuff)
{
	#ifdef USE_SMALL_FONT	/* ʹ��CPU �ڲ�Flash С�ֿ� */
		uint8_t *pDot;
		uint8_t fontBytes = 0;
		uint32_t address;
		uint16_t m;

		pDot = 0;	/* �������ڱ���澯 */
		switch (fontCode)
		{
			case FC_ST_12:		/* 12���� */
				fontBytes = 24;
				pDot = (uint8_t *)g_Hz12;	
				break;
			
			case FC_ST_16:
				fontBytes = 32;
				pDot = (uint8_t *)g_Hz16;
				break;
	
			case FC_ST_24:
				fontBytes = 72;
				pDot = (uint8_t *)g_Hz24;
				break;			
				
			case FC_ST_32:	
				fontBytes = 128;
				pDot = (uint8_t *)g_Hz32;
				break;						
			
			case FC_RA8875_16:
			case FC_RA8875_24:
			case FC_RA8875_32:
				return;
		}	

		m = 0;
		while(1)
		{
			address = m * (fontBytes + 2);
			m++;
			if ((code1 == pDot[address + 0]) && (code2 == pDot[address + 1]))
			{
				address += 2;
				memcpy(strBuff, &pDot[address], fontBytes);
				break;
			}
			else if ((pDot[address + 0] == 0xFF) && (pDot[address + 1] == 0xFF))
			{
				/* �ֿ�������ϣ�δ�ҵ��������ȫFF */
				memset(strBuff, 0xFF, fontBytes);
				break;
			}
		}
	#else	/* ��ȫ�ֿ� */
		uint8_t *pDot = 0;
		uint8_t fontBytes = 0;
			
		switch (fontCode)
		{
			case FC_ST_12:		/* 12���� */
				fontBytes = 24;
				pDot = (uint8_t *)HZK12_ADDR;	
				break;
			
			case FC_ST_16:
				fontBytes = 32;
				pDot = (uint8_t *)HZK16_ADDR;
				break;
	
			case FC_ST_24:
				fontBytes = 72;
				pDot = (uint8_t *)HZK24_ADDR;
				break;			
				
			case FC_ST_32:	
				fontBytes = 128;
				pDot = (uint8_t *)HZK32_ADDR;
				break;						
			
			case FC_RA8875_16:
			case FC_RA8875_24:
			case FC_RA8875_32:
				return;
		}			
	
		/* �˴���Ҫ�����ֿ��ļ����λ�ý����޸� */
		if (code1 >=0xA1 && code1 <= 0xA9 && code2 >=0xA1)
		{
			pDot += ((code1 - 0xA1) * 94 + (code2 - 0xA1)) * fontBytes;
		}
		else if (code1 >=0xB0 && code1 <= 0xF7 && code2 >=0xA1)
		{
			pDot += ((code1 - 0xB0) * 94 + (code2 - 0xA1) + 846) * fontBytes;
		}
		memcpy(strBuff, pDot, fontBytes);
        //Flash_ReadBuffer((uint8_t *)strBuff, (uint32_t)pDot, fontBytes);
	#endif
}

/*
*********************************************************************************************************
*	�� �� ��: LCD_DispStrEx
*	����˵��: ��LCDָ�����꣨���Ͻǣ���ʾһ���ַ����� ��ǿ�ͺ�����֧����\��\�Ҷ��룬֧�ֶ���������
*	��    ��:
*		x : X����
*		y : Y����
*		strPtr  : �ַ���ָ��
*		fontStruct : ����ṹ�壬������ɫ������ɫ(֧��͸��)��������롢���ּ��Ȳ���������ָ��RA8875�ֿ���ʾ����
*		width : �ַ�����ʾ����Ŀ��. 0 ��ʾ�������������򣬴�ʱ_Align��Ч
*		_Align :�ַ�������ʾ����Ķ��뷽ʽ��
*				ALIGN_LEFT = 0,
*				ALIGN_CENTER = 1,
*				ALIGN_RIGHT = 2
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void dispStrEx(uint16_t x, uint16_t y, char *strPtr, struct FontStructDef *fontStruct, uint16_t width, uint8_t _Align, uint8_t layer)
{
        uint32_t i;
        uint8_t code1;
        uint8_t code2;
        uint8_t buf[32 * 32 / 8];        /* ���֧��32������ */
        uint8_t width_1;
        uint16_t m;
        uint8_t fontWidth = 0;
        uint8_t fontHeight = 0;
        uint16_t x_1, y_1;
        uint16_t offset;
        uint16_t strWidth;        /* �ַ���ʵ�ʿ��  */
        
        uint8_t line_bytes;
        uint8_t asc_bytes = 0;
        uint8_t hz_bytes = 0;

        switch (fontStruct->FontCode)
        {
                case FC_ST_12:                /* 12���� */
                        fontHeight = 12;
                        fontWidth = 12;
                        asc_bytes = 1;
                        hz_bytes = 2;
                        break;
               
                case FC_ST_16:
                        fontHeight = 16;
                        fontWidth = 16;
                        asc_bytes = 1;
                        hz_bytes = 2;
                        break;

                case FC_ST_24:
                        fontHeight = 24;
                        fontWidth = 24;
                        asc_bytes = 2;
                        hz_bytes = 3;
                        break;
                                                
                case FC_ST_32:        
                        fontHeight = 32;
                        fontWidth = 32;
                        asc_bytes = 2;
                        hz_bytes = 4;
                        break;

                case FC_RA8875_16: 		
                case FC_RA8875_24: 		
                case FC_RA8875_32: 		   
                     break;                
        }
        
        strWidth = getStrWidth(strPtr, fontStruct);        /* �����ַ���ʵ�ʿ��(RA8875�ڲ�ASCII������Ϊ�䳤 */
        offset = 0;
        if (width > strWidth)
        {
                if (_Align == ALIGN_RIGHT)        /* �Ҷ��� */
                {
                        offset = width - strWidth;
                }
                else if (_Align == ALIGN_CENTER)        /* ����� */
                {
                        offset = (width - strWidth) / 2;
                }
                else        /* ����� ALIGN_LEFT */
                {
                        ;
                }
        }

        /* ������ɫ, �м������ұ߶���  */
        if (offset > 0)
        {
					fill_By_DMA2D(x, y, offset, getFontHeight(fontStruct), fontStruct->BackColor, 1);
					x += offset;
        }
        
        /* �Ҳ����ɫ */
        if (width > strWidth)
        {
					fill_By_DMA2D(x + strWidth,y,width - strWidth - offset,getFontHeight(fontStruct),fontStruct->BackColor,1);
				}
        
        /* ʹ��CPU�ڲ��ֿ�. ������Ϣ��CPU��ȡ */
        {
                /* ��ʼѭ�������ַ� */
                while (*strPtr != 0)
                {
                        code1 = *strPtr;        /* ��ȡ�ַ������ݣ� �����ݿ�����ascii���룬Ҳ���ܺ��ִ���ĸ��ֽ� */
                        if (code1 < 0x80)
                        {
                                /* ��ascii�ַ������Ƶ�buf */
                                readAsciiDot(code1, fontStruct->FontCode, buf);        /* ��ȡASCII�ַ����� */
                                width_1 = fontWidth / 2;
                                line_bytes = asc_bytes;
                        }
                        else
                        {
                                code2 = *++strPtr;
                                if (code2 == 0)
                                {
                                        break;
                                }
                                /* ��1�����ֵĵ��� */
                                readHZDot(code1, code2, fontStruct->FontCode, buf);
                                width_1 = fontWidth;
                                line_bytes = hz_bytes;
                        }
        
                        y_1 = y;
                        /* ��ʼˢLCD */
                        for (m = 0; m < fontHeight; m++)        /* �ַ��߶� */
                        {
                                x_1 = x;
                                for (i = 0; i < width_1; i++)        /* �ַ���� */
                                {
                                        if ((buf[m * line_bytes + i / 8] & (0x80 >> (i % 8 ))) != 0x00)
                                        {
																						setPixel(x_1, y_1, fontStruct->FrontColor, layer);
                                        }
                                        else
                                        {
                                                if (fontStruct->BackColor != CL_MASK)        /* ͸��ɫ */
                                                {
																									setPixel(x_1, y_1, fontStruct->BackColor, layer);
                                                        //LCD_PutPixel(x, y, fontStruct->BackColor);        /* ����������ɫΪ���ֱ���ɫ */
                                                }
                                        }
        
                                        x_1++;
                                }
                                y_1++;
                        }
        
                        if (fontStruct->Space > 0)
                        {
                                /* ������ֵ�ɫ��fontStruct->usBackColor�������ּ����ڵ���Ŀ�ȣ���ô��Ҫ������֮�����(��ʱδʵ��) */
                        }
                        x += width_1 + fontStruct->Space;        /* �е�ַ���� */
                        strPtr++;                        /* ָ����һ���ַ� */
                }
        }
}

