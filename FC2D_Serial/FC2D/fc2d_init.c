#include "io_defines.h"
#include "fc2d_config.h"

io_encoder	encoder_0;
io_force	force_0;
io_actuator	actuator_0;

void fc2d_init(void){
	encoder_0.pin[0]=GPIO_PIN_14;
	encoder_0.pin[1]=GPIO_PIN_15;
	encoder_0.port[0]=GPIOC;
	encoder_0.port[1]=GPIOC;
	encoder_0.IRQ[0] = EXTI15_10_IRQn;
	encoder_0.IRQ[1] = EXTI15_10_IRQn;

	IO_ENCODER_INIT(&encoder_0);
}
