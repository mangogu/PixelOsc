#ifndef CONF_H
#define CONF_H

/* ȫ�ֱ��� */
#define OFF_TIME 					2				/* �ػ�����ʱ������λ���룩 */
#define OFF_WAIT 					1				/* �ػ�����ʹ���ӳ٣���λ���룩 */


#define MAIN_BACK_COLOR		BLUE		/* ������ɫ */
#define GUI_THICKNESS 		2				/* ��϶��С */
#define TEXT_LEN					12			/* �ı����� */

#define MENU_WIDTH 				160			/* �˵��� */
#define MENU_HEIGHT 			70			/* �˵��� */
#define MENU_COLOR_1 			GREY_L	/* �˵���ɫ1 */
#define MENU_COLOR_2 			BLACK		/* �˵���ɫ2 */
#define MENU_COLOR_S 			RED			/* �˵�ѡ����ɫ */
#define MENU_COLOR_CHAR 	WHITE		/* �˵�������ɫ */



#define BOTTOMLINE_HEIGHT				32
#define BOTTOMLINE_WIDTH 				196
#define BOTTOMLINE_COLOR_1 			GREY_L
#define BOTTOMLINE_COLOR_2 			BLACK
#define BOTTOMLINE_COLOR_CHAR 	WHITE
#define BOTTOMLINE_COLOR_S1		 	YELLOW
#define BOTTOMLINE_COLOR_S2		 	PURPLE
#define BOTTOMLINE_COLOR_S3		 	RED_D
#define BOTTOMLINE_COLOR_S4		 	GREEN
#define BOTTOMLINE_WIDTH 				196
#define BOTTOMLINE_LEFT_WIDTH 	32

#define TOPLINE_HEIGHT		32

#define WELCOME_WINDOW_X							50
#define WELCOME_WINDOW_Y							50
#define WELCOME_WINDOW_WIDTH					480
#define WELCOME_WINDOW_HEIGHT					320
#define WELCOME_WINDOW_SHADOW_DISTANCE	6
#define WELCOME_WINDOW_TEXT_OFFSETX		10
#define WELCOME_WINDOW_TEXT_OFFSETY		10
#define WELCOME_WINDOW_COLOR_SHADOW		GREY_L
#define WELCOME_WINDOW_COLOR_TOP			WHITE
#define WELCOME_WINDOW_COLOR_CHAR			BLACK

/* ����ͷ�ļ� */
/* C��׼��ͷ�ļ� */
#include "stdio.h"
/* HAL��ͷ�ļ� */
#include "stm32h7xx_hal.h"
/* ������ͷ�ļ� */
#include "LTDC.h"
#include "GPIO.h"
#include "TIM.h"
#include "SPI.h"
#include "SYSTICK.h"
#include "USART.h"
//#include "IIC.h"
/* �м��ͷ�ļ� */
#include "LCD.h"
#include "FLASH.h"
/* Ӧ�ò�ͷ�ļ� */
#include "GUI.h"
#include "CTR.h"
#include "CONFIG.h"
/* ϵͳ��ͷ�ļ� */
#include "myOS.h"


#include "demo_spi_flash.h"

#endif

