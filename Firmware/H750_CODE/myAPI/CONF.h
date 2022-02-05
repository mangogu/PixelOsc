#ifndef __CONF_H
#define __CONF_H

/* ȫ�ֱ��� */
#define OFF_TIME 					1				/* �ػ�����ʱ������λ���룩 */
#define OFF_WAIT 					1				/* �ػ�����ʹ���ӳ٣���λ���룩 */
#define OFF_MSG_COLOR 		WHITE		/* �ػ���ʾ������ɫ */


#define MAIN_BACK_COLOR		BLACK		/* ������ɫ */
#define GUI_THICKNESS 		2				/* ��϶��С */
#define TEXT_LEN					20			/* �ı����� */

#define MENU_WIDTH 				120			/* �˵��� */
#define MENU_HEIGHT 			70			/* �˵��� */
#define MENU_COLOR_1 			GREY_L	/* �˵���ɫ1 */
#define MENU_COLOR_2 			BLACK		/* �˵���ɫ2 */
#define MENU_COLOR_S 			RED			/* �˵�ѡ����ɫ */
#define MENU_COLOR_CHAR 	WHITE		/* �˵�������ɫ */



#define BOTTOMLINE_HEIGHT				32
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

#define GRID_Y_NUM 8
#define GRID_X_NUM 12

/* ����ͷ�ļ� */
/* C��׼��ͷ�ļ� */
#include "stdio.h"
#include "string.h"
#include "math.h"
/* HAL��ͷ�ļ� */
#include "stm32h7xx_hal.h"
/* ������ͷ�ļ� */
#include "LTDC.h"
#include "GPIO.h"
#include "TIM.h"
#include "SPI.h"
#include "SYSTICK.h"
#include "USART.h"
#include "DAC.h"
#include "I2C.h"
//#include "IIC.h"
/* �м��ͷ�ļ� */
#include "LCD.h"
#include "FLASH.h"
#include "fatfs.h"
#include "usb_host.h"
/* Ӧ�ò�ͷ�ļ� */
#include "GUI.h"
#include "CTR.h"
#include "CONFIG.h"
#include "FILE.h"
#include "BMP.h"
#include "CMD.h"
#include "BTNFUNC.h"
#include "POWER.h"
/* ϵͳ��ͷ�ļ� */
#include "myOS.h"


#include "demo_spi_flash.h"

#endif
