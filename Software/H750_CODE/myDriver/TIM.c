/* 包含文件 */
#include "TIM.h"

/* 定时器句柄 */
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;



/*****TIM3_CH2*****/

/* 更改LCD背光亮度 */
void TIM_LcdBright_Config(uint8_t val)
{
	htim3.Instance->CCR1 = val;
}

//设置并开启LCD背光亮度
void TIM_LcdBright_Init(uint8_t val)
{
	//局部变量
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  //初始化句柄
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 240-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 256-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	
	//初始化定时器基本功能
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
	
	//使用内部时钟
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
	
	//初始化定时器PWM功能
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
	
	//主从模式设置
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
	
	//通道设置
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = val;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
	
  //配置IO口
  HAL_TIM_MspPostInit(&htim3);
	
	//开启PWM
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}


//设置并开启LCD背光亮度
void TIM_Buzzer_Init(uint16_t hz)
{
	uint16_t val;
	/* 计算分频比 */
	val = 20000 / hz;
	
	/* 局部变量 */
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* 初始化句柄 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 12000 - 1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = val - 1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	
	/* 初始化定时器基本功能*/
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
	
	/* 使用内部时钟 */
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
	
	//初始化定时器PWM功能
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
	
	//主从模式设置
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
	
	//通道设置
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse =  val / 2 - 1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
	
  //配置IO口
  HAL_TIM_MspPostInit(&htim2);
}


void TIM_Buzzer_Run(void)
{
	/* 蜂鸣器启动 */
	
}

void TIM_Buzzer_ConfigThenRun(uint16_t hz)
{
	uint16_t var = 20000 / hz;
	htim3.Instance->ARR = var - 1;
	htim3.Instance->CCR1 = var / 2;
	/* 蜂鸣器启动 */
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}

void TIM_Buzzer_Stop(void)
{
	/* 蜂鸣器关闭 */
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
}

