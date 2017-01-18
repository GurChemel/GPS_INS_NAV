/*
 * matrix_manipulation.c
 *
 *  Created on: 12 ����� 2017
 *      Author: ���
 */

/*For calculating Determinant of the Matrix */

#include "../includes/std_inc.h"
#include "matrix_manipulation.h"

float determinant(double a[3][3], int k){
	double s=1,det=0,b[3][3];
	int i,j,m,n,c;

	det=0;
	for (c=0;c<k;c++){
		m=0;
		n=0;
		for (i=0;i<k;i++){
			for (j=0;j<k;j++){
				b[i][j]=0;
				if (i != 0 && j != c){
					b[m][n]=a[i][j];
					if (n<(k-2)) n++;
					else{
					 n=0;
					 m++;
					}
				}
			}
		}
		det=det + s * (a[0][c] * determinant(b,k-1));
		s=-1 * s;
	}
    return (det);
}

void matrix_inverse_3x3(double matrix[3][3]){
	double f=3;
	double b[3][3],fac[3][3];
	int p,q,m,n,i,j;
	for (q=0;q<f;q++) {
		for (p=0;p<f;p++) {
			m=0;
			n=0;
			for (i=0;i<f;i++) {
				for (j=0;j<f;j++) {
					if (i != q && j != p){
						b[m][n]=matrix[i][j];
						if (n<(f-2)) n++;
						else{
							n=0;
							m++;
						}
					}
				}
			}
			fac[q][p]=pow(-1,q + p) * determinant(b,f-1);
		}
	}
	double d=determinant(matrix,3);
	for (i=0;i<3;i++) {
		for (j=0;j<3;j++) {
			matrix[i][j]=fac[j][i]/ d;
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