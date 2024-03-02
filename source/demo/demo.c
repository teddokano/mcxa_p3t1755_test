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

#define	LENGTH		60
#define	THRESHOLD	1.0

static float	samples[ LENGTH ];

void init_demo( void )
{
	init_led();
	
	for ( int i = 0; i < LENGTH; i++ )
		samples[ i ]	= 125.0;
}

void demo( float temp, float *ref_temp_ptr, float (*func_ptr)(uint8_t,uint8_t) )
{
	static int		index				= 0;
	float			min					= 125.0;

	led_set_color( temp, *ref_temp_ptr );
	
	index	%= LENGTH;

	samples[ index++ ]	= temp;

	for ( int i = 0; i < LENGTH; i++ )
		min	= (samples[ i ] < min) ? samples[ i ] : min;

	if ( ((*ref_temp_ptr - THRESHOLD) < min) && (min < (*ref_temp_ptr + THRESHOLD)) )
		return;

	*ref_temp_ptr	= min;
	
	PRINTF( "Minimum temperature for last %d samples are changed\r\n", LENGTH );

	func_ptr( P3T1755_ADDR_I3C, P3T1755_CONFIG_VALUE );
}
