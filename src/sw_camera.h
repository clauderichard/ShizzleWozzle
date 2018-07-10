#ifndef __SW_CAMERA__
#define __SW_CAMERA__

#include "math.h"

struct sw_vector {
	double x;
	double y;
	double z;

	sw_vector(double thex, double they, double thez) {
		x = thex;
		y = they;
		z = thez;
	}
};

struct sw_camera {
	double phi;
	double theta;
	double spread; // tangent of the angle

	double x;
	double y;
	double z;

	sw_camera() {
		phi = 0.0;
		theta = 0.0;
		spread = 1.0;

		x = 0;
		y = 0;
		z = 0;
	}

	sw_vector project(sw_vector obj) {
		double oldx = obj.x-x;
		double oldy = obj.y-y;
		double oldz = obj.z-z;
		double newx = oldx*sin(theta) - oldy*cos(theta);
		double newy = oldz*sin(phi) - oldx*cos(theta)*cos(phi) - oldy*cos(phi)*sin(theta);
		double newz = oldx*sin(phi)*cos(theta) + oldy*sin(phi)*sin(theta) + oldz*cos(phi);
		double wide = newz*spread;
		return sw_vector(newx/wide, newy/wide, newz);
	}
	
};

#endif