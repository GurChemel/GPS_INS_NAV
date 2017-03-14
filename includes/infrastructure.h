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
	double Acc;
} gps_input_data_str;

typedef struct {
	double lat_deg;
	double lat_min;
	double lon_deg;
	double lon_min;
	double POE; // mask bit0 s, bit1 n. bit2: e, bit 3w.
	int Acc;
} gps_input_data_NMEA_str;

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


#define FAILED 0
#define PASSED 1

void get_mag_data(mag_input_data_str* mag_input);
void get_gyr_data(gyr_input_data_str* gyr_input);
void get_acc_data(acc_input_data_str* acc_input);
int get_gps_data(gps_input_data_str* gps_input);

#ifndef MAIN_H_
void copy_and_convert_mag_data_2_algorithm(mag_input_data_str* mag_query, Mag_local_data_str mag_data);
void copy_and_convert_gyr_data_2_algorithm(gyr_input_data_str* gyr_query, Gyr_local_data_str gyr_data);
void copy_and_convert_acc_data_2_algorithm(acc_input_data_str* acc_query, Acc_local_data_str acc_data);
void copy_and_convert_gps_data_2_algorithm(gps_input_data_str* sw_data, gps_local_data_str hw_data);
void copy_and_convert_gps_data_2_algorithm_NMEA(gps_input_data_str* sw_data, gps_local_data_NMEA_str hw_data);
#endif

void update_acc_timer(acc_input_data_str* acc_query);
void update_gyr_timer(gyr_input_data_str* gyr_query);
void init_board_and_sensors();

//yet to be implemented
//int new_gps_point(); TODO: you dont need this any more, get_gps_data will return before uart read if no new data available

#endif /* INCLUDES_INFRASTRUCTURE_H_ */
