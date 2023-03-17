/*
 * https://microcontrollerslab.com/stm32f4-discovery-board-pinout-features-examples/
 * */

#include "main.h"
#include "math.h"
#include "fc2d_config.h"
#include "io_defines.h"
#include "stm32f4xx_it.h"


uint16_t count = 0;
float    count2 = 0;


uint16_t freq = 100;
uint16_t amp  = 4095;
uint16_t y  = 0;
float t = 0;
uint32_t k_t = 0;

uint16_t tim_start = 0;
uint16_t tim_stop = 0;
uint16_t delta_time = 0;


TIM_HandleTypeDef htim7;
ADC_HandleTypeDef hadc2;


#define PS1 4200

void SystemClock_Config(void);
void TIM7_IRQHandler(void);



DAC_HandleTypeDef DAC_Config;
__IO uint32_t Adc_value;

float dt = (84000.0f/PS1)*1000.0f/2.0f;
uint32_t Adc_value2 ;
void TIM7_IRQHandler(void)
{

//	BSP_LED_Toggle(LED4);


	Adc_value2 = Adc_value;


	y = (amp/2.0)*(1.0f+sin(2*M_PI*(Adc_value2/freq+100)*t));
	HAL_DAC_SetValue(&DAC_Config, DAC_CHANNEL_2, DAC_ALIGN_12B_R, y);
	t = (k_t/dt);
	k_t ++;


	HAL_TIM_IRQHandler(&htim7);

//	HAL_ADC_Start(&hadc2);
//	if(HAL_ADC_PollForConversion(&hadc2, 5) == HAL_OK) Adc_value  = HAL_ADC_GetValue(&hadc2);
//	HAL_ADC_Stop(&hadc2);

}

void configure_GPIO(void)
{

/* DAC GPIO ---> PA5 */
 GPIO_InitTypeDef GPIO_InitStruct = {0};
 GPIO_InitStruct.Pin = GPIO_PIN_5;
 GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
 GPIO_InitStruct.Pull = GPIO_NOPULL;
 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
 HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void configure_DAC(void)
{
 DAC_ChannelConfTypeDef Channel_Config;
 __HAL_RCC_DAC_CLK_ENABLE();
 /* DAC Initialization */
 DAC_Config.Instance = DAC;

 HAL_DAC_Init(&DAC_Config);

 /* DAC channel_OUT2 config */
 Channel_Config.DAC_Trigger = DAC_TRIGGER_NONE;
 Channel_Config.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
 HAL_DAC_ConfigChannel(&DAC_Config, &Channel_Config, DAC_CHANNEL_2);
}

void configure_ADC(void){

	hadc2.Instance          = ADCx;

	hadc2.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV8;
	hadc2.Init.Resolution = ADC_RESOLUTION_12B;
	hadc2.Init.ScanConvMode = DISABLE;
	hadc2.Init.ContinuousConvMode = ENABLE;
	hadc2.Init.DiscontinuousConvMode = DISABLE;
	hadc2.Init.NbrOfDiscConversion = 0;
	hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc2.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
	hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc2.Init.NbrOfConversion = 16;
	hadc2.Init.DMAContinuousRequests = ENABLE;
	hadc2.Init.EOCSelection = DISABLE;

	if(HAL_ADC_Init(&hadc2) != HAL_OK){
	/* Initialization Error */
	Error_Handler();
	}

	ADC_ChannelConfTypeDef sConfig;

	sConfig.Channel = ADCx_CHANNEL;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	sConfig.Offset = 0;

	if(HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
	{
	/* Channel Configuration Error */
	Error_Handler();
	}

	if(HAL_ADC_Start_DMA(&hadc2, (uint32_t*)&Adc_value, 1) != HAL_OK)
	{
	/* Start Conversation Error */
	Error_Handler();
	}

}

void MX_TIM7_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim7.Instance = TIM7;
  htim7.Init.Prescaler = PS1-1;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 1;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();

	configure_GPIO();
	configure_DAC();
	HAL_DAC_Start(&DAC_Config, DAC_CHANNEL_2);
	HAL_DAC_SetValue(&DAC_Config, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 0);

	MX_TIM7_Init();
	HAL_TIM_Base_Start_IT(&htim7);

	configure_ADC();

	fc2d_init();

	HAL_Delay(50);




	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);

	for(;;){
		BSP_LED_Toggle(LED3);
		HAL_Delay(200);
	}
}

void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig (&RCC_OscInitStruct);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}


void Error_Handler(void)
{
  /* Turn LED4 on */
  BSP_LED_On(LED4);
  while(1)
  {
  }
}


int _write(int file, char *ptr, int len)
{
  int i=0;
  for(i=0 ; i<len ; i++)
    ITM_SendChar((*ptr++));
  return len;
}
