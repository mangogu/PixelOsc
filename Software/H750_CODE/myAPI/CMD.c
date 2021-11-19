#include "CONF.h"

/* 命令结构体 */
struct cmdStructDef cmdStruct[] = 
{
    {"screen",screenRecall}
};


void cmdProcess(void)
{
	char *token;
	char *opt;
	char *para;
	int cmpRes;
	uint8_t cmdIndex = 0;
	uint8_t hasOneOpt = 0;
	//uint8_t optIndex = 0;
	uint8_t decodeSat = FIND_CMD;
	/* 命令表长度 */
	uint8_t cmdSize = sizeof(cmdStruct)/(sizeof(struct cmdStructDef));

	
	
	/* 给字符串末尾加'/0' */
	dataBuffer[rxStatus&0x3fff] = 0;
	/* 获取第一个子字符串 */
	token = strtok((char*)dataBuffer, " ");
	/* 继续获取其他的子字符串 */
	while (1)
	{
		/* step1: 解析命令 */
		if(decodeSat == FIND_CMD)
		{
			/* 循环查找符合的命令 */
			while(cmdIndex < cmdSize)
			{
				cmpRes = strcmp(token, cmdStruct[cmdIndex].name);
				if(!cmpRes)
				{
					printf("命令 %s 正确\n\r", token);
					/* 进入状态1：解析选项 */
					decodeSat = FIND_OPT;		
					/* 退出循环 */
					break;
				}
				cmdIndex++;
			}
			/* 命令未找到，退出 */
			if(decodeSat != FIND_OPT)
			{
				printf("未找到命令 %s\n\r",token);
				break;
			}
		}
		
		/* step2: 解析选项 */
		else if(decodeSat == FIND_OPT)
		{
			if(*token == '-')
			{
				/* 记录参数 */
				opt = token;
				printf("选项 %s 正确，",opt);
				/* 进入状态2：解析参数 */
				decodeSat = FIND_PARA;			
			}
			else
			{
				/* 如果没有选项 */
				if(token == NULL)
				{
					if(hasOneOpt)
					{
						break;
					}
					else
					{
						printf("未输入选项，");
					}
				}
				/* 如果选项格式错误 */
				else
				{
					printf("选项 %s 格式错误，",token);
				}
				break;
			}
		}
		
		/* step3: 解析参数 */
		else if(decodeSat == FIND_PARA)
		{
			/* 如果没有参数 */
			if(token == NULL)
			{
				printf("未输入参数\t");
				break;
			}
			else
			{
				para = token;
				printf("参数为 %s\t",token);
				cmdStruct[cmdIndex].recallFunc(opt,para);
				hasOneOpt = 1;
				decodeSat = FIND_OPT;
			}
		}

		token = strtok(NULL, " ");
	}
	rxStatus = 0;
}

void screenRecall(char *opt, char *para)
{
	printf("回调成功 %s %s\n\r",opt,para);
	if(!(strcmp(opt,"-b")))
	{
		TIM_LcdBright_Config(atoi(para));
		//TIM_LcdBright_Init(10);
	}
	
	printf("\n\r");
}

