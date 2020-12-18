#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <math.h>
#include "FM.h"


int main(){
	axis_t y[20];
	axis_t bt2[1000];
	axis_t bt1[1000];
	for(int i=0; i<1000; i++)
		{

			bt2[i].data = i;
			bt1[i].data = float(i)/5;
		}
	FM(bt2, bt1, y);
	for(int i=0; i<20; i++){
		printf("%f\n", y[i]);
	}
	return 0;
}
