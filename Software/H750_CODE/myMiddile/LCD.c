/**********************包含**********************/
#include "LCD.h"

/********************全局变量********************/

/* 定义色彩表 */
const uint32_t osc_color_table[256] = COLOR_TABLE_L8;

/* 定义所使用的的屏幕 */
#ifdef LCD_TYPE_800_480
/* 定义显存地址 */
uint8_t Layer1Buffer[480*800] __attribute__((at(L1_GRAM_ADDR)));
struct LcdStructDef myLcd = 
{
	/* 配置宽、高 */
	.width = 800,
	.height = 480,
	/* 屏幕方向 */
	.direction =  0,
	
	
	.L1.start_x = 0,
	.L1.start_y = 0,
	.L1.width = 800,
	.L1.height = 480,
	.L1.LayerAddr = Layer1Buffer
};
#endif

/********************函数定义********************/

/* 初始化LCD */
void Lcd_Init(void)
{
	/* 初始化LTDC */
  MX_LTDC_Init();
  
	/* 开启屏幕背光 */
	TIM_LcdBright_Init(DEFAULT_BRIGHT);
	
	/* 设置LCD方向 */
	setLcdDirection(1);
	
	/* 使能DMA2D时钟 */
	__HAL_RCC_DMA2D_CLK_ENABLE();
	
	/* 清空屏幕 */
	clearLcd(BLACK, 1);
}

/*
*********************************************************************************************************
*	函 数 名: setLcdDirection
*	功能说明: 设置LCD方向
*	形    参:
*			dir			: 方向参数（0:横屏正 1:横屏反 2:竖屏正 3:竖屏反）
*			返 回 值: 无
*********************************************************************************************************
*/
void setLcdDirection(uint8_t dir)
{
	myLcd.direction = dir;
}

