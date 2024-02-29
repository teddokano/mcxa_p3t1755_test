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

#define I3C_BROADCAST_ADDR		0x07E

#define CCC_RSTDAA				0x06U
#define CCC_SETDASA				0x87U
#define CCC_ENEC				0x80U

void		i3c_init( uint32_t i2c_freq, uint32_t i3c_od_freq, uint32_t i3c_pp_freq );
status_t	i3c_reg_write( uint8_t targ, uint8_t reg, const uint8_t *dp, int length );
status_t	i3c_reg_read( uint8_t targ, uint8_t reg, uint8_t *dp, int length );
status_t	i3c_write( uint8_t targ, const uint8_t *dp, int length, bool stop );
status_t	i3c_read( uint8_t targ, uint8_t *dp, int length, bool stop );
status_t	i3c_xfer( i3c_direction_t dir, i3c_bus_type_t type, uint8_t targ, uint8_t *dp, int length, bool stop );
status_t	i3c_change_target_address( uint8_t old_addr, uint8_t new_addr );
status_t	i3c_enable_IBI( uint8_t addr );
uint8_t		i3c_check_IBI( void );
