/*
 * kalman_filter.c
 *
 *  Created on: 12/1/17
 *      Author: Gur Chemel
 */

//#include "includes.h"
#include "kalman_filter.h"
#include "matrix_manipulation.h"

#include "../includes/std_inc.h"
#include "../main.h"
#include "../includes/infrastructure.h"
//#include "uart_if.c"

// Filtering the error between the INS and GPS for steady error correction.
void kalman_filter(double err_new[ERR_VEC_LENGTH], double err_old[ERR_VEC_LENGTH], double cov_mat[ERR_VEC_LENGTH][ERR_VEC_LENGTH], double noise_mat[ERR_VEC_LENGTH][ERR_VEC_LENGTH])
{
	int col,row;
	// Set err_new prediction:
	double err_predict[ERR_VEC_LENGTH];
	for (row=0;row<ERR_VEC_LENGTH;row++)
	{
		err_predict[row]=err_old[row];
	}

	// Set cov_mat prediction
	double cov_predict[ERR_VEC_LENGTH][ERR_VEC_LENGTH];
	for (row=0;row<ERR_VEC_LENGTH;row++)
	{
		for (col=0;col<ERR_VEC_LENGTH;col++)
		{
			cov_predict[row][col]=cov_mat[row][col];
		}
	}

	// Calculate Kalman-gain matrix.
	double temp_mat[3][3];
	double kalman_gain[3][3];
	matrix_add_3x3(cov_predict,noise_mat,temp_mat);
	//MAT_DEBUG_PRINT("noise_mat",noise_mat);
	//MAT_DEBUG_PRINT("cov_predict",cov_predict);
	//MAT_DEBUG_PRINT("temp_mat",temp_mat);
	matrix_inverse_3x3(temp_mat);
	matrix_product_3x3(cov_predict,temp_mat,kalman_gain);
	//MAT_DEBUG_PRINT("cov_predict",cov_predict);
	//MAT_DEBUG_PRINT("temp_mat",temp_mat);

	// Calculate err output.
	double temp_vec[ERR_VEC_LENGTH];
	for (row=0;row<ERR_VEC_LENGTH;row++)
	{
		temp_vec[row]=err_new[row]-err_predict[row];
	}
	//DEBUG_PRINT("kalman Gain first row: (%f,%f,%f)\n\r",kalman_gain[0][0],kalman_gain[0][1],kalman_gain[0][2]);
	//MAT_DEBUG_PRINT("kalman_gain",kalman_gain);
	//DEBUG_PRINT("Err Predict: (%f,%f,%f)\n\r",err_predict[0],err_predict[1],err_predict[2]);
	for (row=0;row<ERR_VEC_LENGTH;row++)
	{
		err_old[row]=err_predict[row]+kalman_gain[row][0]*temp_vec[0]+kalman_gain[row][1]*temp_vec[1]+kalman_gain[row][2]*temp_vec[2];
	}

	// Calculate new cov_mat.
	double eye[3][3]={ {1,0,0}, {0,1,0}, {0,0,1} };
	matrix_sub_3x3(eye,kalman_gain,temp_mat);
	matrix_product_3x3(temp_mat,cov_predict,cov_mat);

}
