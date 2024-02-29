/*
 * Copyright 2024 Tedd OKANO
 */

#define P3T1755_ADDR_I2C			0x48U
#define P3T1755_ADDR_I3C			0x08U
#define P3T1755_CONFIG_VALUE		0x2A

enum	{
	P3T1755_REG_Temp,
	P3T1755_REG_Conf,
	P3T1755_REG_T_LOW,
	P3T1755_REG_T_HIGH,
};
