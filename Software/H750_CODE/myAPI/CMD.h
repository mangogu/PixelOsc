#ifndef __CMD_H
#define __CMD_H

#include "CONF.h"

#define NO_ERROR		0 /* ��ʽ��ȷ */
#define ERR_NO_CMD	1 /* ������ */
#define ERR_NO_OPT 	2	/* ��ѡ�� */
#define ERR_NO_ARG 	3 /* �޲��� */

uint8_t cmdProcess(void);

#endif

