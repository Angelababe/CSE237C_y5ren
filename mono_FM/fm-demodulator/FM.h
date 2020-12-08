/*
	Filename: fir.h
		Header file
		FIR lab wirtten for WES/CSE237C class at UCSD.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <math.h>
typedef float data_t;
void stereo(data_t* xi, data_t* xr, data_t*y);
void downsample(data_t* x, int M, int SIZE);
void lfilter(float* b, data_t* x, int SIZE);
void discrim(data_t *xi, data_t* xr, data_t* disdata, int SIZE);

