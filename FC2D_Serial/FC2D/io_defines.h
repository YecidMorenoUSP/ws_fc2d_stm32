#ifndef __IO_DEFINES__
#define __IO_DEFINES__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f429xx.h"
#include <stdio.h>


#define IO_MAX_TIME_LOG 4

typedef struct {
	uint32_t state[2];
	int32_t raw;
	uint32_t time;
	float x;
	float dx;
	float x_f;
	float dx_f;
}io_encoder_data;

typedef struct {
	uint16_t pin [4]; //A0 B0 A1 B1
	GPIO_TypeDef * port[4]; //A0 B0 A1 B1
	IRQn_Type IRQ[2];
	uint16_t zero;
	int8_t  idx;
	io_encoder_data data[IO_MAX_TIME_LOG];
}io_encoder;

typedef struct {
	int32_t raw;
	uint32_t time;
	float  f;
	float df;
	float  f_f;
	float df_f;
}io_force_data;

typedef struct {
	uint16_t pin;
	uint16_t port;
	uint8_t  idx;
	io_force_data data[IO_MAX_TIME_LOG];
}io_force;

typedef struct {
	int32_t raw;
	uint32_t time;
	float u;
}io_actuator_data;

typedef struct {
	uint16_t pin;
	uint16_t port;
	uint8_t  idx;
	io_actuator_data data[IO_MAX_TIME_LOG];
}io_actuator;

typedef struct {
	io_encoder	encoder;
	io_force	force;
	io_actuator actuator;
}io_fc2d_node;

void IO_ENCODER_INIT(io_encoder * encoder);
void IO_ENCODER_HAS_INTERRUPT(io_encoder * encoder);
void IO_ENCODER_COUNTER(io_encoder * encoder);

#ifdef __cplusplus
}
#endif

#endif
