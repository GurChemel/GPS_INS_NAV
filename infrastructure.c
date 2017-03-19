/*
 * infrastructure.c
 *
 *  Created on: 11  2017
 *      Author: sahiadl
 *
 *      this file includes the infrastructure code.
 *      thie file contains functions that return the data in a manner that can be proccessed and convert to relevant units.
 *
 *      each function bring the data from the relevant device
 *      and sends it to units converter.
 *      for example:
 *      read data from gyroscope in lsb/sec
 *     	and converts it to rad/sec
 */



#include "includes/std_inc.h"
#include "includes/inc.h"
#include "includes/ex_common.h"
#include "includes/driverlib.h"
#include "includes/parameters.h"
#include "ff.h"

#include "board/board.h"
#include "Sensors/sensors.h"
#include "interfaces/interfaces.h"
#include "includes/infrastructure.h"

#define MAX_COUNT_USEC 53687091.2

void init_board_and_sensors(){
	//board and chip
	BoardInit();
	PinMuxConfig();
	int status = 0;
	//console printing
	InitTerm();
	ClearTerm();
	DEBUG_PRINT("\n\r\t\t Welcome to the Matrix.. \n\r");
	reset_global_int();
	//interfaces
	//DEBUG_PRINT("\n\r\t\t entering uart init \n\r");
	init_uart();
	DEBUG_PRINT("\n\r\t\t done uart. entering i2c init \n\r");
	status = init_i2c();
	UART_PRINT("i2c init: %d\n\r", status);
	DEBUG_PRINT("\n\r\t\t done i2c. entering sd init \n\r");
	init_SD_card();
	DEBUG_PRINT("\n\r\t\t done sd init. entering sd write \n\r");
	SD_write_file("hello.txt", "my name is", strlen("my name is"), SD_CREATE_AND_DELETE);
	//DEBUG_PRINT("\n\r\t\t done sd writing. entering ds2401 \n\r");
	init_ds2401();
	DEBUG_PRINT("\n\r\t\t done all init \n\r");

	//sensors
	DEBUG_PRINT("\n\r\t\t entering gps init  \n\r");
	status = init_gps();
	if (status<0) {
		UART_PRINT("failed to initialize gps reason: %d\n\r", status);
		while (1){}
	}
	else DEBUG_PRINT("\n\r\t\t done init gps entering init mag \n\r");
	status=init_HMC5883(MAG_ADDR, true);
	if(status<0){UART_PRINT("!!! mag I2c Error. Status: %d\n\r",status);}
	else DEBUG_PRINT("\n\r\t\t done init mag entering init acc \n\r");
	status=init_ADXL345(ACC_ADDR);
	if(status<0){UART_PRINT("!!! acc I2c Error. Status: %d\n\r",status);}
	else {DEBUG_PRINT("\n\r\t\t done init acc entering init gyr \n\r");}
	status=init_ITG3200(GYR_ADDR);
	if(status<0){UART_PRINT("!!! gyr I2c Error. Status: %d\n\r",status);}
	else {DEBUG_PRINT("\n\r\t\t done init gyr done all sensors init \n\r");}
	//init_MPL115A2();
}

/******************************************************/
//magnetometer read data functions
/******************************************************/
void get_mag_data(mag_input_data_str* mag_query){
	Mag_local_data_str mag_data;
	HMC5883_read_magdata(MAG_ADDR, &mag_data );
	copy_and_convert_mag_data_2_algorithm(mag_query, mag_data);
}

void copy_and_convert_mag_data_2_algorithm(mag_input_data_str* mag_query, Mag_local_data_str mag_data ){
	mag_query->Hx = (double)mag_data.Hx; //TODO: implement this in a more elegant way
	mag_query->Hy = (double)mag_data.Hy;
	mag_query->Hz = (double)mag_data.Hz;
}

/******************************************************/
//magnetometer read data functions
/******************************************************/
void get_acc_data(acc_input_data_str* acc_query){
	Acc_local_data_str acc_data;
	ADXL345_read_accdata(ACC_ADDR, &acc_data);
	copy_and_convert_acc_data_2_algorithm(acc_query, acc_data);
	update_acc_timer(acc_query);
}

void copy_and_convert_acc_data_2_algorithm(acc_input_data_str* acc_query, Acc_local_data_str acc_data ){
	acc_query->Ax = acc_data.Ax*ACC_SCALE_FACTOR;
	acc_query->Ay = acc_data.Ay*ACC_SCALE_FACTOR;
	acc_query->Az = acc_data.Az*ACC_SCALE_FACTOR;
}

