/*
 * Copyright 2022 NXP
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This code based on a sample projects: 
 *    "frdmmcxa153_i3c_master_read_sensor_p3t1755" from SDK_2.14.2_FRDM-MCXA153 and 
 *    "lpcxpresso860max_i3c_master_read_sensor_icm42688p" from SDK_2.15.000_LPCXpresso860MAX
 */

#include <string.h>

#include "fsl_debug_console.h"
#include "fsl_i3c.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "i3c.h"
#include "p3t1755.h"

#define	HIGHER_SCL_FREEQ

#ifdef	HIGHER_SCL_FREEQ
#define EXAMPLE_I3C_OD_BAUDRATE		4000000
#define EXAMPLE_I3C_PP_BAUDRATE		12500000
#else
#define EXAMPLE_I3C_OD_BAUDRATE		1500000
#define EXAMPLE_I3C_PP_BAUDRATE		4000000
#endif //HIGHER_SCL_FREEQ

#define EXAMPLE_I2C_BAUDRATE		400000

void		init_MCU( void );
void		init_I3C( void );
float		temp_sensor_setting( uint8_t addr, uint8_t config );
void		temp_sensor_reg_dump( uint8_t addr );
float		read_temp( uint8_t targ, uint8_t reg );
void		write_temp( uint8_t targ, uint8_t reg, float v );
float		short2celsius( uint16_t v );
uint16_t	celsius2short( float v );
uint16_t	swap_bytes( uint16_t v );
void		wait( float delayTime_sec );

int main(void)
{
	init_MCU();
	i3c_init( EXAMPLE_I2C_BAUDRATE, EXAMPLE_I3C_OD_BAUDRATE, EXAMPLE_I3C_PP_BAUDRATE );
	
	PRINTF("\r\nI3C master example: reading P3T1755 data and get IBI\r\n");

	//	Try DAA
	ccc_broadcast( CCC_BROADCAST_RSTDAA, NULL, 0 ); // Reset DAA
	ccc_set( CCC_DIRECT_SETDASA, P3T1755_ADDR_I2C, P3T1755_ADDR_I3C << 1 ); // Set Dynamic Address from Static Address

	float	temp;
	temp	= temp_sensor_setting( P3T1755_ADDR_I3C, P3T1755_CONFIG_VALUE );
	PRINTF( "  T_HIGH and T_LOW registers are set based on current temperature: %8.4f˚C\r\n", temp );
	
	temp_sensor_reg_dump( P3T1755_ADDR_I3C );

	uint8_t	ibi_addr;
	
	while (1)
	{
		if ( (ibi_addr	= i3c_check_IBI()) )
			PRINTF("*** IBI : Got IBI from target_address: 7’h%02X (0x%02X)\n", ibi_addr, ibi_addr << 1 );

		temp	= read_temp( P3T1755_ADDR_I3C, P3T1755_REG_Temp );

		PRINTF( "Temperature: %8.4f˚C\r\n", temp );
		wait( 1 );
	}
}

float temp_sensor_setting( uint8_t addr, uint8_t config )
{
	float	temp, high, low;
	
	i3c_reg_write( addr, P3T1755_REG_Conf, &config, sizeof( config ) );

	temp	= read_temp( addr, P3T1755_REG_Temp );
	low		= temp + 1.0;
	high	= temp + 2.0;
	
	write_temp( addr, P3T1755_REG_T_LOW,  low  );
	write_temp( addr, P3T1755_REG_T_HIGH, high );

	//	Enable IBI
	ccc_set( CCC_DIRECT_ENEC, addr, 0x01 );

	return temp;
}

void temp_sensor_reg_dump( uint8_t addr )
{
	uint16_t	t, l, h;
	uint8_t		c;
	uint8_t		pid[ PID_LENGTH ];
	uint8_t		bcr, dcr;
	
	i3c_reg_read( addr, P3T1755_REG_Temp,   (uint8_t *)&t, sizeof( t ) );
	i3c_reg_read( addr, P3T1755_REG_Conf,              &c, sizeof( c ) );
	i3c_reg_read( addr, P3T1755_REG_T_LOW,  (uint8_t *)&l, sizeof( l ) );
	i3c_reg_read( addr, P3T1755_REG_T_HIGH, (uint8_t *)&h, sizeof( h ) );

	ccc_get( CCC_DIRECT_GETPID, addr, pid, sizeof( pid ) );
	ccc_get( CCC_DIRECT_GETBCR, addr, &bcr, 1 );
	ccc_get( CCC_DIRECT_GETDCR, addr, &dcr, 1 );

	PRINTF( "\r\n  P3T1755 register dump - I3C target address:7’h%02X (0x%02X)\r\n", P3T1755_ADDR_I3C, P3T1755_ADDR_I3C << 1 );	
	PRINTF( "  - Temp   (0x0): 0x%04X (%8.4f˚C)\r\n", swap_bytes( t ), short2celsius( t ) );	
	PRINTF( "  - Conf   (0x1): 0x  %02X\r\n", c );	
	PRINTF( "  - T_LOW  (0x2): 0x%04X (%8.4f˚C)\r\n", swap_bytes( l ), short2celsius( l ) );	
	PRINTF( "  - T_HIGH (0x3): 0x%04X (%8.4f˚C)\r\n", swap_bytes( h ), short2celsius( h ) );	
	
	PRINTF( "  * PID    (CCC:Provisioned ID)                 : 0x" );
	for ( int i = 0; i < PID_LENGTH; i++ ) PRINTF( " %02X", pid[ i ] );	PRINTF( "\r\n" );
	PRINTF( "  * BCR    (CCC:Bus Characteristics Register)   : 0x%02X\r\n", bcr );
	PRINTF( "  * DCR    (CCC:Device Characteristics Register): 0x%02X (= %s)\r\n", dcr, (0x63 == dcr) ? "Temperature sensor" : "Unknown" );

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

void wait( float delayTime_sec )
{
	SDK_DelayAtLeastUs( (uint32_t)(delayTime_sec * 1000000.0), CLOCK_GetCoreSysClkFreq() );
}
