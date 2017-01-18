/*
 * main.h
 *
 *  Created on: Aug 4, 2016
 *      Author: Rafi
 */

#ifndef MAIN_H_
#define MAIN_H_

enum {
	X_pos = 0,
	Y_pos = 1,
	Z_pos = 2
};

#define MAX_STRING_LENGTH 1000
#define DIM_SIZE 3

typedef struct {
	double Px;
	double Py;
	double Pz;
	double Vx;
	double Vy;
	double Vz;
	double Roll;
	double Pitch;
	double Yaw;
} system_state_str;


#endif /* MAIN_H_ */
