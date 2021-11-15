#include "IIC.h"

#ifndef __IIC_H
#define __IIC_H
 
#include "sys.h"
 
/* �ߵ͵�ƽ */
#define HIGH	1
#define LOW		0
 
/* IO�������� */
#define SDA_IN()  {GPIOH->MODER&=~(3<<(5*2));GPIOH->MODER|=0<<5*2;}		//PH5����ģʽ
#define SDA_OUT() {GPIOH->MODER&=~(3<<(5*2));GPIOH->MODER|=1<<5*2;} 	//PH5���ģʽ
/* IO���� */
#define IIC_SCL(n)  (n?HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_RESET)) //SCL
#define IIC_SDA(n)  (n?HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_RESET)) //SDA
#define READ_SDA    HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_5)					//����SDA
 
/* IIC���в������� */
void IIC_Init(void);										//IIC��ʼ��
void IIC_Start(void);										//����IIC��ʼ�ź�
void IIC_Stop(void);										//����IICֹͣ�ź�
u8   IIC_Wait_Ack(void);									//�ȴ�ACK�źŵ���
void IIC_Ack(void);											//����ACKӦ��
void IIC_NAck(void);										//������ACKӦ��
void IIC_Send_Byte(u8 txd);									//IIC����һ���ֽ�
u8   IIC_Read_Byte(unsigned char ack);						//IIC��ȡһ���ֽ�
 
#endif

