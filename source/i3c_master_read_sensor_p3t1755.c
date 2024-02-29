/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  Standard C Included Files */
#include <string.h>
/*  SDK Included Files */
#include "fsl_debug_console.h"
#include "fsl_p3t1755.h"
#include "fsl_i3c.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

//#define	HIGHER_SCL_FREEQ
//#define	DEFAULT_COMM
#define	TRY_IBI
#define	REG_RW_BUFFER_SIZE			10
//#define	BLOCKING_TRANSFER	//	Not supported in this version


#ifdef	HIGHER_SCL_FREEQ
#define EXAMPLE_I3C_OD_BAUDRATE		4000000
#define EXAMPLE_I3C_PP_BAUDRATE		12500000
#endif	//HIGHER_SCL_FREEQ

#define EXAMPLE_MASTER				I3C0
#define I3C_MASTER_CLOCK_FREQUENCY	CLOCK_GetI3CFClkFreq()
#define SENSOR_SLAVE_ADDR			0x48U
#define I3C_TIME_OUT_INDEX			100000000U

#define SENSOR_ADDR					0x08U
#define CCC_RSTDAA					0x06U
#define CCC_SETDASA					0x87
#define CCC_ENEC					0x80U

#define P3T1755_CONFIG_VALUE		0x02

#ifndef EXAMPLE_I2C_BAUDRATE
#define EXAMPLE_I2C_BAUDRATE		400000
#endif
#ifndef EXAMPLE_I3C_OD_BAUDRATE
#define EXAMPLE_I3C_OD_BAUDRATE		1500000
#endif
#ifndef EXAMPLE_I3C_PP_BAUDRATE
#define EXAMPLE_I3C_PP_BAUDRATE		4000000
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#ifdef TRY_IBI
static void i3c_master_ibi_callback(I3C_Type *base,
									i3c_master_handle_t *handle,
									i3c_ibi_type_t ibiType,
									i3c_ibi_state_t ibiState);
#endif // TRY_IBI

static void i3c_master_callback(I3C_Type *base, i3c_master_handle_t *handle, status_t status, void *userData);
/*******************************************************************************
 * Variables
 ******************************************************************************/
#ifdef TRY_IBI
uint8_t g_ibiBuff[10U];
static uint8_t g_ibiUserBuff[10U];
static uint8_t g_ibiUserBuffUsed	= 0;
static volatile bool g_ibiWonFlag	= false;
static uint8_t 	g_ibiAddress;
#endif // TRY_IBI

volatile status_t g_completionStatus;
volatile bool g_masterCompletionFlag;
i3c_master_handle_t g_i3c_m_handle;
p3t1755_handle_t p3t1755Handle;

#ifdef TRY_IBI
const i3c_master_transfer_callback_t masterCallback = {
	.slave2Master = NULL, .ibiCallback = i3c_master_ibi_callback, .transferComplete = i3c_master_callback};
#else
const i3c_master_transfer_callback_t masterCallback = {
	.slave2Master = NULL, .ibiCallback = NULL, .transferComplete = i3c_master_callback};
#endif // TRY_IBI

/*******************************************************************************
 * Code
 ******************************************************************************/
