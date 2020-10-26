#include<math.h>
#include "dft.h"
#include"coefficients256.h"

void dft(DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE])
{
	int i=0, j=0, f;
		DTYPE real[SIZE];
		DTYPE imag[SIZE];
		DTYPE w;
		for(i=0; i<SIZE; i++){
			real[i] = 0;
			imag[i] = 0;
			w = (2.0* 3.141592653589 /SIZE) * ((DTYPE)i);
			for(j=0; j<SIZE; j++){
				real[i] += (real_sample[j]*cos_coefficients_table[(i*j)%SIZE] - imag_sample[j]*sin_coefficients_table[(i*j)%SIZE]);
				imag[i] += (real_sample[j]*sin_coefficients_table[(i*j)%SIZE] + imag_sample[j]*cos_coefficients_table[(i*j)%SIZE]);
			}
		}
		for(i=0; i<SIZE; i++){
			real_sample[i] = real[i];
			imag_sample[i] = imag[i];
		}
}
