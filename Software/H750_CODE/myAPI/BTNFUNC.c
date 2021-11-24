#include "CONF.h"

char* MasterSrcRecall(uint8_t key,char* setting)
{
	static uint8_t curIndex = 0;
	
	const char MasterSrcList[][5] = 
	{
		"CHA",
		"CHB",
		"MATH"
	};
	
	/* 前进、后退、初始化 */
	if(key != SAVE)
	{
		/* 更新菜单内容 */
		curIndex = shiftContext(key, curIndex, sizeof(MasterSrcList)/(sizeof(char)*5));
		strcpy(menu[0].page[0].menuBtn[0].strPtr_2, MasterSrcList[curIndex]);
	}
	
	/* 保存 */
	else if(key == SAVE)
	{
		
	}
}



uint8_t shiftContext(uint8_t key, uint8_t curIndex, uint8_t num)
{
	if(key == FORWARD)
		{
			if(curIndex == num - 1)
			{
				curIndex = 0;
			}
			else
			{
				curIndex++;
			}
		}
		else if(key == BACK)
		{
			if(curIndex == 0)
			{
				curIndex = num - 1;
			}
			else
			{
				curIndex--;
			}
		}
		else if(key == IMPORT)
		{
			
		}
		else if(key == INIT)
		{
			curIndex = 0;
		}
		
		return curIndex;
}
