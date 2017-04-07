/*
 * matrix_manipulation.c
 *
 *  Created on: 12 בינו׳ 2017
 *      Author: גור
 */

#include "../includes/std_inc.h"
#include "matrix_manipulation.h"

void matrix_inverse_3x3(double matrix[3][3]){
	// computes the inverse of a matrix m
	double det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]) -
	             matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
	             matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);

	double invdet = 1 / det;

	double minv[3][3]; // inverse of matrix m
	minv[0][0] = (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]) * invdet;
	minv[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) * invdet;
	minv[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) * invdet;
	minv[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) * invdet;
	minv[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) * invdet;
	minv[1][2] = (matrix[1][0] * matrix[0][2] - matrix[0][0] * matrix[1][2]) * invdet;
	minv[2][0] = (matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1]) * invdet;
	minv[2][1] = (matrix[2][0] * matrix[0][1] - matrix[0][0] * matrix[2][1]) * invdet;
	minv[2][2] = (matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]) * invdet;
	int col,row;
	for (row=0;row<3;row++){
		for (col=0;col<3;col++){
			matrix[row][col]=minv[row][col];
		}
	}
}

void matrix_product_3x3(double matrix_a[3][3],double matrix_b[3][3],double result[3][3]){
	int col,row;
	for (row=0;row<3;row++){
		for (col=0;col<3;col++){
			result[row][col]=matrix_a[row][0]*matrix_b[0][col]+matrix_a[row][1]*matrix_b[1][col]+matrix_a[row][2]*matrix_b[2][col];
		}
	}
}

void matrix_add_3x3(double matrix_a[3][3],double matrix_b[3][3],double result[3][3]){
	int col,row;
	for (row=0;row<3;row++){
		for (col=0;col<3;col++){
			result[row][col]=matrix_a[row][col]+matrix_b[row][col];
		}
	}
}

void matrix_sub_3x3(double matrix_a[3][3],double matrix_b[3][3],double result[3][3]){
	int col,row;
	for (row=0;row<3;row++){
		for (col=0;col<3;col++){
			result[row][col]=matrix_a[row][col]-matrix_b[row][col];
		}
	}
}