/*
*********************************************************************************************************
*	函 数 名: setPixel
*	功能说明: 画1个像素
*	形    参:
*			x,y 		: 像素坐标
*			color  	: 像素颜色 ( RGB = L8 格式)
*			layer		: 层
*			返 回 值: 无
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
*	函 数 名: drawLine
*	功能说明: 采用 Bresenham 算法，在2点间画一条直线。
*	形    参:
*			start_x, start_y : 起始点坐标
*			end_x, end_y : 终止点Y坐标
*			color     : 颜色
*			layer			:	层
*			返 回 值	: 无
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

	/* 采用 Bresenham 算法，在2点间画一条直线 */

	setPixel(start_x , start_y , color, layer);

	/* 如果两点重合，结束后面的动作。*/
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

	if ( dx < dy )   /*如果dy为计长方向，则交换纵横坐标。*/
	{
		uint16_t temp;

		iTag = 1 ;
		temp = start_x; start_x = start_y; start_y = temp;
		temp = end_x; end_x = end_y; end_y = temp;
		temp = dx; dx = dy; dy = temp;
	}
	tx = end_x > start_x ? 1 : -1 ;    /* 确定是增1还是减1 */
	ty = end_y > start_y ? 1 : -1 ;
	x = start_x ;
	y = start_y ;
	inc1 = 2 * dy ;
	inc2 = 2 * ( dy - dx );
	d = inc1 - dx ;
	while ( x != end_x )     /* 循环画点 */
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
*	函 数 名: drawPoints
*	功能说明: 采用 Bresenham 算法，绘制一组点，并将这些点连接起来。可用于波形显示。
*	形    参:
*			x, y  	: 坐标数组
*			size		: 数组大小
*			color 	: 颜色
*			layer 	: 层
*			返 回 值: 无
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
*	函 数 名: drawHLine
*	功能说明: 绘制一条水平线
*	形    参:
*			x1, y1 		: 起始点坐标
*			len    		: 线的长度
*			color  		: 颜色
*			返 回 值	: 无
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
*	函 数 名: drawVLine
*	功能说明: 绘制一条垂直线
*	形    参:
*			x, y : 		 起始点坐标
*			len  : 		 线的长度
*			color: 		 颜色
*			返 回 值 : 无
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
*	函 数 名: drawRect
*	功能说明: 绘制水平放置的矩形。
*	形    参:
*			x,y			: 矩形左上角的坐标
*			height 	: 矩形的高度
*			width  	: 矩形的宽度
*			返 回 值: 无
*********************************************************************************************************
*/
void drawRect(uint16_t x, uint16_t y,  uint16_t width, uint16_t height, uint8_t color, uint8_t layer)
{
	/*
	 ---------------->---
	|(x，y)        			 |
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
*	函 数 名: drawCircle
*	功能说明: 绘制一个圆，笔宽为1个像素
*	形    参:
*			x,y  		: 圆心的坐标
*			radius  : 圆的半径
*			layer		: 层
*			返 回 值: 无
*********************************************************************************************************
*/
void drawCircle(uint16_t x, uint16_t y, uint16_t radius, uint8_t color, uint8_t layer)
{
	int32_t  D;			/* Decision Variable */
	uint32_t  CurX;		/* 当前 X 值 */
	uint32_t  CurY;		/* 当前 Y 值 */

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
*	函 数 名: fill_By_DMA2D
*	功能说明: DMA2D颜色填充功能
*	形    参: x, y          左上角坐标
*           xSize         色块X轴大小，即每行像素数
*           ySize         色块Y轴大小，即行数
*           color			    色块颜色值（颜色格式 = L8）
*           layer			   	层
*	返 回 值: 无
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
	
	/* 判断屏幕方向 */
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
	
	/* 选择填充层 */
	if(layer == 1)
	{
		/* L8格式颜色需要/2 */
		offline = (myLcd.L1.width - xSize)/2;
		dstAddr = L1_GRAM_ADDR + y * myLcd.L1.width + x;
		
	}
	else if(layer == 2)
	{
		/* L8格式颜色需要/2 */
		offline = (myLcd.L2.width - xSize)/2;
		dstAddr = L2_GRAM_ADDR + y * myLcd.L2.width + x;
	}
	
	/* DMA2D采用寄存器到存储器模式, 这种模式用不到前景层和背景层 */  
	DMA2D->CR      = DMA2D_R2M;
	DMA2D->OCOLR   = color_565;
	DMA2D->OMAR    = (uint32_t)dstAddr;
	DMA2D->OOR     = offline;
	DMA2D->OPFCCR  = LTDC_PIXEL_FORMAT_RGB565;
	DMA2D->NLR     = (uint32_t)((xSize/2) << 16) | (uint16_t)ySize;

	/* 启动传输 */
	DMA2D->CR   |= DMA2D_CR_START;   

	/* 等待DMA2D传输完成 */
	while (DMA2D->CR & DMA2D_CR_START) {} 
}


void clearLcd(uint8_t color, uint8_t layer)
{
	/* 判断屏幕方向和层 */
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
*	函 数 名: getFontWidth
*	功能说明: 读取字体的宽度（像素单位)
*	形    参:
*		fontStruct : 字体结构体，包含颜色、背景色(支持透明)、字体代码、文字间距等参数
*	返 回 值: 字体的宽度（像素单位)
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
*	函 数 名: getFontHeight
*	功能说明: 读取字体的高度（像素单位)
*	形    参:
*		fontStruct : 字体结构体，包含颜色、背景色(支持透明)、字体代码、文字间距等参数
*	返 回 值: 字体的宽度（像素单位)
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
*	函 数 名: getStrWidth
*	功能说明: 计算字符串宽度(像素单位)
*	形    参:
*		strPtr  : 字符串指针
*		fontStruct : 字体结构体，包含颜色、背景色(支持透明)、字体代码、文字间距等参数
*	返 回 值: 无
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
		code1 = *p;	/* 读取字符串数据， 该数据可能是ascii代码，也可能汉字代码的高字节 */
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
		else	/* 汉字 */
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
*        函 数 名: readAsciiDot
*        功能说明: 读取1个ASCII字符的点阵数据
*        形    参:
*                code : ASCII字符的编码，1字节。1-128
*                fontCode ：字体代码
*                strBuff : 存放读出的字符点阵数据
*        返 回 值: 文字宽度
*********************************************************************************************************
*/
static void readAsciiDot(uint8_t code, uint8_t fontCode, uint8_t *strBuff)
{
        const uint8_t *pAscDot;
        uint8_t fontBytes = 0;
        uint16_t m;
        uint16_t address;
        uint8_t fAllHz = 0;        /* 1表示程序中内嵌全部的ASCII字符集 */

        pAscDot = 0;
        switch (fontCode)
        {
                case FC_ST_12:                /* 12点阵 */
                        fontBytes = 24 / 2;
                        pAscDot = g_Ascii12;        
                        fAllHz = 1;
                        break;
               
                case FC_ST_16:
                        /* 缺省是16点阵 */
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

        if (fAllHz == 1)        /* 内嵌全部ASCII字符点阵 */
        {
                /* 将CPU内部Flash中的ascii字符点阵复制到buf */
                memcpy(strBuff, &pAscDot[code * (fontBytes)], (fontBytes));               
        }
        else        /* 内嵌部分字符，字模数组首字节是ASCII码 */
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
                          /* 字库搜索完毕，未找到，则填充全FF */
                          memset(strBuff, 0xFF, fontBytes);
                          break;
                   }           
           }
   }
}

