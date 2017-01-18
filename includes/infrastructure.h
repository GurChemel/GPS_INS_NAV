/*
 * infrastructure.h
 *
 *  Created on: 14 Jan 2017
 *      Author: Samsung
 */

#ifndef INCLUDES_INFRASTRUCTURE_H_
#define INCLUDES_INFRASTRUCTURE_H_

#ifndef DEBUG_PRINT
#define DEBUG_PRINT  Report
#endif

typedef struct {
	double X;
	double Y;
	double Z;
} gps_input_data_str;

typedef struct {
	double Hx;
	double Hy;
	double Hz;
} mag_input_data_str;

typedef struct {
	double Ax;
	double Ay;
	double Az;
	double time;
} acc_input_data_str;

typedef struct {
	double Wr;
	double Wp;
	double Wy;
	double time;
} gyr_input_data_str;

#include "../Sensors/sensors.h"

void get_mag_data(mag_input_data_str* mag_input);
void convert_mag_raw_data_2_units(Mag_inner_data_str* mag_query);
void copy_mag_data_2_algorithm(mag_input_data_str* mag_query, Mag_inner_data_str mag_data );
void get_gyr_data(gyr_input_data_str* gyr_input);
void convert_gyr_raw_data_2_units(Gyr_local_data* gyr_data);
void copy_data_2_algorithm(gyr_input_data_str* gyr_query, Gyr_local_data gyr_data);
void get_acc_data(acc_input_data_str* acc_input);
void convert_acc_raw_data_2_units(Acc_local_data* acc_data);
void copy_acc_data_2_algorithm(acc_input_data_str* acc_query, Acc_local_data acc_data );

void update_acc_timer (acc_input_data_str* acc_query);
void update_gyr_timer (gyr_input_data_str* gyr_query);
void init_board_and_sensors();

//yet to be implemented
//int new_gps_point();
void get_gps_data(gps_input_data_str* gps_input);


#endif /* INCLUDES_INFRASTRUCTURE_H_ */