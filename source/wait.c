/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "fsl_common.h"

void wait( float delayTime_sec )
{
	SDK_DelayAtLeastUs( (uint32_t)(delayTime_sec * 1000000.0), CLOCK_GetCoreSysClkFreq() );
}
