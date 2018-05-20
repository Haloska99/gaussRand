#pragma once

#include <math.h>
#include <cstdlib>

double gaussFnc(double x, double sgm = 1, double x0 = 0);
double gaussRand(double sgm = 1, double x0 = 0, double rng = 5);
double myRnd(void){ return rand()/double(RAND_MAX); }
double myRnd(double a, double b){
	if(a>b) swap(a,b);
	return myRnd()*(b-a)+a;
}
double gaussFnc(double x, double sgm, double x0)
{
	double b = (x-x0)/sgm;
	return exp(-b*b/2) / (sqrt(2*M_PI)*sgm);
}
double gaussRand(double sgm, double x0, double rng)
/*
 * the wider is the range the slower is the function
 * time_per_fucntion ~ (rng * gaussFnc(x0, sgm, x0)) / (\int{gaussFnc(x, sgm, x0) * dx} from x0 to x0+rng)
 */
{
	rng *= sgm;
	double x;
	double y0 = 1.0/(sqrt(2*M_PI)*sgm); //y0 = gaussFnc(x0, sgm, x0); // max value
	double xl = x0-rng, xr = x0+rng;

	do{
		x = myRnd(xl, xr);
	}while(myRnd(0, y0) > gaussFnc(x, sgm, x0));

	return x;
}

/*
 * 
 * usage: 
 * ----------------
 * double x = myRnd();              // uniform random distribution in [0;1]
 * double x = myRnd(-13; 321);      // uniform random distribution in [-13; 321]
 * double x = myRnd(321; -13);      // uniform random distribution in [-13; 321]
 * ----------------
 * double x = gaussRand();          // random number with gauss distribution with \sigma=1 & \mu=0 in range [-5*\sigma; 5*sigma] // 5 is set by default
 * double x = gaussRand(2);         // random number with gauss distribution with \sigma=2 & \mu=0 in range [-5*\sigma; 5*sigma]
 * double x = gaussRand(3, 123);    // random number with gauss distribution with \sigma=3 & \mu=123 in range [-5*\sigma; 5*sigma]
 * double x = gaussRand(1, 0, 10);  // random number with gauss distribution with \sigma=1 & \mu=0 in range [-10*\sigma; 10*sigma]
 * 
 */
