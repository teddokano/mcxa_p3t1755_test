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
	static uint32_t		index	= 0;
	float				max		= -125.0;
	float				min		=  125.0;
	float				avg		=    0.0;
	float				tmp;
	float				compare;
	uint32_t			lim;
	int					max_index	= 0;
	int					min_index	= 0;
	int					local_index;
	
	led_set_color( temp, *ref_temp_ptr );
	
	samples[ index++ % LENGTH ]	= temp;

	lim	= (index < LENGTH) ? index : LENGTH;
	
	if (lim < LENGTH)
		return;
	
	for ( int i = 0; i < lim; i++ )
	{
		tmp	 		 = samples[ i ];
		local_index	 = (i + (index - 1)) % LENGTH;
		
		max_index	 = (max < tmp) ? local_index : max_index;
		min_index	 = (tmp < min) ? local_index : min_index;

		max	 = (max < tmp) ? tmp : max;
		min	 = (tmp < min) ? tmp : min;
		avg	+= samples[ i ];
	}
	
	avg	/= lim;

	if ( ((*ref_temp_ptr - THRESHOLD) < min) && (min < (*ref_temp_ptr + THRESHOLD)) )
		return;

	if ( 2.0 < (max - min) )
		*ref_temp_ptr	= (max_index < min_index) ? min : max;
	else
		*ref_temp_ptr	= min;		

	PRINTF( "Recent temperature for last %d samples are changed from previous one. Changed to %8.4f˚C\r\n", lim, *ref_temp_ptr );
	
	func_ptr( P3T1755_ADDR_I3C, P3T1755_CONFIG_VALUE );;
}
