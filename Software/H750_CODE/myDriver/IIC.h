#include "IIC.h"

#ifndef __IIC_H
#define __IIC_H
 
#include "sys.h"
 
/* 高低电平 */
#define HIGH	1
#define LOW		0
 
/* IO方向设置 */
#define SDA_IN()  {GPIOH->MODER&=~(3<<(5*2));GPIOH->MODER|=0<<5*2;}		//PH5输入模式
#define SDA_OUT() {GPIOH->MODER&=~(3<<(5*2));GPIOH->MODER|=1<<5*2;} 	//PH5输出模式
/* IO操作 */
#define IIC_SCL(n)  (n?HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_RESET)) //SCL
#define IIC_SDA(n)  (n?HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_RESET)) //SDA
#define READ_SDA    HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_5)					//输入SDA
 
/* IIC所有操作函数 */
void IIC_Init(void);										//IIC初始化
void IIC_Start(void);										//产生IIC起始信号
void IIC_Stop(void);										//产生IIC停止信号
u8   IIC_Wait_Ack(void);									//等待ACK信号到来
void IIC_Ack(void);											//产生ACK应答
void IIC_NAck(void);										//不产生ACK应答
void IIC_Send_Byte(u8 txd);									//IIC发送一个字节
u8   IIC_Read_Byte(unsigned char ack);						//IIC读取一个字节
 
#endif