static void i3c_master_callback(I3C_Type *base, i3c_master_handle_t *handle, status_t status, void *userData)
{
	if (status == kStatus_Success)
		g_masterCompletionFlag = true;

	g_completionStatus = status;
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

status_t i3c_write( uint8_t targ, const uint8_t *dp, int length, bool stop )
{
	return i3c_xfer( kI3C_Write, kI3C_TypeI3CSdr, targ, dp, length, stop );
}

status_t i3c_read( uint8_t targ, uint8_t *dp, int length, bool stop )
{
	return i3c_xfer( kI3C_Read, kI3C_TypeI3CSdr, targ, dp, length, stop );
}

status_t i3c_reg_write( uint8_t targ, uint8_t reg, const uint8_t *dp, int length, bool stop )
{
	uint8_t	bp[ REG_RW_BUFFER_SIZE ];
	
	bp[ 0 ]	= reg;
	memcpy( (uint8_t *)bp + 1, (uint8_t *)dp, length );

	return i3c_write( targ, bp, length + 1, stop );
}

status_t i3c_reg_read( uint8_t targ, uint8_t reg, uint8_t *dp, int length, bool stop )
{
	i3c_write( targ, &reg, 1, false );
	return i3c_read( targ, dp, length, stop );
}

status_t I3C_WriteSensor(uint8_t deviceAddress, uint32_t regAddress, uint8_t *regData, size_t dataSize)
{
	status_t result                  = kStatus_Success;
	i3c_master_transfer_t masterXfer = {0};
	uint32_t timeout                 = 0U;

	masterXfer.slaveAddress   = deviceAddress;
	masterXfer.direction      = kI3C_Write;
	masterXfer.busType        = kI3C_TypeI3CSdr;
	masterXfer.subaddress     = regAddress;
	masterXfer.subaddressSize = 1;
	masterXfer.data           = regData;
	masterXfer.dataSize       = dataSize;
	masterXfer.flags          = kI3C_TransferDefaultFlag;

	g_masterCompletionFlag = false;
	g_completionStatus     = kStatus_Success;
	
#ifdef	BLOCKING_TRANSFER
	result	= I3C_MasterTransferBlocking(EXAMPLE_MASTER, &masterXfer);
#else
	result	= I3C_MasterTransferNonBlocking(EXAMPLE_MASTER, &g_i3c_m_handle, &masterXfer);
#endif	// BLOCKING_TRANSFER
	
	if (kStatus_Success != result)
	{
		PRINTF("\r\nERROR @I3C_WriteSensor\r\n");
		return result;
	}

	while (!g_masterCompletionFlag)
	{
		timeout++;
		if ((g_completionStatus != kStatus_Success) || (timeout > I3C_TIME_OUT_INDEX))
		{
			break;
		}
	}

	if (timeout == I3C_TIME_OUT_INDEX)
	{
		result = kStatus_Timeout;
	}
	result = g_completionStatus;

	return result;
}

status_t I3C_ReadSensor(uint8_t deviceAddress, uint32_t regAddress, uint8_t *regData, size_t dataSize)
{
	status_t result                  = kStatus_Success;
	i3c_master_transfer_t masterXfer = {0};
	uint32_t timeout                 = 0U;

	masterXfer.slaveAddress   = deviceAddress;
	masterXfer.direction      = kI3C_Read;
	masterXfer.busType        = kI3C_TypeI3CSdr;
	masterXfer.subaddress     = regAddress;
	masterXfer.subaddressSize = 1;
	masterXfer.data           = regData;
	masterXfer.dataSize       = dataSize;
	masterXfer.flags          = kI3C_TransferDefaultFlag;

	g_masterCompletionFlag = false;
	g_completionStatus     = kStatus_Success;

#ifdef	BLOCKING_TRANSFER
	result	= I3C_MasterTransferBlocking(EXAMPLE_MASTER, &masterXfer);
#else
	result	= I3C_MasterTransferNonBlocking(EXAMPLE_MASTER, &g_i3c_m_handle, &masterXfer);
#endif	// BLOCKING_TRANSFER
	
	if (kStatus_Success != result)
	{
		PRINTF("\r\nERROR @I3C_ReadSensor\r\n");
		return result;
	}

	while (!g_masterCompletionFlag)
	{
		timeout++;
		if ((g_completionStatus != kStatus_Success) || (timeout > I3C_TIME_OUT_INDEX))
		{
			break;
		}
	}

	if (timeout == I3C_TIME_OUT_INDEX)
	{
		result = kStatus_Timeout;
	}
	result = g_completionStatus;

	return result;
}


//status_t p3t1755_set_dynamic_address( uint8_t old_addr, uint8_t new_addr )
status_t p3t1755_set_dynamic_address( void )
{
	uint8_t	data	= CCC_RSTDAA;
	i3c_write( 0x7E, &data, 1, true );

	data	= CCC_SETDASA;
	i3c_write( 0x7E, &data, 1, false );

	data	= SENSOR_ADDR << 1;
	i3c_write( SENSOR_SLAVE_ADDR, &data, 1, true );
}

#ifdef TRY_IBI
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
}

status_t p3t1755_enable_IBI(void)
{
	static const uint8_t	ccc		= CCC_ENEC;
	static const uint8_t	set_int	= 0x01;

	i3c_write( 0x7E, &ccc, 1, false );
	i3c_write( SENSOR_ADDR, &set_int, 1, true  );
}
#endif // TRY_IBI

void init_MCU( void )
{
	/* Attach clock to I3C 24MHZ */
	CLOCK_SetClockDiv(kCLOCK_DivI3C0_FCLK, 2U);
	CLOCK_AttachClk(kFRO_HF_DIV_to_I3C0FCLK);

	BOARD_InitPins();
	BOARD_BootClockFRO48M();
	BOARD_InitDebugConsole();
}

