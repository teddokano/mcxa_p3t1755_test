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
#define	BLOCKING_TRANSFER
#define	DEFAULT_COMM
#define	TRY_IBI


#ifdef	HIGHER_SCL_FREEQ
#define EXAMPLE_I3C_OD_BAUDRATE 4000000
#define EXAMPLE_I3C_PP_BAUDRATE 12500000
#endif	//HIGHER_SCL_FREEQ

#define EXAMPLE_MASTER             I3C0
#define I3C_MASTER_CLOCK_FREQUENCY CLOCK_GetI3CFClkFreq()
#define SENSOR_SLAVE_ADDR          0x48U
#define I3C_TIME_OUT_INDEX 100000000U

#define SENSOR_ADDR 0x08U
#define CCC_RSTDAA  0x06U
#define CCC_SETDASA 0x87

#ifndef EXAMPLE_I2C_BAUDRATE
#define EXAMPLE_I2C_BAUDRATE 400000
#endif
#ifndef EXAMPLE_I3C_OD_BAUDRATE
#define EXAMPLE_I3C_OD_BAUDRATE 1500000
#endif
#ifndef EXAMPLE_I3C_PP_BAUDRATE
#define EXAMPLE_I3C_PP_BAUDRATE 4000000
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
static uint8_t g_ibiUserBuffUsed            = 0;
static volatile bool g_ibiWonFlag           = false;
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
	{
		g_masterCompletionFlag = true;
	}

	g_completionStatus = status;
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
	result                 = I3C_MasterTransferBlocking(EXAMPLE_MASTER, &masterXfer);
#else
	result                 = I3C_MasterTransferNonBlocking(EXAMPLE_MASTER, &g_i3c_m_handle, &masterXfer);
