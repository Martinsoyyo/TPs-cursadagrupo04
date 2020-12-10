#ifndef GPIO_H
#define GPIO_H

//#include "common_define.h"
#include <chip.h>
#include <lpc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	scu_MODE_PULLUP 			= (0x0 << 3),/*!< Enable pull-up resistor at pad */
	scu_MODE_REPEATER 			= (0x1 << 3),/*!< Enable pull-down and pull-up resistor at resistor at pad (repeater mode) */
	scu_MODE_INACT 				= (0x2 << 3),/*!< Disable pull-down and pull-up resistor at resistor at pad */
	scu_MODE_PULLDOWN 			= (0x3 << 3),/*!< Enable pull-down resistor at pad */
	scu_MODE_HIGHSPEEDSLEW_EN 	= (0x1 << 5),/*!< Enable high-speed slew */
	scu_MODE_INBUFF_EN 			= (0x1 << 6),/*!< Enable Input buffer */
	scu_MODE_ZIF_DIS 			= (0x1 << 7),/*!< Disable input glitch filter */
	scu_MODE_4MA_DRIVESTR 		= (0x0 << 8),/*!< Normal drive: 4mA drive strength */
	scu_MODE_8MA_DRIVESTR 		= (0x1 << 8),/*!< Medium drive: 8mA drive strength */
	scu_MODE_14MA_DRIVESTR 		= (0x2 << 8),/*!< High drive: 14mA drive strength */
	scu_MODE_20MA_DRIVESTR 		= (0x3 << 8),/*!< Ultra high- drive: 20mA drive strength */
	scu_MODE_FUNC0 				= 0x0,/*!< Selects pin function 0 */
	scu_MODE_FUNC1 				= 0x1,/*!< Selects pin function 1 */
	scu_MODE_FUNC2 				= 0x2,/*!< Selects pin function 2 */
	scu_MODE_FUNC3 				= 0x3,/*!< Selects pin function 3 */
	scu_MODE_FUNC4 				= 0x4,/*!< Selects pin function 4 */
	scu_MODE_FUNC5 				= 0x5,/*!< Selects pin function 5 */
	scu_MODE_FUNC6 				= 0x6,/*!< Selects pin function 6 */
	scu_MODE_FUNC7 				= 0x7,/*!< Selects pin function 7 */
	scu_PINIO_FAST				= (scu_MODE_INACT | scu_MODE_HIGHSPEEDSLEW_EN | scu_MODE_INBUFF_EN | scu_MODE_ZIF_DIS)
} _gpioInit_t;

typedef enum {
	_INPUT,
	_OUTPUT,
	_OTHER
} _gpio_mode_t;

typedef struct {
	int8_t 		scu_port;
	int8_t		scu_pin;
	int8_t		scu_func;
	_gpio_mode_t gpio_mode;
	int8_t		gpio_port;
	int8_t		gpio_pin;
} _conf_t;

static const _conf_t _gpioPinsInit[] = {
	    /* Board LEDs */
	    {2, 0, (scu_MODE_INBUFF_EN | scu_MODE_PULLUP | scu_MODE_FUNC4) , _OUTPUT , 5, 0 },/* 0 */
	    {2, 1, (scu_MODE_INBUFF_EN | scu_MODE_PULLUP | scu_MODE_FUNC4) , _OUTPUT , 5, 1 },/* 1 */
	    {2, 2, (scu_MODE_INBUFF_EN | scu_MODE_PULLUP | scu_MODE_FUNC4) , _OUTPUT , 5, 2 },/* 2 */
	    {2, 10,(scu_MODE_INBUFF_EN | scu_MODE_PULLUP | scu_MODE_FUNC0) , _OUTPUT , 0, 14},/* 3 */
	    {2, 11,(scu_MODE_INBUFF_EN | scu_MODE_PULLUP | scu_MODE_FUNC0) , _OUTPUT , 1, 11},/* 4 */
	    {2, 12,(scu_MODE_INBUFF_EN | scu_MODE_PULLUP | scu_MODE_FUNC0) , _OUTPUT , 1, 12},/* 5 */

	    /* Board Buttons */
	    {1, 0, (scu_MODE_INBUFF_EN | scu_MODE_INACT | scu_MODE_FUNC0) , _INPUT , 0, 4 },/* 6 */
	    {1, 1, (scu_MODE_INBUFF_EN | scu_MODE_INACT | scu_MODE_FUNC0) , _INPUT , 0, 8 },/* 7 */
	    {1, 2, (scu_MODE_INBUFF_EN | scu_MODE_INACT | scu_MODE_FUNC0) , _INPUT , 0, 9 },/* 8 */
	    {1, 6, (scu_MODE_INBUFF_EN | scu_MODE_INACT | scu_MODE_FUNC0) , _INPUT , 1, 9 },/* 9 */
};

enum _GpioMap_t {
	_LED1 = 3,
	_LED2 = 4,
	_LED3 = 5,
	_LEDR = 0,
	_LEDG = 1,
	_LEDB = 2,
	_TEC_1 = 6,
	_TEC_2 = 7,
	_TEC_3 = 8,
	_TEC_4 = 9,
};

static inline void GpioInit(int8_t PIN)
{
	Chip_SCU_PinMuxSet(
			_gpioPinsInit[PIN].scu_port,
			_gpioPinsInit[PIN].scu_pin,
			_gpioPinsInit[PIN].scu_func
			);

	Chip_GPIO_SetDir(
			LPC_GPIO_PORT,
			_gpioPinsInit[PIN].gpio_port,
			_gpioPinsInit[PIN].gpio_pin,
			_gpioPinsInit[PIN].gpio_mode
			);
}


static inline void GpioWrite(int8_t PIN, bool VALUE )
{
	Chip_GPIO_WritePortBit(
			LPC_GPIO_PORT,
			_gpioPinsInit[PIN].gpio_port,
			_gpioPinsInit[PIN].gpio_pin,
			VALUE
			);
}


static inline  bool GpioRead(int8_t PIN )
{
	volatile bool ret = Chip_GPIO_ReadPortBit(
			LPC_GPIO_PORT,
			_gpioPinsInit[PIN].gpio_port,
			_gpioPinsInit[PIN].gpio_pin
			);

	return ret;
}


#ifdef __cplusplus
}
#endif

#endif
