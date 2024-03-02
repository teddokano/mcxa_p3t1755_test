/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#define	IBI_TRIGGER_OUTPUT	D2

#define	PIN_OUTPUT			kGPIO_DigitalOutput
#define	PIN_INPUT			kGPIO_DigitalInput

#define RED_GPIO			BOARD_LED_RED_GPIO
#define GREEN_GPIO			BOARD_LED_GREEN_GPIO
#define BLUE_GPIO			BOARD_LED_BLUE_GPIO

#define RED_GPIO_PIN		BOARD_LED_RED_GPIO_PIN
#define GREEN_GPIO_PIN		BOARD_LED_GREEN_GPIO
#define BLUE_GPIO_PIN		BOARD_LED_BLUE_GPIO

#define D0_GPIO				BOARD_INITPINS_ARD_D0_GPIO
#define D1_GPIO				BOARD_INITPINS_ARD_D1_GPIO
#define D2_GPIO				BOARD_INITPINS_ARD_D2_GPIO
#define D3_GPIO				BOARD_INITPINS_ARD_D3_GPIO	//	BLUE
#define D4_GPIO				BOARD_INITPINS_ARD_D4_GPIO
#define D5_GPIO				BOARD_INITPINS_ARD_D5_GPIO	//	RED
#define D6_GPIO				BOARD_INITPINS_ARD_D6_GPIO	//	GREEN
#define D7_GPIO				BOARD_INITPINS_ARD_D7_GPIO
#define D8_GPIO				BOARD_INITPINS_ARD_D8_GPIO
#define D9_GPIO				BOARD_INITPINS_ARD_D9_GPIO
#define D10_GPIO			BOARD_INITPINS_ARD_D10_GPIO
#define D11_GPIO			BOARD_INITPINS_ARD_D11_GPIO
#define D12_GPIO			BOARD_INITPINS_ARD_D12_GPIO
#define D13_GPIO			BOARD_INITPINS_ARD_D13_GPIO
#define D18_GPIO			BOARD_INITPINS_ARD_D18_GPIO
#define D19_GPIO			BOARD_INITPINS_ARD_D19_GPIO

#define D0_GPIO_PIN			BOARD_INITPINS_ARD_D0_GPIO_PIN
#define D1_GPIO_PIN			BOARD_INITPINS_ARD_D1_GPIO_PIN
#define D2_GPIO_PIN			BOARD_INITPINS_ARD_D2_GPIO_PIN
#define D3_GPIO_PIN			BOARD_INITPINS_ARD_D3_GPIO_PIN
#define D4_GPIO_PIN			BOARD_INITPINS_ARD_D4_GPIO_PIN
#define D5_GPIO_PIN			BOARD_INITPINS_ARD_D5_GPIO_PIN
#define D6_GPIO_PIN			BOARD_INITPINS_ARD_D6_GPIO_PIN
#define D7_GPIO_PIN			BOARD_INITPINS_ARD_D7_GPIO_PIN
#define D8_GPIO_PIN			BOARD_INITPINS_ARD_D8_GPIO_PIN
#define D9_GPIO_PIN			BOARD_INITPINS_ARD_D9_GPIO_PIN
#define D10_GPIO_PIN		BOARD_INITPINS_ARD_D10_GPIO_PIN
#define D11_GPIO_PIN		BOARD_INITPINS_ARD_D11_GPIO_PIN
#define D12_GPIO_PIN		BOARD_INITPINS_ARD_D12_GPIO_PIN
#define D13_GPIO_PIN		BOARD_INITPINS_ARD_D13_GPIO_PIN
#define D18_GPIO_PIN		BOARD_INITPINS_ARD_D18_GPIO_PIN
#define D19_GPIO_PIN		BOARD_INITPINS_ARD_D19_GPIO_PIN

enum { D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D18, D19 };

#define	RED		D5
#define	GREEN	D6
#define	BLUE	D3

#define	PIN_LED_OFF	true
#define	PIN_LED_ON	false

void	init_pin( int num, int setting );
void	pin_toggle( int num );
void	pin_write( int num, bool value );

void	init_pins( void );
void	set_led_color( float temp, float ref );
void	all_led( bool v );
void	all_led_on( void );
void pin_led_control( int v );
void wait( float delayTime_sec );