#endif	// BLOCKING_TRANSFER
	if (kStatus_Success != result)
	{
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
	result                 = I3C_MasterTransferBlocking(EXAMPLE_MASTER, &masterXfer);
#else
	result                 = I3C_MasterTransferNonBlocking(EXAMPLE_MASTER, &g_i3c_m_handle, &masterXfer);
#endif	// BLOCKING_TRANSFER
	
	if (kStatus_Success != result)
	{
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

status_t p3t1755_set_dynamic_address(void)
{
	status_t result                  = kStatus_Success;
	i3c_master_transfer_t masterXfer = {0};
	uint8_t g_master_txBuff[1];

	/* Reset dynamic address. */
	g_master_txBuff[0]      = CCC_RSTDAA;
	masterXfer.slaveAddress = 0x7E;
	masterXfer.data         = g_master_txBuff;
	masterXfer.dataSize     = 1;
	masterXfer.direction    = kI3C_Write;
	masterXfer.busType      = kI3C_TypeI3CSdr;
	masterXfer.flags        = kI3C_TransferDefaultFlag;
	result                  = I3C_MasterTransferBlocking(EXAMPLE_MASTER, &masterXfer);
	if (result != kStatus_Success)
	{
		return result;
	}

	/* Assign dynmic address. */
	memset(&masterXfer, 0, sizeof(masterXfer));
	g_master_txBuff[0]      = CCC_SETDASA;
	masterXfer.slaveAddress = 0x7E;
	masterXfer.data         = g_master_txBuff;
	masterXfer.dataSize     = 1;
	masterXfer.direction    = kI3C_Write;
	masterXfer.busType      = kI3C_TypeI3CSdr;
	masterXfer.flags        = kI3C_TransferNoStopFlag;
	result                  = I3C_MasterTransferBlocking(EXAMPLE_MASTER, &masterXfer);
	if (result != kStatus_Success)
	{
		return result;
	}

	memset(&masterXfer, 0, sizeof(masterXfer));
	g_master_txBuff[0]      = SENSOR_ADDR << 1;
	masterXfer.slaveAddress = SENSOR_SLAVE_ADDR;
	masterXfer.data         = g_master_txBuff;
	masterXfer.dataSize     = 1;
	masterXfer.direction    = kI3C_Write;
	masterXfer.busType      = kI3C_TypeI3CSdr;
	masterXfer.flags        = kI3C_TransferDefaultFlag;
	return I3C_MasterTransferBlocking(EXAMPLE_MASTER, &masterXfer);
}

static void i3c_master_ibi_callback(I3C_Type *base,
									i3c_master_handle_t *handle,
									i3c_ibi_type_t ibiType,
									i3c_ibi_state_t ibiState)
{
	switch (ibiType)
	{
		case kI3C_IbiNormal:
			if (ibiState == kI3C_IbiDataBuffNeed)
			{
				handle->ibiBuff = g_ibiBuff;
			}
			else
			{
				memcpy(g_ibiUserBuff, (void *)handle->ibiBuff, handle->ibiPayloadSize);
				g_ibiUserBuffUsed = handle->ibiPayloadSize;
			}
			break;

		default:
			assert(false);
			break;
	}
}
/*!
 * @brief Main function
 */
int main(void)
{
	status_t result = kStatus_Success;
	i3c_master_config_t masterConfig;
	p3t1755_config_t p3t1755Config;
	double temperature;

	/* Attach clock to I3C 24MHZ */
	CLOCK_SetClockDiv(kCLOCK_DivI3C0_FCLK, 2U);
	CLOCK_AttachClk(kFRO_HF_DIV_to_I3C0FCLK);

	BOARD_InitPins();
	BOARD_BootClockFRO48M();
	BOARD_InitDebugConsole();

	PRINTF("\r\nI3C master read sensor data example.\r\n");

	I3C_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Hz.i2cBaud          = EXAMPLE_I2C_BAUDRATE;
	masterConfig.baudRate_Hz.i3cPushPullBaud  = EXAMPLE_I3C_PP_BAUDRATE;
	masterConfig.baudRate_Hz.i3cOpenDrainBaud = EXAMPLE_I3C_OD_BAUDRATE;
	masterConfig.enableOpenDrainStop          = false;
	masterConfig.disableTimeout               = true;
	I3C_MasterInit(EXAMPLE_MASTER, &masterConfig, I3C_MASTER_CLOCK_FREQUENCY);

	/* Create I3C handle. */
	I3C_MasterTransferCreateHandle(EXAMPLE_MASTER, &g_i3c_m_handle, &masterCallback, NULL);

	result = p3t1755_set_dynamic_address();
	if (result != kStatus_Success)
	{
		PRINTF("\r\nP3T1755 set dynamic address failed.\r\n");
	}

	p3t1755Config.writeTransfer = I3C_WriteSensor;
	p3t1755Config.readTransfer  = I3C_ReadSensor;
	p3t1755Config.sensorAddress = SENSOR_ADDR;
	P3T1755_Init(&p3t1755Handle, &p3t1755Config);

#ifdef TRY_IBI
	i3c_register_ibi_addr_t	ibiRecord = { .address = { SENSOR_ADDR }, .ibiHasPayload = false };
	I3C_MasterRegisterIBI( EXAMPLE_MASTER, &ibiRecord );

//	result = I3C_WriteSensor(0x7E, 0x06, NULL, 0);


#endif // TRY_IBI

	
	while (1)
	{
#ifdef TRY_IBI
//		I3C_MasterEmitRequest(EXAMPLE_MASTER, kI3C_RequestProcessDAA);
//		result = I3C_WriteSensor(0x7E, 0x06, NULL, 0);
//		result = I3C_WriteSensor(0x7E, 0x06, NULL, 0);
		if (g_ibiWonFlag)
		{
			PRINTF("\r\nReceived slave IBI request.");
			for (uint8_t count = 0; count < g_ibiUserBuffUsed; count++)
			{
				PRINTF(" Data 0x%x.", g_ibiUserBuff[count]);
			}
			g_ibiWonFlag = false;
		}
#endif // TRY_IBI

		
#ifndef	DEFAULT_COMM
		
		
		uint8_t	config;
		result	= P3T1755_ReadReg( &p3t1755Handle, P3T1755_CONFIG_REG, &config, 1 );

		if (result != kStatus_Success)
			PRINTF("\r\nP3T1755 read temperature failed.\r\n");

		PRINTF("\r\config:0x%02X\r\n", config);
		SDK_DelayAtLeastUs(1000000, CLOCK_GetCoreSysClkFreq());
#endif // DEFAULT_COMM


		result = P3T1755_ReadTemperature(&p3t1755Handle, &temperature);

		if (result != kStatus_Success)
			PRINTF("\r\nP3T1755 read temperature failed.\r\n");

		PRINTF("\r\nTemperature:%f \r\n", temperature);
		SDK_DelayAtLeastUs(1000000, CLOCK_GetCoreSysClkFreq());
	}
}
