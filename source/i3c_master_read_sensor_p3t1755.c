/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  Standard C Included Files */
#include <string.h>
/*  SDK Included Files */
#include "fsl_debug_console.h"
#include "fsl_i3c.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "i3c.h"
#include "p3t1755.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define	HIGHER_SCL_FREEQ
#define	TRY_IBI

#ifdef	HIGHER_SCL_FREEQ
#define EXAMPLE_I3C_OD_BAUDRATE		4000000
#define EXAMPLE_I3C_PP_BAUDRATE		12500000
#else
#define EXAMPLE_I3C_OD_BAUDRATE		1500000
#define EXAMPLE_I3C_PP_BAUDRATE		4000000
#endif //HIGHER_SCL_FREEQ

#define EXAMPLE_I2C_BAUDRATE		400000

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void		init_MCU( void );
void		init_I3C( void );
float		temp_sensor_setting( uint8_t addr, uint8_t config );
void		temp_sensor_reg_dump( uint8_t addr );
float		read_temp( uint8_t targ, uint8_t reg );
void		write_temp( uint8_t targ, uint8_t reg, float v );
float		short2celsius( uint16_t v );
uint16_t	celsius2short( float v );
uint16_t	swap_bytes( uint16_t v );

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

int main(void)
{
	init_MCU();
	i3c_init( EXAMPLE_I2C_BAUDRATE, EXAMPLE_I3C_OD_BAUDRATE, EXAMPLE_I3C_PP_BAUDRATE );
	
	PRINTF("\r\nI3C master read sensor data example.\r\n");

	//	Try DAA
	i3c_change_target_address( P3T1755_ADDR_I2C, P3T1755_ADDR_I3C << 1 );

	float	temp;
	temp	= temp_sensor_setting( P3T1755_ADDR_I3C, P3T1755_CONFIG_VALUE );
	PRINTF( "  T_HIGH and T_LOW registers are set based on current temperature: %8.4f\r\n", temp );
	
	temp_sensor_reg_dump( P3T1755_ADDR_I3C );

	uint8_t	ibi_addr;
	
	while (1)
	{
		if ( (ibi_addr	= i3c_check_IBI()) )
			PRINTF("*** IBI : Got IBI from target_address: 7’h%02X (0x%02X)\n", ibi_addr, ibi_addr << 1 );

		temp	= read_temp( P3T1755_ADDR_I3C, P3T1755_REG_Temp );

		PRINTF( "Temperature: %8.4f˚C\r\n", temp );
		SDK_DelayAtLeastUs(1000000, CLOCK_GetCoreSysClkFreq());
	}
}

float temp_sensor_setting( uint8_t addr, uint8_t config )
{
	float	temp, high, low;
	
	i3c_reg_write( addr, P3T1755_REG_Conf, &config, sizeof( config ) );

	temp	= read_temp( addr, P3T1755_REG_Temp );
	high	= temp + 2.0;
	low		= temp + 1.0;
	
	write_temp( addr, P3T1755_REG_T_HIGH, high );
	write_temp( addr, P3T1755_REG_T_LOW,  low  );

	i3c_enable_IBI( addr );
	
	return temp;
}

void temp_sensor_reg_dump( uint8_t addr )
{
	uint16_t	t, h, l;
	uint8_t		c;
	
	i3c_reg_read( addr, P3T1755_REG_Temp,   &t, sizeof( t ) );
	i3c_reg_read( addr, P3T1755_REG_Conf,   &c, sizeof( c ) );
	i3c_reg_read( addr, P3T1755_REG_T_LOW,  &h, sizeof( h ) );
	i3c_reg_read( addr, P3T1755_REG_T_HIGH, &l, sizeof( l ) );

	PRINTF( "\r\n  P3T1755 (I3C target address:7’h%02X (0x%02X)) register dump\r\n", P3T1755_ADDR_I3C, P3T1755_ADDR_I3C << 1 );	
	PRINTF( "  * Temp   (0x0): 0x%04X (%8.4f˚C)\r\n", swap_bytes( t ), short2celsius( t ) );	
	PRINTF( "  * Conf   (0x1): 0x  %02X\r\n", c );	
	PRINTF( "  * T_LOW  (0x2): 0x%04X (%8.4f˚C)\r\n", swap_bytes( l ), short2celsius( l ) );	
	PRINTF( "  * T_HIGH (0x3): 0x%04X (%8.4f˚C)\r\n", swap_bytes( h ), short2celsius( h ) );	
	PRINTF( "\r\n" );	
}

float read_temp( uint8_t targ, uint8_t reg )
{
	uint16_t	tmp;
	i3c_reg_read( targ, reg, (uint8_t *)&tmp, sizeof( tmp ) );
	
	return short2celsius( tmp );
}

void write_temp( uint8_t targ, uint8_t reg, float v )
{
	uint16_t	tmp	= celsius2short( v );
	i3c_reg_write( targ, reg, (uint8_t *)&tmp, sizeof( tmp ) );
}

float short2celsius( uint16_t v )
{
	static const float	k	= 1 / 256.0;
	return (float)(swap_bytes( v )) * k;
}

uint16_t celsius2short( float v )
{
	return swap_bytes( (uint16_t)(v * 256.0) );
}

uint16_t swap_bytes( uint16_t v )
{
#ifdef __BIG_ENDIAN__
	return v;
#else	
	return (v << 8) | (v >> 8);
#endif
}

void init_MCU( void )
{
	/* Attach clock to I3C 24MHZ */
	CLOCK_SetClockDiv(kCLOCK_DivI3C0_FCLK, 2U);
	CLOCK_AttachClk(kFRO_HF_DIV_to_I3C0FCLK);

	BOARD_InitPins();
	BOARD_BootClockFRO48M();
	BOARD_InitDebugConsole();
}