/******************************************************/
//gyroscope read data functions
/******************************************************/
void get_gyr_data(gyr_input_data_str* gyr_query){
	Gyr_local_data_str gyr_data;
	ITG3200_read_gyrdata(GYR_ADDR, &gyr_data);
	copy_and_convert_gyr_data_2_algorithm(gyr_query, gyr_data);
	update_gyr_timer(gyr_query);
}

void copy_and_convert_gyr_data_2_algorithm(gyr_input_data_str* gyr_query, Gyr_local_data_str gyr_data){
	gyr_query->Wr = gyr_data.Wr/GYR_SCALE_FACTOR;
	gyr_query->Wp = gyr_data.Wp/GYR_SCALE_FACTOR;
	gyr_query->Wy = gyr_data.Wy/GYR_SCALE_FACTOR;
}

/****************************************************/
//gps functions
/****************************************************/
/// this function returns SUCCESS if new data available and FAILURE if no new data available
int get_gps_data(gps_input_data_str* gps_input){
	if (new_gps_msg== OLD) return FAILED;
	else {
		gps_local_data_NMEA_str gps_data;
		int status = get_lon_lat(&gps_data);
		if (!status) UART_PRINT("gps data corrupted");
		copy_and_convert_gps_data_2_algorithm_NMEA(gps_input,gps_data);
		new_gps_msg = OLD;
	}
	return PASSED;
}



	/*if (new_gps_msg== NEW) parse_recieved_msg();
	else {
		int status;
		if (!NMEA){
			gps_local_data_str gps_data;
			if (new_nav_msg == false) return FAILED;
			status = parse_ubx_nav_msg (&gps_data, nav_posecef_msg);
			if (!status) UART_PRINT("gps data corrupted");
			copy_and_convert_gps_data_2_algorithm(gps_input,gps_data);
			new_nav_msg= OLD;
		}else{
			gps_local_data_NMEA_str gps_data;
			status = get_lon_lat(&gps_data);
			if (!status) UART_PRINT("gps data corrupted");
			copy_and_convert_gps_data_2_algorithm_NMEA(gps_input,gps_data);
			new_gps_msg = OLD;
		}
	}
	return PASSED;*/


void copy_and_convert_gps_data_2_algorithm(gps_input_data_str* sw_data, gps_local_data_str hw_data){
	sw_data->X   = (double)hw_data.X/100;
	sw_data->Y   = (double)hw_data.Y/100;
	sw_data->Z 	 = (double)hw_data.Z/100;
	sw_data->Acc = (double)hw_data.Acc/100;
}

void copy_and_convert_gps_data_2_algorithm_NMEA(gps_input_data_str* sw_data, gps_local_data_NMEA_str hw_data){
    double clat = cos(hw_data.lat * DEGREES_TO_RADIANS);
    double slat = sin(hw_data.lat * DEGREES_TO_RADIANS);
    double clon = cos(hw_data.lon * DEGREES_TO_RADIANS);
    double slon = sin(hw_data.lon * DEGREES_TO_RADIANS);
    double N = WGS84_A / sqrt(1.0 - WGS84_E * WGS84_E * slat * slat);
    sw_data->X = (N + hw_data.alt) * clat * clon;
    sw_data->Y = (N + hw_data.alt) * clat * slon;
    sw_data->Z = (N * (1.0 - WGS84_E * WGS84_E) + hw_data.alt) * slat;
}

/******************************************************/
//timer functions
/******************************************************/


void update_acc_timer (acc_input_data_str* acc_query){
	Timer_IF_Stop(TIMERA1_BASE,TIMER_A); //not sure if needed
	acc_query->time = MAX_COUNT_USEC-CLOCK_PERIOD_USEC*(Timer_IF_GetCount(TIMERA1_BASE,TIMER_A)); //in uSec
	Timer_IF_Init(PRCM_TIMERA1,TIMERA1_BASE,TIMER_CFG_ONE_SHOT_UP,TIMER_A,1);
	Timer_IF_Start(TIMERA1_BASE,TIMER_A,100);
}

void update_gyr_timer (gyr_input_data_str* gyr_query){
	Timer_IF_Stop(TIMERA2_BASE,TIMER_A); //not sure if needed
	gyr_query->time =  MAX_COUNT_USEC-CLOCK_PERIOD_USEC*(Timer_IF_GetCount(TIMERA2_BASE,TIMER_A));
	Timer_IF_Init(PRCM_TIMERA2,TIMERA2_BASE,TIMER_CFG_ONE_SHOT_UP,TIMER_A,1);
	Timer_IF_Start(TIMERA2_BASE,TIMER_A,100);
}
