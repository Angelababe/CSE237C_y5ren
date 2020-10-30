#include<math.h>
#include "dft.h"
#include"coefficients256.h"

void dft(DTYPE input_real[SIZE], DTYPE input_imag[SIZE], DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE])
{
	int i=0, j=0, f;
		DTYPE real[SIZE];
		DTYPE imag[SIZE];
		for(i=0; i<SIZE; i++){
			real[i] = 0;
			imag[i] = 0;
			for(j=0; j<SIZE; j++){
				real[i] += (input_real[j]*cos_coefficients_table[(i*j)%SIZE]
						- input_imag[j]*sin_coefficients_table[(i*j)%SIZE]);
				imag[i] += (input_real[j]*sin_coefficients_table[(i*j)%SIZE]
						+ input_imag[j]*cos_coefficients_table[(i*j)%SIZE]);
			}
		}
		for(i=0; i<SIZE; i++){
			real_sample[i] = real[i];
			imag_sample[i] = imag[i];
		}
}
