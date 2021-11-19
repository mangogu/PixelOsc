#ifndef __CMD_H
#define __CMD_H

#include "CONF.h"

#define NO_ERROR		0 /* 格式正确 */
#define ERR_NO_CMD	1 /* 无命令 */
#define ERR_NO_OPT 	2	/* 无选项 */
#define ERR_NO_ARG 	3 /* 无参数 */

uint8_t cmdProcess(void);

#endif

