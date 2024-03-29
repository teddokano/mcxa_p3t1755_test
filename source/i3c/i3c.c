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

#include	<string.h>

#include	"fsl_i3c.h"
#include	"i3c.h"

#define	REG_RW_BUFFER_SIZE			10
#define	IBI_PAYLOAD_BUFFER_SIZE		10

#define EXAMPLE_MASTER				I3C0
#define I3C_MASTER_CLOCK_FREQUENCY	CLOCK_GetI3CFClkFreq()

uint8_t					g_ibiBuff[ IBI_PAYLOAD_BUFFER_SIZE ];
static uint8_t			g_ibiUserBuff[ IBI_PAYLOAD_BUFFER_SIZE ];
static uint8_t			g_ibiUserBuffUsed	= 0;
static volatile bool	g_ibiWonFlag		= false;
static uint8_t 			g_ibiAddress;

i3c_master_handle_t		g_i3c_m_handle;
volatile bool			g_masterCompletionFlag;
volatile status_t		g_completionStatus;

i3c_func_ptr			g_ibi_callback	= NULL;


static void i3c_master_ibi_callback(	I3C_Type			*base, 
										i3c_master_handle_t	*handle, 
										i3c_ibi_type_t		ibiType, 
										i3c_ibi_state_t		ibiState
									);
static void i3c_master_callback(	I3C_Type			*base, 
									i3c_master_handle_t	*handle, 
									status_t			status, 
									void				*userData
								);

const i3c_master_transfer_callback_t masterCallback = {
	.slave2Master		= NULL, 
	.ibiCallback		= i3c_master_ibi_callback, 
	.transferComplete	= i3c_master_callback
};

status_t i3c_reg_write( uint8_t targ, uint8_t reg, const uint8_t *dp, int length )
{
	uint8_t	bp[ REG_RW_BUFFER_SIZE ];
	
	bp[ 0 ]	= reg;
	memcpy( (uint8_t *)bp + 1, (uint8_t *)dp, length );

	return i3c_write( targ, bp, length + 1, true );
}

status_t i3c_reg_read( uint8_t targ, uint8_t reg, uint8_t *dp, int length )
{
	i3c_write( targ, &reg, 1, false );
	return i3c_read( targ, dp, length, true );
}

status_t i3c_write( uint8_t targ, const uint8_t *dp, int length, bool stop )
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
	return i3c_xfer( kI3C_Write, kI3C_TypeI3CSdr, targ, dp, length, stop );
#pragma GCC diagnostic pop
}

status_t i3c_read( uint8_t targ, uint8_t *dp, int length, bool stop )
{
	return i3c_xfer( kI3C_Read, kI3C_TypeI3CSdr, targ, dp, length, stop );
}

status_t i3c_xfer( i3c_direction_t dir, i3c_bus_type_t type, uint8_t targ, uint8_t *dp, int length, bool stop )
{
	i3c_master_transfer_t masterXfer = {0};
	
	masterXfer.slaveAddress = targ;
	masterXfer.data         = dp;
	masterXfer.dataSize     = length;
	masterXfer.direction    = dir;
	masterXfer.busType      = type;
	masterXfer.flags        = stop ? kI3C_TransferDefaultFlag : kI3C_TransferNoStopFlag;
	
	return I3C_MasterTransferBlocking( EXAMPLE_MASTER, &masterXfer );
}

void init_i3c( uint32_t i2c_freq, uint32_t i3c_od_freq, uint32_t i3c_pp_freq )
{
	i3c_master_config_t	masterConfig;

	I3C_MasterGetDefaultConfig( &masterConfig );

	masterConfig.baudRate_Hz.i2cBaud          = i2c_freq;
	masterConfig.baudRate_Hz.i3cOpenDrainBaud = i3c_od_freq;
	masterConfig.baudRate_Hz.i3cPushPullBaud  = i3c_pp_freq;
	masterConfig.enableOpenDrainStop          = false;
	masterConfig.disableTimeout               = true;
	
	I3C_MasterInit( EXAMPLE_MASTER, &masterConfig, I3C_MASTER_CLOCK_FREQUENCY );

	/* Create I3C handle. */
	I3C_MasterTransferCreateHandle( EXAMPLE_MASTER, &g_i3c_m_handle, &masterCallback, NULL );
}

void set_IBI_callback( i3c_func_ptr fp )
{
	g_ibi_callback	= fp;
}


status_t ccc_broadcast( uint8_t ccc, const uint8_t *dp, uint8_t length )
{
	uint8_t	bp[ REG_RW_BUFFER_SIZE ];

	bp[ 0 ]	= ccc;
	memcpy( (uint8_t *)bp + 1, (uint8_t *)dp, length );
	
	return i3c_write( I3C_BROADCAST_ADDR, bp, length + 1, true );
}

status_t ccc_set( uint8_t ccc, uint8_t addr, uint8_t data )
{
	i3c_write( I3C_BROADCAST_ADDR, &ccc, 1, false );
	i3c_write( addr, &data, 1, true  );
}

status_t ccc_get( uint8_t ccc, uint8_t addr, uint8_t *dp, uint8_t length )
{
	i3c_write( I3C_BROADCAST_ADDR, &ccc, 1, false );
	i3c_read( addr, dp, length, true );
}

uint8_t	i3c_check_IBI( void )
{
	if ( !g_ibiWonFlag )
		return 0;

	g_ibiWonFlag	= false;
	
	return g_ibiAddress;
}

static void i3c_master_ibi_callback( I3C_Type *base, i3c_master_handle_t *handle, i3c_ibi_type_t ibiType, i3c_ibi_state_t ibiState )
{
	g_ibiWonFlag	= true;
	g_ibiAddress	= handle->ibiAddress;
	
	switch ( ibiType )
	{
		case kI3C_IbiNormal:
			if ( ibiState == kI3C_IbiDataBuffNeed )
			{
				handle->ibiBuff = g_ibiBuff;
			}
			else
			{
				memcpy( g_ibiUserBuff, (void *)handle->ibiBuff, handle->ibiPayloadSize );
				g_ibiUserBuffUsed = handle->ibiPayloadSize;
			}
			break;

		default:
			assert(false);
			break;
	}
	
	if ( g_ibi_callback )
		g_ibi_callback();
}

static void i3c_master_callback( I3C_Type *base, i3c_master_handle_t *handle, status_t status, void *userData )
{
	if (status == kStatus_Success)
		g_masterCompletionFlag = true;

	g_completionStatus = status;
}
