/*****************************************************************************
                 INCLUDES
*****************************************************************************/

//#include "includes.h"
#include "includes/infrastructure.h"
#include "main.h"
#include "INS/INS.h"
#include "INS/kalman_filter.h"

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

	// Set INS Parameters.
	system_state_str systemState;
	double local_ref_in_ECEF[DIM_SIZE];
	double enu_to_ecef_mat[DIM_SIZE][DIM_SIZE];
	double ins_position_in_ECEF[DIM_SIZE]= {0};
	if (DEBUG_MODE){
		DEBUG_PRINT("\n\rStarting system Initialization....\n\r");
	}
	INS_init(&systemState, local_ref_in_ECEF, enu_to_ecef_mat);

	if (DEBUG_MODE){
		DEBUG_PRINT("\n\rSystem Initialized:\n\r");
		DEBUG_PRINT("\t Local Reference (x,y,z) in ECEF: (%f,%f,%f).\n\r",local_ref_in_ECEF(X_pos),local_ref_in_ECEF(Y_pos),local_ref_in_ECEF(Z_pos));
		DEBUG_PRINT("\t System State (x,y,z) in ENU: (%f,%f,%f).\n\r",systemState.Px,systemState.Py,systemState.Pz);
		DEBUG_PRINT("\t System State (Vx,Vy,Vz) in ENU: (%f,%f,%f).\n\r",systemState.Vx,systemState.Vy,systemState.Vz);
		DEBUG_PRINT("\t System State (Roll,Pitch,Yaw) from ENU: (%f,%f,%f).\n\r",systemState.Roll,systemState.Pitch,systemState.Yaw);
	}

	// Set Kalman Parameters.
	double position_diff_new[DIM_SIZE]= {0};
	double position_diff_old[DIM_SIZE]= {0};
	double covariance_matrix[DIM_SIZE][DIM_SIZE]={ {1,0,0}, {0,1,0}, {0,0,1} };		// TODO: Set real values!!
	double noise_variance_matrix[DIM_SIZE][DIM_SIZE]={ {1,0,0}, {0,1,0}, {0,0,1} };	// TODO: Maybe move to Infrastructure.

	// set GPS Parameters.
	gps_input_data_str gps_data;

	// Set general Parameters.
	double output_position_in_ECEF[DIM_SIZE];
	char position_data_format[] = "Position in ECEF (x,y,z): (%f,%f,%f)\n\r";
	char position_data_str[MAX_STRING_LENGTH];
	int row;

	while(1){
		// Check for new GPS data.
		int new_gps_flag= 0;//new_gps_point();
		if (new_gps_flag){	// Activate Kalman filter.		TODO: Write new_gps_point function.
			if (DEBUG_MODE){
				DEBUG_PRINT("\n\r\t New GPS data.\n\r");
			}
			get_gps_data(&gps_data);
			position_diff_new[X_pos]=gps_data.X-ins_position_in_ECEF[X_pos];
			position_diff_new[Y_pos]=gps_data.Y-ins_position_in_ECEF[Y_pos];
			position_diff_new[Z_pos]=gps_data.Z-ins_position_in_ECEF[Z_pos];
			kalman_filter(position_diff_new,position_diff_old,covariance_matrix,noise_variance_matrix);
		}

		// Calculate INS position.
		INS_calc(&systemState);
		for (row=0;row<DIM_SIZE;row++){
			ins_position_in_ECEF[row]=enu_to_ecef_mat[row][0]*systemState.Px+enu_to_ecef_mat[row][1]*systemState.Py+enu_to_ecef_mat[row][2]*systemState.Pz;
			output_position_in_ECEF[row]=ins_position_in_ECEF[row]+position_diff_old[row];
		}

		// Send Position to SD Card:
		sprintf(position_data_str,position_data_format,output_position_in_ECEF[X_pos],output_position_in_ECEF[Y_pos],output_position_in_ECEF[Z_pos]);
		//SD_write_file("position_data.txt",position_data_str, strlen(position_data_str), SD_CREATE_AND_DELETE);

		// Debug Printing to terminal.
		if (DEBUG_MODE){
			DEBUG_PRINT("\n\rEnd of loop data:\n\r");
			DEBUG_PRINT(position_data_str);
			DEBUG_PRINT("\t INS State (x,y,z) in ENU: (%f,%f,%f).\n\r",systemState.Px,systemState.Py,systemState.Pz);
			DEBUG_PRINT("\t INS State (Vx,Vy,Vz) in ENU: (%f,%f,%f).\n\n\r",systemState.Vx,systemState.Vy,systemState.Vz);
			DEBUG_PRINT("\t INS State (x,y,z) in ECEF: (%f,%f,%f).\n\r",systemState.Px,systemState.Py,systemState.Pz);
			DEBUG_PRINT("\t LAST GPS (x,y,z) in ECEF: (%f,%f,%f).\n\r",systemState.Roll,systemState.Pitch,systemState.Yaw);
			DEBUG_PRINT("\t Kalman Error (x,y,z) in ECEF: (%f,%f,%f).\n\r",systemState.Px,systemState.Py,systemState.Pz);
		}
	}

}







/*
// Initiating and Clearing the Terminal.
InitTerm();
ClearTerm();

// Displaying Application name and Compilation data.
DisplayBanner(APP_NAME);

static void
DisplayBanner(char * AppName)
{
	UART_PRINT("\n\n\n\r");
	UART_PRINT("\t\t *************************************************\n\r");
	UART_PRINT("\t\t      CC3200 %s Application       \n\r", AppName);
	UART_PRINT("\t\t *************************************************\n\r");
	UART_PRINT("\n\n\n\r");
	// Print Debugging information.
	UART_PRINT("\33[H\33[2J");
	UART_PRINT("Software compiled: ");
	UART_PRINT(__TIME__);
	UART_PRINT(" ");
	UART_PRINT(__DATE__);
	UART_PRINT("\n\r");
	UART_PRINT("\n\rREADY...\n\r");
}
*/