/*****************************************************************************
                 INCLUDES
*****************************************************************************/

//#include "includes.h"
#include "main.h"
#include "board/board.h"
#include "includes/infrastructure.h"
#include "INS/INS.h"
#include "Sensors/sensors.h"
#include "INS/kalman_filter.h"
#include "common/uart_if.h"
#include "includes/std_inc.h"

#define WAIT_LOOPS_UNTIL_NEW_AVERAGE 250 //250*0.4 ~ 10 sec

/*****************************************************************************
                 General Functions
*****************************************************************************/


/*****************************************************************************
                 APPLICATION MAIN
*****************************************************************************/

int main(void)
{
	// Initiating Board and Sensors.
	init_board_and_sensors();
	DEBUG_PRINT("\n\r\t\t done complete init \n\r");
	// Set INS Parameters.
	system_state_str systemState;
	double local_ref_in_ECEF[DIM_SIZE];
	double gyro_offset[DIM_SIZE]={0};
	double enu_offset[DIM_SIZE]={0};
	double enu_to_ecef_mat[DIM_SIZE][DIM_SIZE];
	double ecef_to_enu_mat[DIM_SIZE][DIM_SIZE];
	double ins_position_in_ECEF[DIM_SIZE]= {0};
	char info_string[MAX_STRING_LENGTH];
	sprintf(info_string,"%d: Starting system Initialization....\n\r",rand());
	DEBUG_PRINT(info_string);
	SD_write_file("log.txt",info_string, strlen(info_string), SD_CREATE_OR_OPEN);
	INS_init(&systemState, local_ref_in_ECEF, enu_to_ecef_mat,ecef_to_enu_mat,gyro_offset,enu_offset);
	light_all_init_led(2);
	sprintf(info_string,"Finished system Initialization.\n\r");
	SD_write_file("log.txt",info_string, strlen(info_string), SD_CREATE_OR_OPEN);
	if (1){
		DEBUG_PRINT("\n\rSystem Initialized:\n\r");
		DEBUG_PRINT("\t Local Reference (x,y,z) in ECEF: (%f, %f, %f).\n\r",(local_ref_in_ECEF[X_pos]),(local_ref_in_ECEF[Y_pos]),(local_ref_in_ECEF[Z_pos]));
		DEBUG_PRINT("\t System State (x,y,z) in ENU: (%f,%f,%f).\n\r",systemState.Px,systemState.Py,systemState.Pz);
		DEBUG_PRINT("\t System State (Vx,Vy,Vz) in ENU: (%f,%f,%f).\n\r",systemState.Vx,systemState.Vy,systemState.Vz);
		DEBUG_PRINT("\t System State (Roll,Pitch,Yaw) from ENU: (%f,%f,%f).\n\r",systemState.Roll,systemState.Pitch,systemState.Yaw);
	}

	// Set Kalman Parameters.
	double position_diff_new[DIM_SIZE]= {0};
	double position_diff_old[DIM_SIZE]= {0};
	double covariance_matrix[DIM_SIZE][DIM_SIZE]={ {0.25,0,0}, {0,0.25,0}, {0,0,0.25} };		// TODO: Set real values!!
	double noise_variance_matrix[DIM_SIZE][DIM_SIZE]={ {0.25,0,0}, {0,0.25,0}, {0,0,0.25} };	// TODO: Maybe move to Infrastructure.

	// set GPS Parameters.
	gps_input_data_str gps_data,old_gps_data;
	// Initialize old_gps:
	old_gps_data.X=local_ref_in_ECEF[X_pos];
	old_gps_data.Y=local_ref_in_ECEF[Y_pos];
	old_gps_data.Z=local_ref_in_ECEF[Z_pos];

	// Set general Parameters.
	double gps_trust_value=1; // Must be set between 0 to 1.
	int row;
	int loop_counter=1;
	double output_position_in_ECEF[DIM_SIZE];
	char position_data_format[] = "%lf %lf %lf %lf\n";	//Position in ECEF (x,y,z,time (uSec))
	char position_data_str[MAX_STRING_LENGTH];
	double dt,time;
	cycles_timer(&dt);
	time=0;

	// Gur: Added for offset testing:
	//gyr_input_data_str gyr_data_for_offset;			//	gyr_data.Wr , gyr_data.Wp , gyr_data.Wy , gyr.data.time
	//double gyro_mean[3]={0};
	//int i=0;
	sprintf(position_data_str,"GPS_X GPS_Y GPS_Z\n");
	SD_write_file("gps.txt",position_data_str, strlen(position_data_str), SD_CREATE_AND_DELETE);
	sprintf(position_data_str,"X_ECEF_POSITION Y_ECEF_POSITION Z_ECEF_POSITION TIME\n");
	SD_write_file("position.txt",position_data_str, strlen(position_data_str), SD_CREATE_AND_DELETE);
	while(1){
		// Check for new GPS data.
		if ((get_gps_data(&gps_data) == PASSED) && (loop_counter>1)){	// Activate Kalman filter.
			//position_diff_new[X_pos]=gps_data.X-ins_position_in_ECEF[X_pos];
			//position_diff_new[Y_pos]=gps_data.Y-ins_position_in_ECEF[Y_pos];
			//position_diff_new[Z_pos]=gps_data.Z-ins_position_in_ECEF[Z_pos];
			//DEBUG_PRINT("\n\r\t New GPS data.\n\n\r");
			//DEBUG_PRINT("New Diff: (%f,%f,%f)\n\r",position_diff_new[0],position_diff_new[1],position_diff_new[2]);
			//kalman_filter(position_diff_new,position_diff_old,covariance_matrix,noise_variance_matrix);
			local_ref_in_ECEF[X_pos]=gps_data.X;
			local_ref_in_ECEF[Y_pos]=gps_data.Y;
			local_ref_in_ECEF[Z_pos]=gps_data.Z;
			systemState.Vx=1*(ecef_to_enu_mat[0][0]*(gps_data.X-old_gps_data.X)+ecef_to_enu_mat[0][1]*(gps_data.Y-old_gps_data.Y)+ecef_to_enu_mat[0][2]*(gps_data.Z-old_gps_data.Z))+(1-1)*systemState.Vx;
			systemState.Vy=1*(ecef_to_enu_mat[1][0]*(gps_data.X-old_gps_data.X)+ecef_to_enu_mat[1][1]*(gps_data.Y-old_gps_data.Y)+ecef_to_enu_mat[1][2]*(gps_data.Z-old_gps_data.Z))+(1-1)*systemState.Vy;
			systemState.Vz=1*(ecef_to_enu_mat[2][0]*(gps_data.X-old_gps_data.X)+ecef_to_enu_mat[2][1]*(gps_data.Y-old_gps_data.Y)+ecef_to_enu_mat[2][2]*(gps_data.Z-old_gps_data.Z))+(1-1)*systemState.Vz;
			systemState.Px=0; //gps_trust_value*(ecef_to_enu_mat[0][0]*(gps_data.X)+ecef_to_enu_mat[0][1]*(gps_data.Y)+ecef_to_enu_mat[0][2]*(gps_data.Z))+(1-gps_trust_value)*systemState.Px;
			systemState.Py=0; //gps_trust_value*(ecef_to_enu_mat[1][0]*(gps_data.X)+ecef_to_enu_mat[1][1]*(gps_data.Y)+ecef_to_enu_mat[1][2]*(gps_data.Z))+(1-gps_trust_value)*systemState.Py;
			systemState.Pz=0; //gps_trust_value*(ecef_to_enu_mat[2][0]*(gps_data.X)+ecef_to_enu_mat[2][1]*(gps_data.Y)+ecef_to_enu_mat[2][2]*(gps_data.Z))+(1-gps_trust_value)*systemState.Pz;
			old_gps_data.X=gps_data.X;
			old_gps_data.Y=gps_data.Y;
			old_gps_data.Z=gps_data.Z;
			cycles_timer(&dt);
			time=time+(dt);
			sprintf(position_data_str,position_data_format,gps_data.X,gps_data.Y,gps_data.Z,time);
			SD_write_file("gps.txt",position_data_str, strlen(position_data_str), SD_CREATE_OR_OPEN);
		} else {
			// Calculate INS position.
			INS_calc(&systemState,gyro_offset,enu_offset);
			position_diff_new[X_pos]=old_gps_data.X-ins_position_in_ECEF[X_pos];
			position_diff_new[Y_pos]=old_gps_data.Y-ins_position_in_ECEF[Y_pos];
			position_diff_new[Z_pos]=old_gps_data.Z-ins_position_in_ECEF[Z_pos];
			kalman_filter(position_diff_new,position_diff_old,covariance_matrix,noise_variance_matrix);
		}


		// Convert ENU to ECEF:
		for (row=0;row<DIM_SIZE;row++){
			ins_position_in_ECEF[row]=local_ref_in_ECEF[row]+enu_to_ecef_mat[row][0]*systemState.Px+enu_to_ecef_mat[row][1]*systemState.Py+enu_to_ecef_mat[row][2]*systemState.Pz;
			output_position_in_ECEF[row]=ins_position_in_ECEF[row]+position_diff_old[row];
		}
		//Send Position to SD Card:
		cycles_timer(&dt);
		time=time+(dt);
		sprintf(position_data_str,position_data_format,output_position_in_ECEF[X_pos],output_position_in_ECEF[Y_pos],output_position_in_ECEF[Z_pos],time);
		SD_write_file("position.txt",position_data_str, strlen(position_data_str), SD_CREATE_OR_OPEN);

		// Debug Printing to terminal.
		//DEBUG_PRINT("Diff: (%f,%f,%f)\n\r",position_diff_old[0],position_diff_old[1],position_diff_old[2]);
		//DEBUG_PRINT(position_data_format,output_position_in_ECEF[X_pos]-gps_data.X,output_position_in_ECEF[Y_pos]-gps_data.Y,output_position_in_ECEF[Z_pos]-gps_data.Z);
		//DEBUG_PRINT("\n\rEnd of loop data:\n\r");
		DEBUG_PRINT(position_data_str);
		//DEBUG_PRINT("\t INS State (x,y,z) in ENU: (%f,%f,%f).\n\r",systemState.Px,systemState.Py,systemState.Pz);
		//DEBUG_PRINT("INS State (Vx,Vy,Vz) in ENU: (%f,%f,%f).\n\r",systemState.Vx,systemState.Vy,systemState.Vz);
		//DEBUG_PRINT("INS State (x,y,z) in ECEF: (%f,%f,%f).\n\r",systemState.Px,systemState.Py,systemState.Pz);
		//DEBUG_PRINT("%f,%f,%f,",systemState.Vx,systemState.Vy,systemState.Vz);
		//DEBUG_PRINT("%f,%f,%f\n\r",systemState.Px,systemState.Py,systemState.Pz);
		//DEBUG_PRINT("\t LAST GPS (x,y,z) in ECEF: (%f,%f,%f).\n\r",systemState.Roll,systemState.Pitch,systemState.Yaw);
		//DEBUG_PRINT("\t Kalman Error (x,y,z) in ECEF: (%f,%f,%f).\n\r",systemState.Px,systemState.Py,systemState.Pz);

		loop_counter++;

		/*if (loop_counter < WAIT_LOOPS_UNTIL_NEW_AVERAGE) {
			loop_counter++;
		}
		else{
			gyro_mean[X_pos]=0;
			gyro_mean[Y_pos]=0;
			gyro_mean[Z_pos]=0;
			// Get gyro offset mean:
			for (i=0;i<100;i++){
				get_gyr_data(&gyr_data_for_offset);
				gyro_mean[X_pos]=gyro_mean[X_pos]+gyr_data_for_offset.Wr;
				gyro_mean[Y_pos]=gyro_mean[Y_pos]+gyr_data_for_offset.Wp;
				gyro_mean[Z_pos]=gyro_mean[Z_pos]+gyr_data_for_offset.Wy;
				MAP_UtilsDelay(1000000/5);	// Wait for ~0.0125 sec.
			}
			gyro_offset[X_pos]=gyro_mean[X_pos]/100;
			gyro_offset[Y_pos]=gyro_mean[Y_pos]/100;
			gyro_offset[Z_pos]=gyro_mean[Z_pos]/100;
			loop_counter=0;
			//DEBUG_PRINT("%f,%f,%f\n\r",gyro_offset[X_pos]-gyro_offset[X_pos],gyro_offset[Y_pos]-gyro_offset[Y_pos],gyro_offset[Z_pos]-gyro_offset[Z_pos]);
		}*/
	}

}

