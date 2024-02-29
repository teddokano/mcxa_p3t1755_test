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
status_t	enable_IBI( uint8_t addr );
float		short2celsius( uint16_t v );

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
	uint16_t	tmp;
	uint8_t	config	= P3T1755_CONFIG_VALUE;
	
	i3c_reg_write( P3T1755_ADDR_I3C, P3T1755_REG_Conf, &config, sizeof( config ) );
	i3c_reg_read(  P3T1755_ADDR_I3C, P3T1755_REG_Conf, &config, sizeof( config ) );
	PRINTF( "config:0x%02X\r\n", config );
	
	enable_IBI( P3T1755_ADDR_I3C );

	i3c_reg_read( P3T1755_ADDR_I3C, P3T1755_REG_Temp, (uint8_t *)&tmp, sizeof( tmp ) );
	PRINTF( " Temp reg read value: %8.4f\r\n", short2celsius( tmp ) );
	
	tmp++;	//	valid in little-endian system only
	i3c_reg_write( P3T1755_ADDR_I3C, P3T1755_REG_T_LOW, (uint8_t *)&tmp, sizeof( tmp ) );

	tmp++;	//	valid in little-endian system only
	i3c_reg_write( P3T1755_ADDR_I3C, P3T1755_REG_T_HIGH, (uint8_t *)&tmp, sizeof( tmp ) );

	i3c_reg_read( P3T1755_ADDR_I3C, P3T1755_REG_T_HIGH, (uint8_t *)&tmp, sizeof( tmp ) );
	PRINTF( " T_HIGH(0x03) = %8.4f\r\n", short2celsius( tmp ) );

	i3c_reg_read( P3T1755_ADDR_I3C, P3T1755_REG_T_LOW, (uint8_t *)&tmp, sizeof( tmp ) );
	PRINTF( " T_LOW (0x02) = %8.4f\r\n", short2celsius( tmp ) );	

	uint8_t	ibi_addr;
	
#endif // TRY_IBI

	while (1)
	{
#ifdef TRY_IBI
		if ( (ibi_addr	= i3c_check_ibi()) )
		{
			PRINTF("*** IBI : Got IBI from target_address: 7’h%02X (0x%02X)\n", ibi_addr, ibi_addr << 1 );
		}
#endif // TRY_IBI
		i3c_reg_read( P3T1755_ADDR_I3C, P3T1755_REG_Temp, &tmp, sizeof( tmp ) );

		PRINTF( "Temperature: %8.4f \r\n", short2celsius( tmp ) );
		SDK_DelayAtLeastUs(1000000, CLOCK_GetCoreSysClkFreq());
	}
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

status_t enable_IBI( uint8_t addr )
{
	static const uint8_t	ccc		= CCC_ENEC;
	static const uint8_t	set_int	= 0x01;

	i3c_write( I3C_BROADCAST_ADDR, &ccc, 1, false );
	i3c_write( addr, &set_int, 1, true  );
}

float short2celsius( uint16_t v )
{
	return (float)(((v & 0x00FF) << 4) | ((v & 0xFF00) >> 12)) * 0.0625;
}

