/*Include Files
	包含头文件*/
#include "CONF.h"

/*LTDC 初始化结构体*/
LTDC_HandleTypeDef hltdc;

/*LTDC Initialize
	LTDC 初始化函数*/
void MX_LTDC_Init(void)
{

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 3;
  hltdc.Init.VerticalSync = 3;
  hltdc.Init.AccumulatedHBP = 11;
  hltdc.Init.AccumulatedVBP = 11;
  hltdc.Init.AccumulatedActiveW = 811;
  hltdc.Init.AccumulatedActiveH = 491;
  hltdc.Init.TotalWidth = 819;
  hltdc.Init.TotalHeigh = 499;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
	//配置LTDC
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
	
	extern const struct LcdStructDef myLcd;
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = myLcd.L1.width;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = myLcd.L1.height;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_L8;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = L1_GRAM_ADDR; //显存地址
  pLayerCfg.ImageWidth = myLcd.L1.width;
  pLayerCfg.ImageHeight = myLcd.L1.height;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
	//配置Layer 1
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
	
	//配置CLUT转换
	HAL_LTDC_ConfigCLUT(&hltdc,(unsigned int * )osc_color_table,256,LTDC_LAYER_1);
	
	//使能CLUT转换
	HAL_LTDC_EnableCLUT(&hltdc,LTDC_LAYER_1);	

}

void LTDC_ConfigColorCHA(uint8_t startBrightness)
{
	uint32_t i;
	for(i = 64; i < 128; i++)
	{
		osc_color_table[i] = RGB2HEX(startBrightness, startBrightness, 0);
		startBrightness += 4;
	}
	HAL_LTDC_ConfigCLUT(&hltdc,(unsigned int * )osc_color_table,256,LTDC_LAYER_1);
}