void init_I3C( void )
{
	i3c_master_config_t masterConfig;

	I3C_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Hz.i2cBaud          = EXAMPLE_I2C_BAUDRATE;
	masterConfig.baudRate_Hz.i3cPushPullBaud  = EXAMPLE_I3C_PP_BAUDRATE;
	masterConfig.baudRate_Hz.i3cOpenDrainBaud = EXAMPLE_I3C_OD_BAUDRATE;
	masterConfig.enableOpenDrainStop          = false;
	masterConfig.disableTimeout               = true;
	I3C_MasterInit(EXAMPLE_MASTER, &masterConfig, I3C_MASTER_CLOCK_FREQUENCY);

	/* Create I3C handle. */
	I3C_MasterTransferCreateHandle(EXAMPLE_MASTER, &g_i3c_m_handle, &masterCallback, NULL);
}

/*!
 * @brief Main function
 */
int main(void)
{
	status_t result = kStatus_Success;
	p3t1755_config_t p3t1755Config;
	double temperature;

	init_MCU();
	init_I3C();
	
	PRINTF("\r\nI3C master read sensor data example.\r\n");

	p3t1755_set_dynamic_address();

	p3t1755Config.writeTransfer = I3C_WriteSensor;
	p3t1755Config.readTransfer  = I3C_ReadSensor;
	p3t1755Config.sensorAddress = SENSOR_ADDR;
	P3T1755_Init(&p3t1755Handle, &p3t1755Config);

#ifdef TRY_IBI
	uint16_t	tmp;
	uint8_t	config	= P3T1755_CONFIG_VALUE;
	
	uint8_t	b[]	= { 0x01, 0x02 };
	i3c_reg_write( SENSOR_ADDR, P3T1755_CONFIG_REG, &config, sizeof( config ), true );
	i3c_reg_read(  SENSOR_ADDR, P3T1755_CONFIG_REG, &config, sizeof( config ), true );		
	PRINTF( "config:0x%02X\r\n", config );
	
	p3t1755_enable_IBI();

	i3c_reg_read( SENSOR_ADDR, 0x00, (uint8_t *)&tmp, sizeof( tmp ), true );
	PRINTF( " Temp reg read value: 0x%04x\r\n", tmp );
	
	tmp	= (tmp & 0x00FF) + 1;	//	valid in little-endian system only
	i3c_reg_write( SENSOR_ADDR, 0x02, (uint8_t *)&tmp, sizeof( tmp ), true );
	
	tmp	+= 1;					//	valid in little-endian system only
	i3c_reg_write( SENSOR_ADDR, 0x03, (uint8_t *)&tmp, sizeof( tmp ), true );

	i3c_reg_read( SENSOR_ADDR, 0x02, (uint8_t *)&tmp, sizeof( tmp ), true );
	PRINTF( " LOW  0x%04x\r\n", tmp );	

	i3c_reg_read( SENSOR_ADDR, 0x03, (uint8_t *)&tmp, sizeof( tmp ), true );
	PRINTF( " HIGH 0x%04x\r\n", tmp );

#endif // TRY_IBI

	while (1)
	{
#ifdef TRY_IBI
		if ( g_ibiWonFlag )
		{
			g_ibiWonFlag = false;
			PRINTF("*** IBI : Got IBI from target_address: 7’h%02X (0x%02X)\n", g_ibiAddress, g_ibiAddress << 1 );
		}
#endif // TRY_IBI

#ifndef	DEFAULT_COMM
		uint8_t	config;
		i3c_reg_read(  SENSOR_ADDR, P3T1755_CONFIG_REG, &config, sizeof( config ), true );		
		i3c_reg_write( SENSOR_ADDR, P3T1755_CONFIG_REG, &config, sizeof( config ), true );
		
		PRINTF( "config:0x%02X\r\n", config );
#endif // DEFAULT_COMM

		i3c_reg_read(  SENSOR_ADDR, 0x00, &tmp, sizeof( tmp ), true );		

		PRINTF( "Temperature:%f \r\n", (float)(((tmp & 0x00FF) << 4) | ((tmp & 0xFF00) >> 12)) * 0.0625 );
		SDK_DelayAtLeastUs(1000000, CLOCK_GetCoreSysClkFreq());
	}
}
