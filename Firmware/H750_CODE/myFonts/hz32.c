
/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
/*
*********************************************************************************************************
*
*	ģ������ : ���ֵ����ֿ⡣
*	�ļ����� : hz32.c
*	��    �� : V1.0
*	˵    �� : ֻ�����������õ������ֿ�
*	�޸ļ�¼ :
*		�汾��  ����       ����    ˵��
*		v1.0    2015-04-05 armfly  ST�̼���V3.5.0�汾��
*
*	Copyright (C), 2015-2016, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#include "fonts.h"

/*
	FLASH����ǶС�ֿ⣬ֻ�����������õ��ĺ��ֵ���
	ÿ�е������ݣ�ͷ2�ֽ��Ǻ��ӵ����룬�����ֽ��ǵ����ֵ���ģ���ݡ�
*/
#ifdef USE_SMALL_FONT

unsigned char const g_Hz32[] = {



/* ���һ�б�����0xFF,0xFF�����������ֿ����������־ */
0xFF,0xFF

};
#else
	unsigned char const g_Hz32[] = {0xFF, 0xFF};
#endif
