#include<math.h>
#include "dft.h"
#include"coefficients256.h"

void dft(DTYPE input_real[SIZE], DTYPE input_imag[SIZE], DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE])
{
#pragma HLS DATAFLOW
#pragma HLS array_partition variable=input_real cyclic factor = 8
#pragma HLS array_partition variable=input_imag cyclic factor = 8
	int i=0, j=0, real=0, imag=0;
	mvp (i,j,real, imag, input_real,input_imag,real_sample,imag_sample);
}

void split1 (DTYPE *real, DTYPE *imag, DTYPE real_sample, DTYPE imag_sample){
	*real = real_sample;
	*imag = imag_sample;
}

void mvp (int i, int j, DTYPE real, DTYPE imag, DTYPE input_real[SIZE],
		DTYPE input_imag[SIZE],DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE]){
	for(i=0; i<SIZE; i++){
		real = 0;
		imag = 0;
		for(j=0; j<SIZE; j++){
#pragma HLS unroll factor = 8
#pragma HLS pipeline
			real_sample[i] += (input_real[j]*cos_coefficients_table[(i*j)%SIZE]
					- input_imag[j]*sin_coefficients_table[(i*j)%SIZE]) + real;
			imag_sample[i] += (input_real[j]*sin_coefficients_table[(i*j)%SIZE]
					+ input_imag[j]*cos_coefficients_table[(i*j)%SIZE]) + imag;
			split1 (&real, &imag, real_sample[i], imag_sample[i]);
		}
	}
}