/*
*********************************************************************************************************
*	函 数 名: readHZDot
*	功能说明: 读取1个汉字的点阵数据
*	形    参:
*		code1, _cod2 : 汉字内码. GB2312编码
*		fontCode ：字体代码
*		strBuff : 存放读出的字符点阵数据
*	返 回 值: 无
*********************************************************************************************************
*/
static void readHZDot(uint8_t code1, uint8_t code2,  uint8_t fontCode, uint8_t *strBuff)
{
	#ifdef USE_SMALL_FONT	/* 使用CPU 内部Flash 小字库 */
		uint8_t *pDot;
		uint8_t fontBytes = 0;
		uint32_t address;
		uint16_t m;

		pDot = 0;	/* 仅仅用于避免告警 */
		switch (fontCode)
		{
			case FC_ST_12:		/* 12点阵 */
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
				/* 字库搜索完毕，未找到，则填充全FF */
				memset(strBuff, 0xFF, fontBytes);
				break;
			}
		}
	#else	/* 用全字库 */
		uint8_t *pDot = 0;
		uint8_t fontBytes = 0;
			
		switch (fontCode)
		{
			case FC_ST_12:		/* 12点阵 */
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
	
		/* 此处需要根据字库文件存放位置进行修改 */
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
*	函 数 名: LCD_DispStrEx
*	功能说明: 在LCD指定坐标（左上角）显示一个字符串。 增强型函数。支持左\中\右对齐，支持定长清屏。
*	形    参:
*		x : X坐标
*		y : Y坐标
*		strPtr  : 字符串指针
*		fontStruct : 字体结构体，包含颜色、背景色(支持透明)、字体代码、文字间距等参数。可以指定RA8875字库显示汉字
*		width : 字符串显示区域的宽度. 0 表示不处理留白区域，此时_Align无效
*		_Align :字符串在显示区域的对齐方式，
*				ALIGN_LEFT = 0,
*				ALIGN_CENTER = 1,
*				ALIGN_RIGHT = 2
*	返 回 值: 无
*********************************************************************************************************
*/
void dispStrEx(uint16_t x, uint16_t y, char *strPtr, struct FontStructDef *fontStruct, uint16_t width, uint8_t _Align, uint8_t layer)
{
        uint32_t i;
        uint8_t code1;
        uint8_t code2;
        uint8_t buf[32 * 32 / 8];        /* 最大支持32点阵汉字 */
        uint8_t width_1;
        uint16_t m;
        uint8_t fontWidth = 0;
        uint8_t fontHeight = 0;
        uint16_t x_1, y_1;
        uint16_t offset;
        uint16_t strWidth;        /* 字符串实际宽度  */
        
        uint8_t line_bytes;
        uint8_t asc_bytes = 0;
        uint8_t hz_bytes = 0;

        switch (fontStruct->FontCode)
        {
                case FC_ST_12:                /* 12点阵 */
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
        
        strWidth = getStrWidth(strPtr, fontStruct);        /* 计算字符串实际宽度(RA8875内部ASCII点阵宽度为变长 */
        offset = 0;
        if (width > strWidth)
        {
                if (_Align == ALIGN_RIGHT)        /* 右对齐 */
                {
                        offset = width - strWidth;
                }
                else if (_Align == ALIGN_CENTER)        /* 左对齐 */
                {
                        offset = (width - strWidth) / 2;
                }
                else        /* 左对齐 ALIGN_LEFT */
                {
                        ;
                }
        }

        /* 左侧填背景色, 中间对齐和右边对齐  */
        if (offset > 0)
        {
					fill_By_DMA2D(x, y, offset, getFontHeight(fontStruct), fontStruct->BackColor, 1);
					x += offset;
        }
        
        /* 右侧填背景色 */
        if (width > strWidth)
        {
					fill_By_DMA2D(x + strWidth,y,width - strWidth - offset,getFontHeight(fontStruct),fontStruct->BackColor,1);
				}
        
        /* 使用CPU内部字库. 点阵信息由CPU读取 */
        {
                /* 开始循环处理字符 */
                while (*strPtr != 0)
                {
                        code1 = *strPtr;        /* 读取字符串数据， 该数据可能是ascii代码，也可能汉字代码的高字节 */
                        if (code1 < 0x80)
                        {
                                /* 将ascii字符点阵复制到buf */
                                readAsciiDot(code1, fontStruct->FontCode, buf);        /* 读取ASCII字符点阵 */
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
                                /* 读1个汉字的点阵 */
                                readHZDot(code1, code2, fontStruct->FontCode, buf);
                                width_1 = fontWidth;
                                line_bytes = hz_bytes;
                        }
        
                        y_1 = y;
                        /* 开始刷LCD */
                        for (m = 0; m < fontHeight; m++)        /* 字符高度 */
                        {
                                x_1 = x;
                                for (i = 0; i < width_1; i++)        /* 字符宽度 */
                                {
                                        if ((buf[m * line_bytes + i / 8] & (0x80 >> (i % 8 ))) != 0x00)
                                        {
																						setPixel(x_1, y_1, fontStruct->FrontColor, layer);
                                        }
                                        else
                                        {
                                                if (fontStruct->BackColor != CL_MASK)        /* 透明色 */
                                                {
																									setPixel(x_1, y_1, fontStruct->BackColor, layer);
                                                        //LCD_PutPixel(x, y, fontStruct->BackColor);        /* 设置像素颜色为文字背景色 */
                                                }
                                        }
        
                                        x_1++;
                                }
                                y_1++;
                        }
        
                        if (fontStruct->Space > 0)
                        {
                                /* 如果文字底色按fontStruct->usBackColor，并且字间距大于点阵的宽度，那么需要在文字之间填充(暂时未实现) */
                        }
                        x += width_1 + fontStruct->Space;        /* 列地址递增 */
                        strPtr++;                        /* 指向下一个字符 */
                }
        }
}

