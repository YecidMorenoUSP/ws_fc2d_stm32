#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stdio.h"
#include "io_defines.h"
#include "stm32f4xx_hal.h"
#include "stm32f429i_discovery.h"
#include "fc2d_config.h"

#include "gpio.h"
//https://microcontrollerslab.com/adc-stm32f4-discovery-board-with-hal-adc-driver/#:~:text=STM32F4%20Discovery%20Board%20ADC%20modules&text=STM32F407VG%20microcontroller%20has%20three%20successive,for%20the%20STM32F4%20discovery%20board.
#define ADCx                            ADC3
#define ADCx_CLK_ENABLE()               __HAL_RCC_ADC3_CLK_ENABLE()
#define DMAx_CLK_ENABLE()               __HAL_RCC_DMA2_CLK_ENABLE()
#define ADCx_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOF_CLK_ENABLE()

#define ADCx_FORCE_RESET()              __HAL_RCC_ADC_FORCE_RESET()
#define ADCx_RELEASE_RESET()            __HAL_RCC_ADC_RELEASE_RESET()

/* Definition for ADCx Channel Pin */
#define ADCx_CHANNEL_PIN                GPIO_PIN_1
#define ADCx_CHANNEL_GPIO_PORT          GPIOC

/* Definition for ADCx's Channel */
#define ADCx_CHANNEL                    ADC_CHANNEL_11

/* Definition for ADCx's DMA */
#define ADCx_DMA_CHANNEL                DMA_CHANNEL_2
#define ADCx_DMA_STREAM                 DMA2_Stream0

/* Definition for ADCx's NVIC */
#define ADCx_DMA_IRQn                   DMA2_Stream0_IRQn
#define ADCx_DMA_IRQHandler             DMA2_Stream0_IRQHandler

void Error_Handler(void);
int _write(int file, char *ptr, int len);

#ifdef __cplusplus
}
#endif

#endif
