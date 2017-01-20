//Accelerometr
/*
 * ADXL345.c
 *
 *  Created on: Jun 6, 2016
 *      Author: Rafi
 */

#include "sensors.h"

int init_ADXL345(char addr)
{

	unsigned char data[2];

	// BW = 1600Hz
	data[0] = 0x2C;
	data[1] = 0x0F;
	if(I2C_IF_Write(addr, data, 2, true)<0)	return -1;
	while(I2CMasterBusy(I2CA0_BASE)){}

	// Act threshold -threshold to set that indicate if the device is active or not.
	data[0] = 0x24;
	data[1] = 0x20;
	if(I2C_IF_Write(addr, data, 2, true)<0)	return -1;
	while(I2CMasterBusy(I2CA0_BASE)){}

	// Activity int control - the way we want to define activity/inactivity
	// referenced to the threshold
	data[0] = 0x27;
	data[1] = 0x70;//dc coupled act
	if(I2C_IF_Write(addr, data, 2, true)<0)	return -1;
	while(I2CMasterBusy(I2CA0_BASE)){}

	// Int map what int will show through what int pin
	data[0] = 0x2F;
	data[1] = 0x80;//0xEF; //0x8F;
	if(I2C_IF_Write(addr, data, 2, true)<0)	return -1;
	while(I2CMasterBusy(I2CA0_BASE)){}

	// Data format -
	data[0] = 0x31;
	data[1] = 0x0B;//TODO: talk with gur regarding FULL_RES
	if(I2C_IF_Write(addr, data, 2, true)<0)	return -1;
	while(I2CMasterBusy(I2CA0_BASE)){}


	// Int enable
	data[0] = 0x2E;
	data[1] = 0x91;// 0x10
	if(I2C_IF_Write(addr, data, 2, true)<0)	return -1;
	while(I2CMasterBusy(I2CA0_BASE)){}


	// Turn on measurement
	data[0] = 0x2d;
	data[1] = 0x08;
	if(I2C_IF_Write(addr, data, 2, true)<0)	return -1;
	while(I2CMasterBusy(I2CA0_BASE)){}

	Timer_IF_Init(PRCM_TIMERA1,TIMERA1_BASE,TIMER_CFG_ONE_SHOT_UP,TIMER_A,0);
	Timer_IF_Start(TIMERA1_BASE,TIMER_A,0);

	return 0;
}



int ADXL345_read_accdata(char addr, Acc_local_data_str* acc_data)
{
	unsigned char data[2];
	unsigned char rdata[10];
	SHORT Xdata, Ydata, Zdata;

	data[0] = 0x32;
	if(I2C_IF_Write(addr, data, 1, false)<0)	return -1;
	while(I2CMasterBusy(I2CA0_BASE)){}
	if(I2C_IF_Read(addr, rdata, 6)<0)			return -2;
	while(I2CMasterBusy(I2CA0_BASE)){}

	Xdata = (int)rdata[1];
	Xdata <<=8;
	Xdata += (int)rdata[0];

	Ydata = (int)rdata[3];
	Ydata <<=8;
	Ydata += (int)rdata[2];

	Zdata = (int)rdata[5];
	Zdata <<=8;
	Zdata += (int)rdata[4];

	acc_data->Ax = Xdata;
	acc_data->Ay = Ydata;
	acc_data->Az = Zdata;

	return 0;
}
