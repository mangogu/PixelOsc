#ifndef __CMD_H
#define __CMD_H

#include "CONF.h"

#define FIND_CMD		0 /* ����CMD */
#define FIND_OPT		1 /* ����OPT */
#define FIND_PARA		2 /* ����PARA */

#define NO_ERROR		0 /* ��ʽ��ȷ */
#define ERR_NO_CMD	1 /* ������ */
#define ERR_NO_OPT 	2	/* ��ѡ�� */
#define ERR_NO_ARG 	3 /* �޲��� */

/* ����ṹ�� */
struct cmdStructDef
{
	/* �������� */
	char name[10];		
	void (*recallFunc)(char*, char *);
}; 

void cmdProcess(void);
void screenRecall(char *opt, char *para);

#endif

