#ifndef __FC2D_CONFIG_
#define __FC2D_CONFIG_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

#include "io_defines.h"

/* I/O */

#define ENCODER_0__A0_PIN   GPIO_PIN_8
#define ENCODER_0__A0_PORT  GPIOA
#define ENCODER_0__A1_PIN   GPIO_PIN_8
#define ENCODER_0__A1_PORT	GPIOA
#define ENCODER_0__B0_PIN   GPIO_PIN_8
#define ENCODER_0__B0_PORT	GPIOA
#define ENCODER_0__B1_PIN	GPIO_PIN_8
#define ENCODER_0__B1_PORT	GPIOA

#define FORCE_0__PIN  GPIO_PIN_8
#define FORCE_0__PORT GPIOA

#define ACTUATOR_0__PIN  GPIO_PIN_8
#define ACTUATOR_0__PORT GPIOA

/* Constants */

#define ENCODER_0__Q 1024

#define FORCE_0__Q 1024

/* IO structures  */

extern io_encoder	encoder_0;
extern io_force		force_0;
extern io_actuator	actuator_0;


void fc2d_init(void);

#ifdef __cplusplus
}
#endif

#endif
