#include "io_defines.h"
#include "fc2d_config.h"
#include "utils.h"

void IO_ENCODER_INIT(io_encoder * encoder){

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// Habilitar relojes, crear funcion automatica.
	__HAL_RCC_GPIOC_CLK_ENABLE();

	for (int i = 0 ; i < 2 ; i++){

		GPIO_InitStruct.Pin = encoder->pin[i];
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		HAL_GPIO_Init(encoder->port[i], &GPIO_InitStruct);

		HAL_NVIC_SetPriority(encoder->IRQ[i], 0x0F, 0x0F);
		HAL_NVIC_EnableIRQ(encoder->IRQ[i]);
	}

	int idx_1 = get_idx(encoder->idx, -1, IO_MAX_TIME_LOG);

	encoder->data[ idx_1 ].state[0] = HAL_GPIO_ReadPin(encoder->port[0], encoder->pin[0]);
	encoder->data[ idx_1 ].state[1] = HAL_GPIO_ReadPin(encoder->port[1], encoder->pin[1]);
	encoder->data[ idx_1 ].raw = 0;
	encoder->data[ idx_1 ].time = 0;
}

void IO_ENCODER_COUNTER(io_encoder * encoder){
	int idx_1 = 3;//get_idx(encoder->idx, -1, IO_MAX_TIME_LOG);
	int idx0 = 0;//get_idx(encoder->idx,  0, IO_MAX_TIME_LOG);

	encoder->data[idx0].state[0] = HAL_GPIO_ReadPin(encoder->port[0], encoder->pin[0]);
	encoder->data[idx0].state[1] = HAL_GPIO_ReadPin(encoder->port[1], encoder->pin[1]);


	if(encoder->data[idx0].state[0] ^ encoder->data[idx_1].state[1]){
		encoder->data[idx0].raw = encoder->data[idx_1].raw+1;
	}else{
		encoder->data[idx0].raw = encoder->data[idx_1].raw-1;
	}

	encoder->data[idx_1].state[0] = encoder->data[idx0].state[0];
	encoder->data[idx_1].state[1] = encoder->data[idx0].state[1];
	encoder->data[idx_1].raw = encoder->data[idx0].raw;
//	encoder->idx = get_idx(encoder->idx, +1, IO_MAX_TIME_LOG);
}

void IO_ENCODER_HAS_INTERRUPT(io_encoder * encoder){

	if(__HAL_GPIO_EXTI_GET_IT(encoder->pin[0])){
			__HAL_GPIO_EXTI_CLEAR_IT(encoder->pin[0]);
//			encoder->data[0].state[0] = !encoder->data[0].state[0];
			IO_ENCODER_COUNTER(encoder);
			return;
	}else
	if(__HAL_GPIO_EXTI_GET_IT(encoder->pin[1])){
			__HAL_GPIO_EXTI_CLEAR_IT(encoder->pin[1]);
//			encoder->data[0].state[1] = !encoder->data[0].state[1];
			IO_ENCODER_COUNTER(encoder);
			return;
	}
}
