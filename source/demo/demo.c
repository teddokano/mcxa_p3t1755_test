/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include	"config.h"

#include	"fsl_debug_console.h"

#include	"i3c/i3c.h"
#include	"demo/demo.h"
#include	"demo/led_control.h"
#include	"demo/pin.h"
#include	"p3t1755.h"

void trigger_output( void );

void init_demo( void )
{
	init_led();
	set_IBI_callback( trigger_output );
}

void demo( float temp, float *ref_temp_ptr, float (*func_ptr)(uint8_t,uint8_t) )
{
	led_set_color( temp, *ref_temp_ptr );
}

void trigger_output( void )
{
	pin_write( IBI_TRIGGER_OUTPUT, false );
}
