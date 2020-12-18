#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <math.h>
#include "FM.h"
//typedef float axis_t;

float b1[64] = {
	-0.000570976,
	-0.000222011,
	0.000248603,
	0.000792292,
	0.001296806,
	0.001576333,
	0.001410031,
	0.000630176,
	-0.000766216,
	-0.002529942,
	-0.004148569,
	-0.004945903,
	-0.004288253,
	-0.001847815,
	0.002163637,
	0.006889415,
	0.010926623,
	0.012648752,
	0.010697516,
	0.00451942,
	-0.005217876,
	-0.016486934,
	-0.026137589,
	-0.030508014,
	-0.026295276,
	-0.011478651,
	0.013952187,
	0.047684493,
	0.085312171,
	0.121097528,
	0.149111154,
	0.164486888,
	0.164486888,
	0.149111154,
	0.121097528,
	0.085312171,
	0.047684493,
	0.013952187,
	-0.011478651,
	-0.026295276,
	-0.030508014,
	-0.026137589,
	-0.016486934,
	-0.005217876,
	0.00451942,
	0.010697516,
	0.012648752,
	0.010926623,
	0.006889415,
	0.002163637,
	-0.001847815,
	-0.004288253,
	-0.004945903,
	-0.004148569,
	-0.002529942,
	-0.000766216,
	0.000630176,
	0.001410031,
	0.001576333,
	0.001296806,
	0.000792292,
	0.000248603,
	-0.000222011,
	-0.000570976,
	};

float b2[64] = {
		-0.000366538,
		-0.000134168,
		0.000150239,
		0.000508612,
		0.000949195,
		0.001453866,
		0.001969259,
		0.002404499,
		0.002637394,
		0.002529588,
		0.001949578,
		0.000800891,
		-0.000948565,
		-0.00324077,
		-0.00591034,
		-0.008679954,
		-0.011171238,
		-0.01293192,
		-0.01347777,
		-0.012345556,
		-0.009151316,
		-0.003646923,
		0.004232465,
		0.014336929,
		0.026291596,
		0.039510697,
		0.053235971,
		0.066596484,
		0.078684159,
		0.088637134,
		0.095721853,
		0.09940465,
		0.09940465,
		0.095721853,
		0.088637134,
		0.078684159,
		0.066596484,
		0.053235971,
		0.039510697,
		0.026291596,
		0.014336929,
		0.004232465,
		-0.003646923,
		-0.009151316,
		-0.012345556,
		-0.01347777,
		-0.01293192,
		-0.011171238,
		-0.008679954,
		-0.00591034,
		-0.00324077,
		-0.000948565,
		0.000800891,
		0.001949578,
		0.002529588,
		0.002637394,
		0.002404499,
		0.001969259,
		0.001453866,
		0.000949195,
		0.000508612,
		0.000150239,
		-0.000134168,
		-0.000366538,
};


float buff1[64];
float buff2[64];
float buff3[64];


void FM(axis_t* xi, axis_t* xr, axis_t*y){
	int N1 = 10;
	int SIZE1 = SIZE/N1;
	float xIII[SIZE];
	float xRRR[SIZE];
	float xid[SIZE1];
	float xrd[SIZE1];
	float disdata[SIZE1];
	float disdata1[SIZE1];
	int N2=5;
	int SIZE2 = SIZE1/N2;
	float out[SIZE2];


#pragma HLS dataflow
	axis_t xI;
	float xII[SIZE];
	axis_t xR;
	float xRR[SIZE];

	for(int i=0; i<1000; i++){
#pragma HLS unroll factor = 20
#pragma HLS pipeline II=20
		xI = *xi;
		xII[i] = xI.data;
		xR = *xr;
		xRR[i] = xR.data;
		xi++;
		xr++;
	}


	lfilterI(b1, xII, xIII, SIZE);
	lfilterR(b1, xRR, xRRR, SIZE);


	downsample(xid, xIII, N1, SIZE);
	downsample(xrd, xRRR, N1, SIZE);


	discrim(xid, xrd, disdata, SIZE1);


	lfilterD(b2, disdata, disdata1, SIZE1);


	downsample(out, disdata1, N2, SIZE1);

	axis_t temp;
	for(int i=0; i<SIZE2; i++){
#pragma HLS unroll factor = 5
#pragma HLS pipeline II=5
		temp.data = out[i];
		if(i == SIZE2-1){
			temp.last = 1;
		}
		else{
			temp.last = 0;
		}
		*y = temp;
		y++;
	}
}

