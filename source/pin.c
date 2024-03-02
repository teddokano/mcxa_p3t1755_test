/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "fsl_gpio.h"

#include "pin.h"

typedef	struct	_gpio_pin {
	GPIO_Type	*base;
	uint32_t	pin;
} gpio_pin;

static gpio_pin pins[]	= {
	{ D0_GPIO, D0_GPIO_PIN },
	{ D1_GPIO, D1_GPIO_PIN },
	{ D2_GPIO, D2_GPIO_PIN },
	{ D3_GPIO, D3_GPIO_PIN },
	{ D4_GPIO, D4_GPIO_PIN },
	{ D5_GPIO, D5_GPIO_PIN },
	{ D6_GPIO, D6_GPIO_PIN },
	{ D7_GPIO, D7_GPIO_PIN },
	{ D8_GPIO, D8_GPIO_PIN },
	{ D9_GPIO, D9_GPIO_PIN },
	{ D10_GPIO, D10_GPIO_PIN },
	{ D11_GPIO, D11_GPIO_PIN },
	{ D12_GPIO, D12_GPIO_PIN },
	{ D13_GPIO, D13_GPIO_PIN },
	{ D18_GPIO, D18_GPIO_PIN },
	{ D19_GPIO, D19_GPIO_PIN }
};

void init_pin( int num, int setting )
{
	gpio_pin_config_t led_config = { kGPIO_DigitalOutput, 0 };

	GPIO_PinInit( pins[ num ].base, pins[ num ].pin, &led_config );
}

void pin_toggle( int num )
{
	GPIO_PortToggle( pins[ num ].base, 1u << pins[ num ].pin );
}

void pin_write( int num, bool value )
{
	GPIO_PinWrite( pins[ num ].base, pins[ num ].pin, value );
}

void init_pins( void )
{
	uint8_t	pins[]	= { RED, GREEN, BLUE };

	for ( int i = 0; i < sizeof( pins ); i++ )
	{
		init_pin( pins[ i ], PIN_OUTPUT );
		pin_write( pins[ i ], false ); wait( 0.1 );
		pin_write( pins[ i ], true  ); wait( 0.1 );
	}
	
	init_pin( IBI_TRIGGER_OUTPUT, PIN_OUTPUT );	
}

void set_led_color( float temp, float ref )
{
	if ( (ref + 2) < temp )
	{
		pin_write( RED,   PIN_LED_ON  );
		pin_write( GREEN, PIN_LED_OFF );
		pin_write( BLUE,  PIN_LED_OFF );
	}
	else if ( (ref + 1) < temp )
	{
		pin_write( RED,   PIN_LED_OFF );
		pin_write( GREEN, PIN_LED_ON  );
		pin_write( BLUE,  PIN_LED_OFF );
	}
	else
	{
		pin_write( RED,   PIN_LED_OFF );
		pin_write( GREEN, PIN_LED_OFF );
		pin_write( BLUE,  PIN_LED_ON  );
	}
	
	pin_write( IBI_TRIGGER_OUTPUT, true );
}

void all_led_on( void )
{
	pin_write( IBI_TRIGGER_OUTPUT, false );
	pin_write( RED,   PIN_LED_ON );
	pin_write( GREEN, PIN_LED_ON );
	pin_write( BLUE,  PIN_LED_ON );
}
