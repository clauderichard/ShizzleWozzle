#ifndef __SW_PDE_PLANE__
#define __SW_PDE_PLANE__

#include <math.h>

struct sw_pde_plane {
	// constants
	double l;
	double g;
	double mb;
	double mh;

	// variables
	double x;
	double y;
	double a;
	double b;
	double c;
	double dx;
	double dy;
	double da;
	double db;

	// applied force
	double fx;
	double fy;

	// flag
	double onfloor;

	sw_pde_plane() {
		reset();
	}

	void reset() {
		l = 2;
		g = 9.8;
		mb = 2;
		mh = 0.3;

		x = 0;
		y = 0;
		a = 0;
		b = 0;
		c = l;
		dx = 0;
		dy = 0;
		da = 0;
		db = 0;

		fx = 0;
		fy = 0;

		onfloor = false;
	}

	void step(double time) {
		double ddx;
		double ddy;
		double dda;
		double ddb;
		
		// calculate accelerations
		double mbpmh = mb+mh;
		double z2 = l*l-a*a-b*b;
		double z = sqrt(z2);
		double b3overa = g/z - (a*da+b*db)*(a*da+b*db)/(z2*z2) - (da*da+db*db)/z2;
		double b3 = a*b3overa;
		double b4 = b*b3overa;
		double l1 = mbpmh*b3 - fx;
		double l2 = mbpmh*b4 - fy;
		double lma = l*l-a*a;
		double lmb = l*l-b*b;

		dda = z2*(l1*(mb*lma + mh*b*b) - l2*mbpmh*a*b) / ( (mb*lmb + mh*a*a)*(mb*lma + mh*b*b) - mbpmh*mbpmh*a*b );
		ddb = z2*(l2*(mb*lmb + mh*a*a) - l1*mbpmh*a*b) / ( (mb*lmb + mh*a*a)*(mb*lma + mh*b*b) - mbpmh*mbpmh*b*b );
		ddx = (fx - mh*dda)/(mb+mh);
		ddy = (fy - mh*ddb)/(mb+mh);

		dx += ddx*time;
		dy += ddy*time;
		da += dda*time;
		db += ddb*time;

		// check if hit floor
		double mdz = (a*da+b*db)/z;
		double newz = z - mdz*time;
		if (newz <= 0.01) onfloor = true;

		x += dx*time;
		y += dy*time;
		a += da*time;
		b += db*time;

		if (sqrt(a*a+b*b) >= l - 0.2) {
			onfloor = true;
		} else {
			c = sqrt(l*l-a*a-b*b);
		}
	}
};

#endif