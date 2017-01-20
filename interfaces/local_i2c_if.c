/*
 * local_i2c_if.c
 *
 *  Created on: 20 Jan 2017
 *      Author: Samsung
 */

#include "../includes/std_inc.h"
#include "local_i2c_if.h"
#include "hw_types.h"
#include "hw_memmap.h"
#include "prcm.h"
#include "i2c.h"
#include "../common/i2c_if.h"



void init_i2c (){
	PRCMPeripheralReset(PRCM_I2CA0);
	I2C_IF_Open(I2C_MASTER_MODE_STD);
	I2CMasterIntClearEx(I2CA0_BASE, 0xFFF);
	I2CMasterEnable(I2CA0_BASE);
}

