#ifndef __MAIN_H__
#define __MAIN_H__

#include "GPIO.h"

static inline void Board_GPIO_Init()
{
	GpioInit(LED1);
	GpioInit(LED2);
	GpioInit(LED3);
	GpioInit(LEDR);
	GpioInit(LEDG);
	GpioInit(LEDB);

	GpioInit(TEC_1);
	GpioInit(TEC_2);
	GpioInit(TEC_3);
	GpioInit(TEC_4);
}

#endif
