#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <math.h>
#include "ap_int.h"
struct axis_t{
	float data;
	ap_int<1> last;
};
#define SIZE 1000
void FM(axis_t* xi, axis_t* xr, axis_t*y);
void downsample(float*y, float* x, int M, int siz);
void lfilterR(float* b, float* x, float *y, int siz);
void lfilterI(float* b, float* x, float *y, int siz);
void lfilterD(float* b, float* x, float *y, int siz);
void lfilter1(float* b, float* x, float*y, int siz);
void discrim(float *xi, float* xr, float* disdata, int siz);

