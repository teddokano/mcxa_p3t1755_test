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
float		read_temp( uint8_t targ, uint8_t reg );
void		write_temp( uint8_t targ, uint8_t reg, float v );
float		short2celsius( uint16_t v );
uint16_t	celsius2short( float v );

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

#ifdef TRY_IBI
	float	temp;
	uint8_t	config	= P3T1755_CONFIG_VALUE;
	
	i3c_reg_write( P3T1755_ADDR_I3C, P3T1755_REG_Conf, &config, sizeof( config ) );
	i3c_reg_read(  P3T1755_ADDR_I3C, P3T1755_REG_Conf, &config, sizeof( config ) );
	PRINTF( "config:0x%02X\r\n", config );
	
	i3c_enable_IBI( P3T1755_ADDR_I3C );

	temp	= read_temp( P3T1755_ADDR_I3C, P3T1755_REG_Temp );
	PRINTF( " Temp reg read value: %8.4f\r\n", temp );
	
	write_temp( P3T1755_ADDR_I3C, P3T1755_REG_T_HIGH, temp + 2.0 );
	write_temp( P3T1755_ADDR_I3C, P3T1755_REG_T_LOW,  temp + 1.0 );
	
	temp	= read_temp( P3T1755_ADDR_I3C, P3T1755_REG_T_HIGH );
	PRINTF( " T_HIGH(0x03) = %8.4f\r\n", temp );

	temp	= read_temp( P3T1755_ADDR_I3C, P3T1755_REG_T_LOW  );
	PRINTF( " T_LOW (0x02) = %8.4f\r\n", temp );	

	uint8_t	ibi_addr;
	
#endif // TRY_IBI

	while (1)
	{
#ifdef TRY_IBI
		if ( (ibi_addr	= i3c_check_IBI()) )
		{
			PRINTF("*** IBI : Got IBI from target_address: 7’h%02X (0x%02X)\n", ibi_addr, ibi_addr << 1 );
		}
#endif // TRY_IBI
		temp	= read_temp( P3T1755_ADDR_I3C, P3T1755_REG_Temp );

		PRINTF( "Temperature: %8.4f \r\n", temp );
		SDK_DelayAtLeastUs(1000000, CLOCK_GetCoreSysClkFreq());
	}
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
#ifdef __BIG_ENDIAN__
	return (float)v * 0.0625;
#else
	return (float)(((v & 0x00FF) << 4) | ((v & 0xFF00) >> 12)) * 0.0625;
#endif
}

uint16_t celsius2short( float v )
{
	uint16_t tmp	= (uint16_t)(v * 256.0);

#ifdef __BIG_ENDIAN__
	return tmp;
#else	
	return (uint16_t)((tmp << 8) | (tmp >> 8));
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
