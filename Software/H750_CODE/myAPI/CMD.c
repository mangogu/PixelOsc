#include "CONF.h"

/* ����ṹ�� */
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
	/* ������� */
	uint8_t cmdSize = sizeof(cmdStruct)/(sizeof(struct cmdStructDef));

	
	
	/* ���ַ���ĩβ��'/0' */
	dataBuffer[rxStatus&0x3fff] = 0;
	/* ��ȡ��һ�����ַ��� */
	token = strtok((char*)dataBuffer, " ");
	/* ������ȡ���������ַ��� */
	while (1)
	{
		/* step1: �������� */
		if(decodeSat == FIND_CMD)
		{
			/* ѭ�����ҷ��ϵ����� */
			while(cmdIndex < cmdSize)
			{
				cmpRes = strcmp(token, cmdStruct[cmdIndex].name);
				if(!cmpRes)
				{
					printf("���� %s ��ȷ\n\r", token);
					/* ����״̬1������ѡ�� */
					decodeSat = FIND_OPT;		
					/* �˳�ѭ�� */
					break;
				}
				cmdIndex++;
			}
			/* ����δ�ҵ����˳� */
			if(decodeSat != FIND_OPT)
			{
				printf("δ�ҵ����� %s\n\r",token);
				break;
			}
		}
		
		/* step2: ����ѡ�� */
		else if(decodeSat == FIND_OPT)
		{
			if(*token == '-')
			{
				/* ��¼���� */
				opt = token;
				printf("ѡ�� %s ��ȷ��",opt);
				/* ����״̬2���������� */
				decodeSat = FIND_PARA;			
			}
			else
			{
				/* ���û��ѡ�� */
				if(token == NULL)
				{
					if(hasOneOpt)
					{
						break;
					}
					else
					{
						printf("δ����ѡ�");
					}
				}
				/* ���ѡ���ʽ���� */
				else
				{
					printf("ѡ�� %s ��ʽ����",token);
				}
				break;
			}
		}
		
		/* step3: �������� */
		else if(decodeSat == FIND_PARA)
		{
			/* ���û�в��� */
			if(token == NULL)
			{
				printf("δ�������\t");
				break;
			}
			else
			{
				para = token;
				printf("����Ϊ %s\t",token);
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
	printf("�ص��ɹ� %s %s\n\r",opt,para);
	if(!(strcmp(opt,"-b")))
	{
		TIM_LcdBright_Config(atoi(para));
		//TIM_LcdBright_Init(10);
	}
	
	printf("\n\r");
}

