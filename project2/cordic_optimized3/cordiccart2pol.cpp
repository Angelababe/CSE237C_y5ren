#include "cordiccart2pol.h"
#include <ap_fixed.h>

ap_fixed <32,6> Kvalues[NO_ITER] = {1,	0.500000000000000,	0.250000000000000,	0.125000000000000,	0.0625000000000000,	0.0312500000000000,	0.0156250000000000,	0.00781250000000000,	0.00390625000000000,	0.00195312500000000,	0.000976562500000000,	0.000488281250000000,	0.000244140625000000,	0.000122070312500000,	6.10351562500000e-05,	3.05175781250000e-05};

data_t angles[NO_ITER] = {0.785398163397448,	0.463647609000806,	0.244978663126864,	0.124354994546761,	0.0624188099959574,	0.0312398334302683,	0.0156237286204768,	0.00781234106010111,	0.00390623013196697,	0.00195312251647882,	0.000976562189559320,	0.000488281211194898,	0.000244140620149362,	0.000122070311893670,	6.10351561742088e-05,	3.05175781155261e-05};


void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta)
{
	// Write your code here
	//determine the quadrant
		*theta = 0;
		*r = 0;
		int rot=0;
		float factor=1;
		data_t trans;
		if(y>0){
			//point in quadrant 2, rotate 90 degree
			if(x<0){
				trans = x;
				x = y;
				y = -trans;
				rot = 1;
			}
		}
		else if(y<0){
			//point in quadrant 3, rotate -90 degree
			if(x<0){
				trans = x;
				x = -y;
				y = trans;
				rot = -1;
			}
		}
		else{
			//point on axis
			if(x>0){
				*r = x;
				*theta = M_PI;
			}
			else if(x<0){
				*r = x;
				*theta = -M_PI;
			}
			else{
				*r=0;
				*theta=0;
			}
		}

		int i=0;
		while(i<NO_ITER){
			if(y>0){
				trans = x;
				x = x + float(((ap_fixed <32,6>) y)*Kvalues[i]);
				y = -float(((ap_fixed <32,6>) trans)*Kvalues[i]) + y;
				*theta+=angles[i];
			}
			else{
				trans = x;
				x = x - float(((ap_fixed <32,6>) y)*Kvalues[i]);
				y = float(((ap_fixed <32,6>) trans)*Kvalues[i]) + y;
				*theta-=angles[i];
			}
			factor = factor/cos(angles[i]);
			i++;
		}
		*r = x/factor;
		*theta += rot*M_PI/2;
}
