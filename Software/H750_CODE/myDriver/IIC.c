#include "CONF.h"

/***************************************************************
 @Function			void IIC_Init(void)
 @Description		IIC��ʼ��
 @Input					void
 @Return				void
***************************************************************/
/*
*********************************************************************************************************
*	�� �� ��: setPixel
*	����˵��: ��1������
*	��   	��:	��
*	�� �� ֵ����
*********************************************************************************************************
*/
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_GPIOH_CLK_ENABLE();									//ʹ��GPIOHʱ��
	
	/* PH4,5��ʼ������ */
	GPIO_Initure.Pin = GPIO_PIN_4 | GPIO_PIN_5;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;						//�������
	GPIO_Initure.Pull = GPIO_PULLUP;								//����
	GPIO_Initure.Speed = GPIO_SPEED_FAST;							//����
	HAL_GPIO_Init(GPIOH, &GPIO_Initure);
	
	IIC_SDA(HIGH);
	IIC_SCL(HIGH);
}
 
/***************************************************************
 @Function			void IIC_Start(void)
 @Description		����IIC��ʼ�ź�
					SCL : HIGH
					SDA : HIGH -> LOW
 @Input				void
 @Return			void
***************************************************************/
void IIC_Start(void)
{
	SDA_OUT();														//sda�����
	IIC_SDA(HIGH);
	IIC_SCL(HIGH);
	delay_us(4);
	IIC_SDA(LOW);		//START : when CLK is high,DATA change form high to low
	delay_us(4);
	IIC_SCL(LOW);													//ǯסI2C����,׼�����ͻ�������� 
}
 
/***************************************************************
 @Function			void IIC_Stop(void)
 @Description		����IICֹͣ�ź�
					SCL : HIGH
					SDA : LOW -> HIGH
 @Input				void
 @Return			void
***************************************************************/
void IIC_Stop(void)
{
	SDA_OUT();														//sda�����
	IIC_SDA(LOW);
	IIC_SCL(HIGH);
	delay_us(4);
	IIC_SDA(HIGH);		//STOP : when CLK is high,DATA change form low to high
	delay_us(4);
}
 
/***************************************************************
 @Function			u8 IIC_Wait_Ack(void)
 @Description		�ȴ�ACK�źŵ���
 @Input				void
 @Return			1 : ����Ӧ��ʧ��
					0 : ����Ӧ��ɹ�
***************************************************************/
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime = 0;
	
	SDA_IN();														//SDA����Ϊ����
	IIC_SDA(HIGH);delay_us(1);
	IIC_SCL(HIGH);delay_us(1);
	while (READ_SDA) {
		ucErrTime++;
		if (ucErrTime > 250) {
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL(LOW);													//ʱ�����0
	return 0;
}
 
/***************************************************************
 @Function			void IIC_Ack(void)
 @Description		����ACKӦ��
 @Input				void
 @Return			void
***************************************************************/
void IIC_Ack(void)
{
	SDA_OUT();														//sda�����
	IIC_SCL(LOW);
	IIC_SDA(LOW);
	delay_us(2);
	IIC_SCL(HIGH);
	delay_us(2);
	IIC_SCL(LOW);
}
 
/***************************************************************
 @Function			void IIC_NAck(void)
 @Description		������ACKӦ��
 @Input				void
 @Return			void
***************************************************************/
void IIC_NAck(void)
{
	SDA_OUT();														//sda�����
	IIC_SCL(LOW);
	IIC_SDA(HIGH);
	delay_us(2);
	IIC_SCL(HIGH);
	delay_us(2);
	IIC_SCL(LOW);
}
 
/***************************************************************
 @Function			void IIC_Send_Byte(u8 txd)
 @Description		IIC����һ���ֽ�
 @Input				txd : ��������
 @Return			void
***************************************************************/
void IIC_Send_Byte(u8 txd)
{
	u8 t;
	
	SDA_OUT();														//sda�����
	IIC_SCL(LOW);													//����ʱ�ӿ�ʼ���ݴ���
	for (t = 0; t < 8; t++)
	{
		IIC_SDA((txd & 0x80) >> 7);
		txd <<= 1;
		delay_us(2);
		IIC_SCL(HIGH);
		delay_us(2);
		IIC_SCL(LOW);
		delay_us(2);
	}
}
 
/***************************************************************
 @Function			u8 IIC_Read_Byte(unsigned char ack)
 @Description		��1���ֽ�,ack=1ʱ,����ACK,ack=0,����nACK
 @Input				ack
 @Return			��������
***************************************************************/
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	
	SDA_IN();														//SDA����Ϊ����
	for (i = 0; i < 8; i++)
	{
		IIC_SCL(LOW);
        delay_us(2);
		IIC_SCL(HIGH);
        receive <<= 1;
        if (READ_SDA) receive++;
		delay_us(1);
	}
	if (!ack)
		IIC_NAck();													//����nACK
	else
		IIC_Ack();													//����ACK
	
	return receive;
}

