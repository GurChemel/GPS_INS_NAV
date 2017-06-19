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
#define MAT_DEBUG_PRINT(string,mat) DEBUG_PRINT("Matrix %s:\n\r\t(%lf,%lf,%lf)\n\r\t(%lf,%lf,%lf)\n\r\t(%lf,%lf,%lf)\n\r",string,mat[0][0],mat[0][1],mat[0][2],mat[1][0],mat[1][1],mat[1][2],mat[2][0],mat[2][1],mat[2][2])
#endif

typedef struct {
	double X;
	double Y;
	double Z;
	double Acc;
} gps_input_data_str;

typedef struct {
	double lat;
	double lon;
	double alt; // mask bit0 s, bit1 n. bit2: e, bit 3w.
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
#define INF_PI 3.141592653589793
#define WGS84_A 6378137
#define WGS84_E 0.0818191908426
#define DEGREES_TO_RADIANS INF_PI/180

void get_mag_data(mag_input_data_str* mag_input);
void get_gyr_data(gyr_input_data_str* gyr_input);
void get_acc_data(acc_input_data_str* acc_input);
int get_gps_data(gps_input_data_str* gps_input);
void light_all_init_led(int);
#ifndef MAIN_H_
void copy_and_convert_mag_data_2_algorithm(mag_input_data_str* mag_query, Mag_local_data_str mag_data);
void copy_and_convert_gyr_data_2_algorithm(gyr_input_data_str* gyr_query, Gyr_local_data_str gyr_data);
void copy_and_convert_acc_data_2_algorithm(acc_input_data_str* acc_query, Acc_local_data_str acc_data);
void copy_and_convert_gps_data_2_algorithm(gps_input_data_str* sw_data, gps_local_data_str hw_data);
void copy_and_convert_gps_data_2_algorithm_NMEA(gps_input_data_str* sw_data, gps_local_data_NMEA_str hw_data);
#endif

void cycles_timer(double*);
void update_acc_timer(acc_input_data_str* acc_query);
void update_gyr_timer(gyr_input_data_str* gyr_query);
void init_board_and_sensors();

#endif /* INCLUDES_INFRASTRUCTURE_H_ */
