/*
 * sensors.h
 *
 *  Created on: 13 Jan 2017
 *      Author: Samsung
 */

#ifndef SENSORS_SENSORS_H_
#define SENSORS_SENSORS_H_

//hw IF and std includes
#include "../includes/std_inc.h"
#include "../includes/inc.h"
#include "../includes/ex_common.h"
#include "../includes/driverlib.h"


//Sensors includes
#include "ITG3200.h"
#include "MPL115A2.h"
#include "ADXL345.h"
#include "GPS.h"
#include "HMC5883.h"

#define ADDRESS 0x0
#define DATA 	0x1

#define X_POS_L 0x0
#define X_POS_H 0x1
#define Y_POS_L 0x2
#define Y_POS_H 0x3
#define Z_POS_L 0x4
#define Z_POS_H 0x5

#define GYRO_X_POS_H 0x0
#define GYRO_X_POS_L 0x1
#define GYRO_Y_POS_H 0x2
#define GYRO_Y_POS_L 0x3
#define GYRO_Z_POS_H 0x4
#define GYRO_Z_POS_L 0x5

#define I2C_REG_SIZE 0x8

#endif /* SENSORS_SENSORS_H_ */
