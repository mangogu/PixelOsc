#ifndef __CONF_H
#define __CONF_H

/* 全局变量 */
#define OFF_TIME 					1				/* 关机按键时长（单位：秒） */
#define OFF_WAIT 					1				/* 关机按键使能延迟（单位：秒） */
#define OFF_MSG_COLOR 		WHITE		/* 关机提示文字颜色 */


#define MAIN_BACK_COLOR		BLACK		/* 主背景色 */
#define GUI_THICKNESS 		2				/* 间隙大小 */
#define TEXT_LEN					20			/* 文本长度 */

#define MENU_WIDTH 				120			/* 菜单宽 */
#define MENU_HEIGHT 			70			/* 菜单高 */
#define MENU_COLOR_1 			GREY_L	/* 菜单颜色1 */
#define MENU_COLOR_2 			BLACK		/* 菜单颜色2 */
#define MENU_COLOR_S 			RED			/* 菜单选中颜色 */
#define MENU_COLOR_CHAR 	WHITE		/* 菜单文字颜色 */



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

/* 包含头文件 */
/* C标准库头文件 */
#include "stdio.h"
#include "string.h"
#include "math.h"
/* HAL库头文件 */
#include "stm32h7xx_hal.h"
/* 驱动层头文件 */
#include "LTDC.h"
#include "GPIO.h"
#include "TIM.h"
#include "SPI.h"
#include "SYSTICK.h"
#include "USART.h"
#include "DAC.h"
#include "I2C.h"
//#include "IIC.h"
/* 中间层头文件 */
#include "LCD.h"
#include "FLASH.h"
#include "fatfs.h"
#include "usb_host.h"
/* 应用层头文件 */
#include "GUI.h"
#include "CTR.h"
#include "CONFIG.h"
#include "FILE.h"
#include "BMP.h"
#include "CMD.h"
#include "BTNFUNC.h"
#include "POWER.h"
/* 系统层头文件 */
#include "myOS.h"


#include "demo_spi_flash.h"

#endif

