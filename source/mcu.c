/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "fsl_i3c.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "fsl_utick.h"
#include "fsl_clock.h"
#include "fsl_reset.h"

void init_mcu( void )
{
	/* Attach clock to I3C 24MHZ */
	CLOCK_SetClockDiv( kCLOCK_DivI3C0_FCLK, 2U );
	CLOCK_AttachClk( kFRO_HF_DIV_to_I3C0FCLK );

	CLOCK_EnableClock( kCLOCK_GateGPIO1 );
	CLOCK_EnableClock( kCLOCK_GateGPIO3 );
	CLOCK_EnableClock( kCLOCK_GateGPIO2 );

	RESET_PeripheralReset( kUTICK0_RST_SHIFT_RSTn );

	BOARD_InitPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	UTICK_Init( UTICK0 );
}

void wait( float delayTime_sec )
{
	SDK_DelayAtLeastUs( (uint32_t)(delayTime_sec * 1000000.0), CLOCK_GetCoreSysClkFreq() );
}
