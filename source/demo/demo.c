/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include	"fsl_debug_console.h"
#include	"demo/demo.h"
#include	"demo/led_control.h"
#include	"p3t1755.h"


void init_demo( void )
{
	init_led();
}

void demo( float temp, float *ref_temp_ptr, float (*func_ptr)(uint8_t,uint8_t) )
{
	led_set_color( temp, *ref_temp_ptr );
}
