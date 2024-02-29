#include <string.h>
#include "fsl_debug_console.h"
#include "fsl_i3c.h"
#include "i3c.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#define	REG_RW_BUFFER_SIZE			10

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

status_t change_target_address( uint8_t old_addr, uint8_t new_addr )
{
	uint8_t	data	= CCC_RSTDAA;
	i3c_write( I3C_BROADCAST_ADDR, &data, 1, true );

	data	= CCC_SETDASA;
	i3c_write( I3C_BROADCAST_ADDR, &data, 1, false );

	data	= new_addr;
	i3c_write( old_addr, &data, 1, true );
}

