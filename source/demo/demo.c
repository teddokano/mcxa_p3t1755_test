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

#define	LENGTH		10
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
	static uint32_t		index	= 0;
	float				avg		= 0.0;
	uint32_t			lim;

	led_set_color( temp, *ref_temp_ptr );
	
	samples[ index++ % LENGTH ]	= temp;

	lim	= (index < LENGTH) ? index : LENGTH;
	
	for ( int i = 0; i < lim; i++ )
		avg	+= samples[ i ];
	
	avg	/= lim;

	if ( ((*ref_temp_ptr - THRESHOLD) < avg) && (avg < (*ref_temp_ptr + THRESHOLD)) )
		return;

	*ref_temp_ptr	= avg;
	PRINTF( "Minimum temperature for last %d samples are changed\r\n", LENGTH );
	
	func_ptr( P3T1755_ADDR_I3C, P3T1755_CONFIG_VALUE );;
}
