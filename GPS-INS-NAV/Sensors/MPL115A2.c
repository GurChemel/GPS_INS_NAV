//Barometer
/*
 * MPL115A2.c
 *
 *  Created on: Aug 2, 2016
 *      Author: Rafi
 */


#include "sensors.h"

/*
int NNN = 16;
int pres_index = 0;

float pres_data[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
*/

void init_MPL115A2(void)
{
	/*
	float datanull;
	int ij;
	for(ij=0; ij<NNN; ij++)
	{
		int k = MPL115A2_get_pressure(&datanull);
	}
	 */
}

//int MPL115A2_get_pressure_single(float* pressure)
int MPL115A2_get_pressure(float* pressure)
{
	unsigned char data[2];
	unsigned char rdata[12];


	data[0] = 0x12;
	data[1] = 0x00;
	if(I2C_IF_Write(MPL115A2_ADDR, data, 2, true)<0)	return -1;
	while(I2CMasterBusy(I2CA0_BASE)){}

	UtilsDelay(80000);

	data[0] = 0x00;
	if(I2C_IF_Write(MPL115A2_ADDR, data, 1, false)<0)	return -2;
	while(I2CMasterBusy(I2CA0_BASE)){}

	if(I2C_IF_Read(MPL115A2_ADDR, rdata, 12)<0)			return -3;
	while(I2CMasterBusy(I2CA0_BASE)){}


	unsigned int Padc = ((unsigned int)rdata[0])<<2 | rdata[1]>>6;
	unsigned int Tadc = ((unsigned int)rdata[2])<<2 | rdata[3]>>6;

	unsigned int a0_raw = ((unsigned int)rdata[4])<<8 | rdata[5];
	unsigned int b1_raw = ((unsigned int)rdata[6])<<8 | rdata[7];
	unsigned int b2_raw = ((unsigned int)rdata[8])<<8 | rdata[9];
	unsigned int c12_raw = ((unsigned int)rdata[10])<<6 | rdata[11]>>2;

	double a0 = ((int16_t)a0_raw) / 8.0;
	double b1 = ((int16_t)b1_raw) / 8192.0;
	double b2 = ((int16_t)b2_raw) / 16384.0;
	double c12 = ((int16_t) (c12_raw<<2)) / 4.0 /4194304;


	double Pcomp = a0 + (b1+c12*Tadc)*Padc + b2*Tadc;

	*pressure = 50 + Pcomp*(115-50)/1023;

	if (*pressure<49 || *pressure>116) return -10;
	return 0;
}
/*
int MPL115A2_get_pressure(float* pressure)
{
	int res;
	float new_data;
	res = MPL115A2_get_pressure(&new_data);
	if(res!=0) return res;

	pres_index++;

	if(pres_index>=NNN) pres_index=0;
	pres_data[pres_index] = new_data;

 *pressure = 0;
	int ij;
	for(ij=0; ij<NNN; ij++)
	{
 *pressure = pres_data[ij] / NNN;
	}
	return 0;
}

 */
int MPL115A2_get_pressure_avg(float* pressure, int num) //num<=100
{
	int res;
	float new_data;
	int NNN = num;
	float pres_data[100];
	int ij;

	for(ij=0; ij<NNN; ij++)
	{
		res = MPL115A2_get_pressure(&new_data);
		if(res!=0) return res;
		pres_data[ij] = new_data;
	}

	*pressure = 0;

	for(ij=0; ij<NNN; ij++)
	{
		*pressure += pres_data[ij] / NNN;
	}

	return 0;
}














