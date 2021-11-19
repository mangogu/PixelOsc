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
	/* ������� */
	uint8_t cmdSize = sizeof(cmdList)/(sizeof(char)*20);
	/* ���ַ���ĩβ��'/0' */
	dataBuffer[rxStatus&0x3fff + 1] = 0;
	/* ��ȡ��һ�����ַ��� */
	token = strtok((char*)dataBuffer, " ");
	/* ������ȡ���������ַ��� */
	while (token != NULL)
	{
		/* �������� */
		if(decodeSat == 0)
		{
			/* ѭ�����ҷ��ϵ����� */
			while(cmdIndex < cmdSize)
			{
				cmpRes = strcmp(token, cmdList[cmdIndex]);
				if(!cmpRes)
				{
					printf("%s %d\n\r", token, cmdIndex);
					/* ����״̬1������������ */
					decodeSat = 1;		
					/* �˳�ѭ�� */
					break;
				}
				cmdIndex++;
			}
			/* �˳�ѭ�� */
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


