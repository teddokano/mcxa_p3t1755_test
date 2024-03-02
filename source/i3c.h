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

#include "fsl_i3c.h"

#define I3C_BROADCAST_ADDR		0x7E

#define CCC_BROADCAST_ENEC		0x00
#define CCC_BROADCAST_RSTDAA	0x06
#define CCC_BROADCAST_ENTDAA	0x07
#define CCC_DIRECT_ENEC			0x80
#define CCC_DIRECT_DICEC		0x81
#define CCC_DIRECT_SETDASA		0x87
#define CCC_DIRECT_SETNEWDA		0x88
#define CCC_DIRECT_GETPID		0x8D
#define CCC_DIRECT_GETBCR		0x8E
#define CCC_DIRECT_GETDCR		0x8F
#define CCC_DIRECT_GETSTATUS	0x90
#define CCC_DIRECT_RSTACT		0x90

#define	PID_LENGTH				6

typedef void (*i3c_func_ptr)(void); 

void		i3c_init( uint32_t i2c_freq, uint32_t i3c_od_freq, uint32_t i3c_pp_freq );
status_t	i3c_reg_write( uint8_t targ, uint8_t reg, const uint8_t *dp, int length );
status_t	i3c_reg_read( uint8_t targ, uint8_t reg, uint8_t *dp, int length );
status_t	i3c_write( uint8_t targ, const uint8_t *dp, int length, bool stop );
status_t	i3c_read( uint8_t targ, uint8_t *dp, int length, bool stop );
status_t	i3c_xfer( i3c_direction_t dir, i3c_bus_type_t type, uint8_t targ, uint8_t *dp, int length, bool stop );
uint8_t		i3c_check_IBI( void );
void		set_IBI_callback( i3c_func_ptr fp );
status_t	ccc_broadcast( uint8_t ccc, const uint8_t *dp, uint8_t length );
status_t	ccc_set( uint8_t ccc, uint8_t addr, uint8_t data );
status_t	ccc_get( uint8_t ccc, uint8_t addr, uint8_t *dp, uint8_t length );

