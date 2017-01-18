/*
 * ADXL345.h
 *
 *  Created on: Jun 6, 2016
 *      Author: Rafi
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#define ACC_SCALE_FACTOR 0.0039

typedef struct {
	double Ax;
	double Ay;
	double Az;
}Acc_local_data;

int init_ADXL345(char addr);
int ADXL345_read_accdata(char addr,  Acc_local_data* acc_data);


#endif /* ADXL345_H_ */
