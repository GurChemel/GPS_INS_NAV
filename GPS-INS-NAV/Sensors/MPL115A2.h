/*
 * MPL115A2.h
 *
 *  Created on: Aug 2, 2016
 *      Author: Rafi
 */

#ifndef MPL115A2_H_
#define MPL115A2_H_

#define MPL115A2_ADDR 0x60

//int MPL115A2_get_pressure_single(float* pressure);

int MPL115A2_get_pressure_avg(float* pressure, int num);  //num<=100

int MPL115A2_get_pressure(float* pressure);

void init_MPL115A2(void);

#endif /* MPL115A2_H_ */
