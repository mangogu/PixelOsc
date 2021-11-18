#ifndef __BMP_H
#define __BMP_H

#include "CONF.h"

//BMPͷ�ļ�
typedef __packed struct
{
    uint16_t  bfType ;     //�ļ���־.ֻ��'BM',����ʶ��BMPλͼ����
    uint32_t  bfSize ;     //�ļ���С,ռ�ĸ��ֽ�
    uint16_t  bfReserved1 ;//����
    uint16_t  bfReserved2 ;//����
    uint32_t  bfOffBits ;  //���ļ���ʼ��λͼ����(bitmap data)��ʼ֮��ĵ�ƫ����
}BITMAPFILEHEADER ;

//BMP��Ϣͷ
typedef __packed struct
{
    uint32_t biSize ;                //˵��BITMAPINFOHEADER�ṹ����Ҫ��������
    long  biWidth ;         //˵��ͼ��Ŀ�ȣ�������Ϊ��λ 
    long  biHeight ;        //˵��ͼ��ĸ߶ȣ�������Ϊ��λ 
    uint16_t  biPlanes ;         //ΪĿ���豸˵��λ��������ֵ�����Ǳ���Ϊ1 
    uint16_t  biBitCount ;       //˵��������/���أ���ֵΪ1��4��8��16��24����32
		/*˵��ͼ������ѹ�������͡���ֵ����������ֵ֮һ��
		BI_RGB��û��ѹ����
		BI_RLE8��ÿ������8���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����(�ظ����ؼ�������ɫ����)��  
		BI_RLE4��ÿ������4���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����
		BI_BITFIELDS��ÿ�����صı�����ָ�������������*/
    uint32_t biCompression ;     
    uint32_t biSizeImage ;       //˵��ͼ��Ĵ�С�����ֽ�Ϊ��λ������BI_RGB��ʽʱ��������Ϊ0  
    long  biXPelsPerMeter ; //˵��ˮƽ�ֱ��ʣ�������/�ױ�ʾ
    long  biYPelsPerMeter ; //˵����ֱ�ֱ��ʣ�������/�ױ�ʾ
    uint32_t biClrUsed ;         //˵��λͼʵ��ʹ�õĲ�ɫ���е���ɫ������
    uint32_t biClrImportant ;    //˵����ͼ����ʾ����ҪӰ�����ɫ��������Ŀ�������0����ʾ����Ҫ�� 
}BITMAPINFOHEADER ;

//��ɫ�� 
typedef __packed struct 
{
    uint8_t rgbBlue ;    //ָ����ɫǿ��
    uint8_t rgbGreen ;   //ָ����ɫǿ�� 
    uint8_t rgbRed ;     //ָ����ɫǿ�� 
    uint8_t rgbReserved ;//����������Ϊ0 
}RGBQUAD ;

//������Ϣͷ
typedef __packed struct
{ 
    BITMAPFILEHEADER bmfHeader;
    BITMAPINFOHEADER bmiHeader;  
    //RGBQUAD RGB_MASK[3];            //��ɫ�����ڴ��RGB����.
}BITMAPINFO; 

void createBMP(void);


#endif


