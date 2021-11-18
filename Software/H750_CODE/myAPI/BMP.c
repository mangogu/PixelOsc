#include "CONF.h"

extern char USBHPath[4];   /* USBH logical drive path */
extern FATFS USBHFatFS;    /* File system object for USBH logical drive */
extern FIL USBHFile;       /* File object for USBH */

extern FILINFO USBHfno;
extern FRESULT fresult;  	// result
extern UINT br, bw;  			// File read/write count

void snapShot(void)
{	   	
 	BITMAPINFO bmp;			//bmpͷ	 
	uint8_t* pixelPtr;  //����ָ��
	uint16_t i,j;					//ѭ������
	uint8_t r,g,b;			//ɫ��
	//���ļ����������ھʹ���
	fresult = f_open(&USBHFile, "mypic.bmp", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
	//�ļ��򿪳ɹ�
	if(fresult == FR_OK)
	{
		//��д�ļ���Ϣͷ��Ϣ  
		bmp.bmfHeader.bfType = 0x4D42;          //bmp����  "BM"
		bmp.bmfHeader.bfSize= 54 + 800*480*3;   //�ļ���С����Ϣ�ṹ��+�������ݣ�
		bmp.bmfHeader.bfReserved1 = 0x0000;     //����������Ϊ0
		bmp.bmfHeader.bfReserved2 = 0x0000;             
		bmp.bmfHeader.bfOffBits=54;             //λͼ��Ϣ�ṹ����ռ���ֽ���

		//��дλͼ��Ϣͷ��Ϣ  
		bmp.bmiHeader.biSize=40;            //λͼ��Ϣͷ�Ĵ�С
		bmp.bmiHeader.biWidth=800;          //λͼ�Ŀ��
		bmp.bmiHeader.biHeight=480;         //ͼ��ĸ߶�
		bmp.bmiHeader.biPlanes=1;           //Ŀ�����ļ��𣬱�����1
		bmp.bmiHeader.biBitCount=24;        //ÿ����λ��
		bmp.bmiHeader.biCompression=0;      //RGB888��ʽ
		bmp.bmiHeader.biSizeImage=800*480*3;//ʵ��λͼ��ռ�õ��ֽ�����������λͼ�������ݣ�
		bmp.bmiHeader.biXPelsPerMeter=0;    //ˮƽ�ֱ���
		bmp.bmiHeader.biYPelsPerMeter=0;    //��ֱ�ֱ���
		bmp.bmiHeader.biClrImportant=0;     //˵��ͼ����ʾ����ҪӰ�����ɫ������Ŀ��0�������е���ɫһ����Ҫ
		bmp.bmiHeader.biClrUsed=0;          //λͼʵ��ʹ�õĲ�ɫ���е���ɫ��������0��ʾʹ�����еĵ�ɫ����

		//RGB565��ʽ����
//		bmp.RGB_MASK[0].rgbBlue = 0;
//		bmp.RGB_MASK[0].rgbGreen = 0xF8;
//		bmp.RGB_MASK[0].rgbRed = 0;
//		bmp.RGB_MASK[0].rgbReserved = 0;

//		bmp.RGB_MASK[1].rgbBlue = 0xE0;
//		bmp.RGB_MASK[1].rgbGreen = 0x07;
//		bmp.RGB_MASK[1].rgbRed = 0;
//		bmp.RGB_MASK[1].rgbReserved = 0;

//		bmp.RGB_MASK[2].rgbBlue = 0x1F;
//		bmp.RGB_MASK[2].rgbGreen = 0;
//		bmp.RGB_MASK[2].rgbRed = 0;
//		bmp.RGB_MASK[2].rgbReserved = 0;

		/* д�ļ�ͷ */
		fresult = f_write(&USBHFile,(uint8_t *)&bmp,sizeof(bmp),&bw);//д��BMP�ײ�  f_write(&USBHFile, bmp, sizeof(bmp), &bw);
		
		/* д�ļ� */
		pixelPtr = (uint8_t *)L1_GRAM_ADDR;
		for(i = 0; i<480; i++)
		{
			pixelPtr += 800;
			for(j = 0; j<800; j++)
			{
				r = osc_color_table[*(pixelPtr-j)] >> 16;
				g = osc_color_table[*(pixelPtr-j)] >> 8;
				b = osc_color_table[*(pixelPtr-j)];
				fresult = f_write(&USBHFile,(uint8_t *)&b,sizeof(uint8_t),&bw);
				fresult = f_write(&USBHFile,(uint8_t *)&g,sizeof(uint8_t),&bw);
				fresult = f_write(&USBHFile,(uint8_t *)&r,sizeof(uint8_t),&bw);
			}
		}
		
		fresult = f_close(&USBHFile);
	}
}

