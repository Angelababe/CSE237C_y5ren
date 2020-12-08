#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <math.h>
#include "FM.h"


int main(){
	data_t y[4];
	data_t bt2[128];
	data_t bt1[128];
	for(int i=0; i<128; i++)
		{

			bt2[i] = i/100000;
			bt1[i] = 0.0;
		}
	//stereo(bt2, bt1, y);
	/*for(int i=0; i<sizeof(y); i++){
		printf("%f\n", y[i]);
	}*/
	return 0;
}
