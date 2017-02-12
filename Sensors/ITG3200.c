//Gyro
/*
 * ITG3200.c
 *
 *  Created on: Jun 6, 2016
 *      Author: Rafi
 */

#include "sensors.h"

int init_ITG3200(char addr)
{
	unsigned char data[2];
	unsigned char* rdata;
	int itg_ready =0;

	// sample rate divider
	data[ADDRESS] = SAMPLE_RATE_DIV_REG;
	data[DATA] = SAMPLE_RATE_DIV_VALUE;
	if(I2C_IF_Write(addr, data, 2, true)<0)	return -1;
	while(I2CMasterBusy(I2CA0_BASE)){}

	// plpf and full scale
	data[ADDRESS] = DLPF_FULL_SCALE_REG;
	data[DATA] = DLPF_FULL_SCALE_VALUE;
	if(I2C_IF_Write(addr, data, 2, true)<0)	return -1;
	while(I2CMasterBusy(I2CA0_BASE)){}

	// interrupts configuration
	data[ADDRESS] = INTERRUPTS_CFG_REG;
	data[DATA] = INTERRUPTS_CFG_VALUE;
	if(I2C_IF_Write(addr, data, 2, true)<0)	return -1;
	while(I2CMasterBusy(I2CA0_BASE)){}

	// Power Management
	data[ADDRESS] = POWER_MNG_REG ;
	data[DATA] = POWER_MNG_VALUE;
	if(I2C_IF_Write(addr, data, 2, true)<0)	return -1;
	while(I2CMasterBusy(I2CA0_BASE)){}

	//read pll rdy interrupt status to make sure the gyro is ready (50ms)
	data[ADDRESS] = INTERRUPTS_STATUS_REG;
	while (!itg_ready){
		if(I2C_IF_Write(addr, data, 1, false)<0) {
			itg_ready =0;
			continue;
		}
		while(I2CMasterBusy(I2CA0_BASE)){}
		if(I2C_IF_Read(addr, rdata, 1)<0) {
			itg_ready =0;
			continue;
		}
		while(I2CMasterBusy(I2CA0_BASE)){}
		itg_ready =1;
	}

	Timer_IF_Init(PRCM_TIMERA2,TIMERA2_BASE,TIMER_CFG_ONE_SHOT_UP,TIMER_A,0);
	Timer_IF_Start(TIMERA2_BASE,TIMER_A,0);

	return 0;
}



int ITG3200_read_gyrdata(char addr, Gyr_local_data_str* gyr_data)
{
	unsigned char data[2];
	unsigned char rdata[6];
	SHORT Xdata, Ydata, Zdata;

	data[ADDRESS] = GYRO_XOUT_HIGH_REG;
	if(I2C_IF_Write(addr, data, 1, false)<0)	return -1;
	while(I2CMasterBusy(I2CA0_BASE)){}
	if(I2C_IF_Read(addr, rdata, 6)<0)			return -2;
	while(I2CMasterBusy(I2CA0_BASE)){}

	Xdata = (int)rdata[GYRO_X_POS_H];
	Xdata <<=I2C_REG_SIZE;
	Xdata += (int)rdata[GYRO_X_POS_L];

	Ydata = (int)rdata[GYRO_Y_POS_H];
	Ydata <<=I2C_REG_SIZE;
	Ydata += (int)rdata[GYRO_Y_POS_L];

	Zdata = (int)rdata[GYRO_Z_POS_H];
	Zdata <<=I2C_REG_SIZE;
	Zdata += (int)rdata[GYRO_Z_POS_L];

	gyr_data->Wr = Xdata;
	gyr_data->Wp = Ydata;
	gyr_data->Wy = Zdata;

	return 0;
}
