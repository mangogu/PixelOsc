#include "CONF.h"

/***************************************************************
 @Function			void IIC_Init(void)
 @Description		IIC初始化
 @Input					void
 @Return				void
***************************************************************/
/*
*********************************************************************************************************
*	函 数 名: setPixel
*	功能说明: 画1个像素
*	形   	参:	无
*	返 回 值：无
*********************************************************************************************************
*/
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_GPIOH_CLK_ENABLE();									//使能GPIOH时钟
	
	/* PH4,5初始化设置 */
	GPIO_Initure.Pin = GPIO_PIN_4 | GPIO_PIN_5;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;						//推挽输出
	GPIO_Initure.Pull = GPIO_PULLUP;								//上拉
	GPIO_Initure.Speed = GPIO_SPEED_FAST;							//快速
	HAL_GPIO_Init(GPIOH, &GPIO_Initure);
	
	IIC_SDA(HIGH);
	IIC_SCL(HIGH);
}
 
/***************************************************************
 @Function			void IIC_Start(void)
 @Description		产生IIC起始信号
					SCL : HIGH
					SDA : HIGH -> LOW
 @Input				void
 @Return			void
***************************************************************/
void IIC_Start(void)
{
	SDA_OUT();														//sda线输出
	IIC_SDA(HIGH);
	IIC_SCL(HIGH);
	delay_us(4);
	IIC_SDA(LOW);		//START : when CLK is high,DATA change form high to low
	delay_us(4);
	IIC_SCL(LOW);													//钳住I2C总线,准备发送或接收数据 
}
 
/***************************************************************
 @Function			void IIC_Stop(void)
 @Description		产生IIC停止信号
					SCL : HIGH
					SDA : LOW -> HIGH
 @Input				void
 @Return			void
***************************************************************/
void IIC_Stop(void)
{
	SDA_OUT();														//sda线输出
	IIC_SDA(LOW);
	IIC_SCL(HIGH);
	delay_us(4);
	IIC_SDA(HIGH);		//STOP : when CLK is high,DATA change form low to high
	delay_us(4);
}
 
/***************************************************************
 @Function			u8 IIC_Wait_Ack(void)
 @Description		等待ACK信号到来
 @Input				void
 @Return			1 : 接收应答失败
					0 : 接收应答成功
***************************************************************/
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime = 0;
	
	SDA_IN();														//SDA设置为输入
	IIC_SDA(HIGH);delay_us(1);
	IIC_SCL(HIGH);delay_us(1);
	while (READ_SDA) {
		ucErrTime++;
		if (ucErrTime > 250) {
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL(LOW);													//时钟输出0
	return 0;
}
 
/***************************************************************
 @Function			void IIC_Ack(void)
 @Description		产生ACK应答
 @Input				void
 @Return			void
***************************************************************/
void IIC_Ack(void)
{
	SDA_OUT();														//sda线输出
	IIC_SCL(LOW);
	IIC_SDA(LOW);
	delay_us(2);
	IIC_SCL(HIGH);
	delay_us(2);
	IIC_SCL(LOW);
}
 
/***************************************************************
 @Function			void IIC_NAck(void)
 @Description		不产生ACK应答
 @Input				void
 @Return			void
***************************************************************/
void IIC_NAck(void)
{
	SDA_OUT();														//sda线输出
	IIC_SCL(LOW);
	IIC_SDA(HIGH);
	delay_us(2);
	IIC_SCL(HIGH);
	delay_us(2);
	IIC_SCL(LOW);
}
 
/***************************************************************
 @Function			void IIC_Send_Byte(u8 txd)
 @Description		IIC发送一个字节
 @Input				txd : 发送数据
 @Return			void
***************************************************************/
void IIC_Send_Byte(u8 txd)
{
	u8 t;
	
	SDA_OUT();														//sda线输出
	IIC_SCL(LOW);													//拉低时钟开始数据传输
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
 @Description		读1个字节,ack=1时,发送ACK,ack=0,发送nACK
 @Input				ack
 @Return			所读数据
***************************************************************/
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	
	SDA_IN();														//SDA设置为输入
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
		IIC_NAck();													//发送nACK
	else
		IIC_Ack();													//发送ACK
	
	return receive;
}

