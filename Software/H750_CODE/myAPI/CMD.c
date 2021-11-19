#include "CONF.h"

const char cmdList[][20] = 
{
	"menu",
	"trig"
};

uint8_t cmdProcess(void)
{
	char *token;
	int cmpRes;
	uint8_t cmdIndex = 0;
	uint8_t decodeSat = 0;
	/* 命令表长度 */
	uint8_t cmdSize = sizeof(cmdList)/(sizeof(char)*20);
	/* 给字符串末尾加'/0' */
	dataBuffer[rxStatus&0x3fff + 1] = 0;
	/* 获取第一个子字符串 */
	token = strtok((char*)dataBuffer, " ");
	/* 继续获取其他的子字符串 */
	while (token != NULL)
	{
		/* 解析命令 */
		if(decodeSat == 0)
		{
			/* 循环查找符合的命令 */
			while(cmdIndex < cmdSize)
			{
				cmpRes = strcmp(token, cmdList[cmdIndex]);
				if(!cmpRes)
				{
					printf("%s %d\n\r", token, cmdIndex);
					/* 进入状态1：解析擦桉树 */
					decodeSat = 1;		
					/* 退出循环 */
					break;
				}
				cmdIndex++;
			}
			/* 退出循环 */
			if(decodeSat != 1)
			{
				rxStatus = 0;
				return ERR_NO_CMD;
			}
		}
		token = strtok(NULL, " ");
	}
	rxStatus = 0;
}