void downsample(float *y, float* x, int M, int siz){

	int size = siz/M;
	for(int i=0; i<size; i++){
#pragma HLS unroll factor = 5
#pragma HLS pipeline II=5
		y[i] = x[i*M];
	}
}

void lfilterD(float* b, float* x, float *y, int siz){
#pragma HLS array_partition variable = buff3 block factor=4 dim=1
	float temp;
	for(int i=0; i<siz; i++){
#pragma HLS pipeline II=4
		for(int j=0; j<64-1; j++){
#pragma HLS unroll factor = 8
			buff3[64-1-j] = buff3[64-2-j];
		}
		buff3[0] = x[i];
		temp = 0;
		for (int j=0; j<64; j++){
#pragma HLS unroll factor = 8
			temp+=buff3[j]*b[j];
		}
		y[i] = temp;
	}
}


void lfilterR(float* b, float* x, float *y, int siz){
#pragma HLS array_partition variable = buff1 block factor=4 dim=1
	float temp;
	for(int i=0; i<siz; i++){
#pragma HLS pipeline II=4
		for(int j=0; j<64-1; j++){
#pragma HLS unroll factor = 8
			buff1[64-1-j] = buff1[64-2-j];
		}
		buff1[0] = x[i];
		temp = 0;
		for (int j=0; j<64; j++){
#pragma HLS unroll factor = 8
			temp+=buff1[j]*b[j];
		}
		y[i] = temp;
	}
}

void lfilterI(float* b, float* x, float *y, int siz){
#pragma HLS array_partition variable = buff2 block factor=4 dim=1
	float temp;
	for(int i=0; i<siz; i++){
#pragma HLS pipeline II=4
		for(int j=0; j<64-1; j++){
#pragma HLS unroll factor = 8
			buff2[64-1-j] = buff2[64-2-j];
		}
		buff2[0] = x[i];
		temp = 0;
		for (int j=0; j<64; j++){
#pragma HLS unroll factor = 8
			temp+=buff2[j]*b[j];
		}
		y[i] = temp;
	}
}

void discrim(float *xI, float* xQ, float* disdata, int siz){
	float b[2] = {1, -1};


	float der_xI[100];
	float derX[100];
	for(int i=0; i<siz;i++){
#pragma HLS unroll factor = 5
#pragma HLS pipeline II=5
		derX[i] = xI[i];
	}
	lfilter1(b,derX, der_xI, siz);


	float der_xQ[100];
	float derQ[100];
	for(int i=0; i<siz;i++){
#pragma HLS unroll factor = 5
#pragma HLS pipeline II=5
		derQ[i] = xQ[i];
	}

	lfilter1(b,derQ, der_xQ, siz);
	for(int i=0; i<siz; i++){
#pragma HLS unroll factor = 5
#pragma HLS pipeline II=5
		disdata[i] = (xI[i]*der_xQ[i]-xQ[i]*der_xI[i])/(xI[i]*xI[i]+xQ[i]*xQ[i]);
	}
}

void lfilter1(float* b, float* x, float *y, int siz){
	float buff[2];
	buff[0] = 0;
	buff[1] = 0;
	float temp;
	for(int i=0; i<siz; i++){
#pragma HLS unroll factor = 5
#pragma HLS pipeline II=5
		buff[1] = buff[0];
		buff[0] = x[i];
		temp = 0;
		temp+=buff[0]*b[0];
		temp+=buff[1]*b[1];
		y[i] = temp;
	}
}



