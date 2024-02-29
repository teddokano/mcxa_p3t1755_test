#include "fsl_i3c.h"

#define EXAMPLE_MASTER			I3C0

#define I3C_BROADCAST_ADDR		0x07E

#define CCC_RSTDAA				0x06U
#define CCC_SETDASA				0x87U
#define CCC_ENEC				0x80U


status_t	i3c_xfer( i3c_direction_t dir, i3c_bus_type_t type, uint8_t targ, uint8_t *dp, int length, bool stop );
status_t	i3c_write( uint8_t targ, const uint8_t *dp, int length, bool stop );
status_t	i3c_read( uint8_t targ, uint8_t *dp, int length, bool stop );
status_t	i3c_reg_write( uint8_t targ, uint8_t reg, const uint8_t *dp, int length );
status_t	i3c_reg_read( uint8_t targ, uint8_t reg, uint8_t *dp, int length );
