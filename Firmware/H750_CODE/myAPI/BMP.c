#include "CONF.h"

extern char USBHPath[4];   /* USBH logical drive path */
extern FATFS USBHFatFS;    /* File system object for USBH logical drive */
extern FIL USBHFile;       /* File object for USBH */

extern FILINFO USBHfno;
extern FRESULT fresult;  	// result
extern UINT br, bw;  			// File read/write count

void snapShot(void)
{	   	
 	BITMAPINFO bmp;			//bmp头	 
	uint8_t* pixelPtr;  //像素指针
	uint16_t i,j;					//循环变量
	uint8_t r,g,b;			//色彩
	//打开文件，若不存在就创建
	fresult = f_open(&USBHFile, "mypic.bmp", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
	//文件打开成功
	if(fresult == FR_OK)
	{
		//填写文件信息头信息  
		bmp.bmfHeader.bfType = 0x4D42;          //bmp类型  "BM"
		bmp.bmfHeader.bfSize= 54 + 800*480*3;   //文件大小（信息结构体+像素数据）
		bmp.bmfHeader.bfReserved1 = 0x0000;     //保留，必须为0
		bmp.bmfHeader.bfReserved2 = 0x0000;             
		bmp.bmfHeader.bfOffBits=54;             //位图信息结构体所占的字节数

		//填写位图信息头信息  
		bmp.bmiHeader.biSize=40;            //位图信息头的大小
		bmp.bmiHeader.biWidth=800;          //位图的宽度
		bmp.bmiHeader.biHeight=480;         //图像的高度
		bmp.bmiHeader.biPlanes=1;           //目标设别的级别，必须是1
		bmp.bmiHeader.biBitCount=24;        //每像素位数
		bmp.bmiHeader.biCompression=0;      //RGB888格式
		bmp.bmiHeader.biSizeImage=800*480*3;//实际位图所占用的字节数（仅考虑位图像素数据）
		bmp.bmiHeader.biXPelsPerMeter=0;    //水平分辨率
		bmp.bmiHeader.biYPelsPerMeter=0;    //垂直分辨率
		bmp.bmiHeader.biClrImportant=0;     //说明图像显示有重要影响的颜色索引数目，0代表所有的颜色一样重要
		bmp.bmiHeader.biClrUsed=0;          //位图实际使用的彩色表中的颜色索引数，0表示使用所有的调色板项

		//RGB565格式掩码
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

		/* 写文件头 */
		fresult = f_write(&USBHFile,(uint8_t *)&bmp,sizeof(bmp),&bw);//写入BMP首部  f_write(&USBHFile, bmp, sizeof(bmp), &bw);
		
		/* 写文件 */
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

