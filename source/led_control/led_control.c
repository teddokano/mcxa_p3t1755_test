/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include	"fsl_utick.h"

#include	"mcu.h"
#include	"led_control/pin.h"
#include	"led_control/pwm.h"
#include	"led_control/led_control.h"

void init_pins( void );


static void led_control_callback(void)
{
	pwm_update();
}


void init_led( void )
{
	init_pins();
	pwm_start();
	UTICK_SetTick( UTICK0, kUTICK_Repeat, 10000 - 1, led_control_callback );
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

volatile int target_led	= BLUE;

void led_set_color0( float temp, float ref )
{
	if ( (ref + 2) < temp )
	{
		target_led	= RED;
	}
	else if ( (ref + 1) < temp )
	{
		target_led	= GREEN;
	}
	else
	{
		target_led	= BLUE;
	}
	pin_write( IBI_TRIGGER_OUTPUT, true );
}

void led_set_color( float temp, float ref )
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

void led_all( bool v )
{
	pin_write( IBI_TRIGGER_OUTPUT, false );
	pin_write( RED,   v );
	pin_write( GREEN, v );
	pin_write( BLUE,  v );
}

void led_pin_control( int v )
{
	if ( !(v % 2) )
		led_all( PIN_LED_OFF );

	if ( v % 2 )
	pin_write( target_led, PIN_LED_ON );
}
