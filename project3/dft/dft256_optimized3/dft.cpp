#include<math.h>
#include "dft.h"
#include"coefficients256.h"

void dft(DTYPE input_real[SIZE], DTYPE input_imag[SIZE], DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE])
{
	int i=0, j=0, f;
#pragma HLS array_partition variable=input_real cyclic factor = 8
#pragma HLS array_partition variable=input_imag cyclic factor = 8
		for(i=0; i<SIZE; i++){
			for(j=0; j<SIZE; j++){
	#pragma HLS unroll factor = 8
				real_sample[i] += (input_real[j]*cos_coefficients_table[(i*j)%SIZE]
						- input_imag[j]*sin_coefficients_table[(i*j)%SIZE]);
				imag_sample[i] += (input_real[j]*sin_coefficients_table[(i*j)%SIZE]
						+ input_imag[j]*cos_coefficients_table[(i*j)%SIZE]);
			}
		}
}
