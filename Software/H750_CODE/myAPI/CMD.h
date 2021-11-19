#ifndef __CMD_H
#define __CMD_H

#include "CONF.h"

#define FIND_CMD		0 /* 查找CMD */
#define FIND_OPT		1 /* 查找OPT */
#define FIND_PARA		2 /* 查找PARA */

#define NO_ERROR		0 /* 格式正确 */
#define ERR_NO_CMD	1 /* 无命令 */
#define ERR_NO_OPT 	2	/* 无选项 */
#define ERR_NO_ARG 	3 /* 无参数 */

/* 命令结构体 */
struct cmdStructDef
{
	/* 命令名称 */
	char name[10];		
	void (*recallFunc)(char*, char *);
}; 

void cmdProcess(void);
void screenRecall(char *opt, char *para);

#endif

