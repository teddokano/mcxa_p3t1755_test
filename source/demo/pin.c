/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "fsl_gpio.h"

#include	"mcu.h"
#include	"pin.h"

typedef	struct	_gpio_pin {
	GPIO_Type	*base;
	uint32_t	pin;
} gpio_pin;

static gpio_pin pins[]	= {
	{ D0_GPIO,  D0_GPIO_PIN  },
	{ D1_GPIO,  D1_GPIO_PIN  },
	{ D2_GPIO,  D2_GPIO_PIN  },
	{ D3_GPIO,  D3_GPIO_PIN  },
	{ D4_GPIO,  D4_GPIO_PIN  },
	{ D5_GPIO,  D5_GPIO_PIN  },
	{ D6_GPIO,  D6_GPIO_PIN  },
	{ D7_GPIO,  D7_GPIO_PIN  },
	{ D8_GPIO,  D8_GPIO_PIN  },
	{ D9_GPIO,  D9_GPIO_PIN  },
	{ D10_GPIO, D10_GPIO_PIN },
	{ D11_GPIO, D11_GPIO_PIN },
	{ D12_GPIO, D12_GPIO_PIN },
	{ D13_GPIO, D13_GPIO_PIN },
	{ D18_GPIO, D18_GPIO_PIN },
	{ D19_GPIO, D19_GPIO_PIN },
	{ A0_GPIO,  A0_GPIO_PIN  },
	{ A1_GPIO,  A1_GPIO_PIN  },
	{ A2_GPIO,  A2_GPIO_PIN  },
	{ A3_GPIO,  A3_GPIO_PIN  },
	{ A4_GPIO,  A4_GPIO_PIN  },
	{ A5_GPIO,  A5_GPIO_PIN  }
};

void init_pin( int num, int setting )
{
	if ( NULL == pins[ num ].base )
		return;
	
	gpio_pin_config_t led_config = { setting, 0 };

	GPIO_PinInit( pins[ num ].base, pins[ num ].pin, &led_config );
}

void pin_toggle( int num )
{
	if ( NULL == pins[ num ].base )
		return;

	GPIO_PortToggle( pins[ num ].base, 1u << pins[ num ].pin );
}

void pin_write( int num, bool value )
{
	if ( NULL == pins[ num ].base )
		return;

	GPIO_PinWrite( pins[ num ].base, pins[ num ].pin, value );
}


#include	"mcu.h"

void pin_test( void )
{
	for ( int i = 0; i < sizeof( pins ) / sizeof( gpio_pin ); i++ )
	{
		init_pin( i, PIN_OUTPUT );
		pin_write( i, false );
	}

	for ( int i = 0; i < sizeof( pins ) / sizeof( gpio_pin ); i++ )
	{
		for ( int j = 0; j < (i + 1); j++ )
		{
			pin_write( i, true );
			wait( 0.01 );
			pin_write( i, false );
			wait( 0.01 );
		}
	}
}
