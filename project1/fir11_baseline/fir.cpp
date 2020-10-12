/*
	Filename: fir.cpp
		FIR lab wirtten for WES/CSE237C class at UCSD.

	INPUT:
		x: signal (chirp)

	OUTPUT:
		y: filtered output

*/

#include "fir.h"

void fir (
  data_t *y,
  data_t x
  )
{
	coef_t c[N] = {53, 0, -91, 0, 313, 500, 313, 0, -91, 0,53};
	static data_t data[11];
	
	//shift
	for(int i=10; i>0; i--){
		data[i]=data[i-1];
	}
	data[0] = x;
	
	acc_t acc=0;
	//accumulate
	for(int i=0; i<11; i++){
		acc+=data[i]*c[i];
	}
	
	*y=acc;
}


