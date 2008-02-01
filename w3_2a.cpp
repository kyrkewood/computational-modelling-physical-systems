// Computational Modelling of Physical Systems
// Week 3, Question 2, Part A
// Program to find roots of a function
// Nicholas Kyrke-Smith, 25 January 2008

#include <iostream>
#include <cmath>
#include <fstream>
#include <nag.h>
#include <nag_stdlib.h>
#include <nagc05.h>

using namespace std;

//This function returns the value of the function at a specific point
double funct(double x)
{
	double value = ((5.0/2.0)*cos(x))-log(x);
	return value;
}

//This function returns the differential of the function at a specific point
double differential(double x)
{
	double value = ((-5.0/2.0)*sin(x))-(1.0/x);
	return value;
}

//This function returns the root between two points as determined by the bisection method
double bisection(double xb, double xt)
{
	double xm;
	for (int i = 1; i < 100; i++)
	{	
		xm = (xb + xt)/2.0;

		if (((funct(xb))*(funct(xm))) > 0)
		{
			xb = xm;
		}
		else
		{
			xt = xm;
		}
	}
	return xm;
}

//This function returns the root near a point as determined by the Newton Raphson method
double raphson(double x)
{
	for (int i = 1; i < 100; i++)
	{	
		double m = differential(x);
		double y = funct(x);
		double c = y - (m*x);
		x = (-c)/m; 
	}
	return x;
}

//This function uses a NAG routine to determine a root between two points
double nagroutine(double a, double b)
{
	double x, ftol = 0, xtol = 1e-05;
	static NagError fail;

	nag_zero_cont_func_bd(a, b, &x, funct, xtol, ftol, &fail);
	if (fail.code == NE_NOERROR)
	{
		cout << x;
		return EXIT_SUCCESS;
	}
	else
	{
		cout << fail.message;
		if (fail.code == NE_XTOL_TOO_SMALL || fail.code == NE_PROBABLE_POLE)
		{
			cout << "Final point = " << x;
		}
		return EXIT_FAILURE;
	}
}

int main()
{
	//These are the sets of points to pass to the functions as determined by inspection of the plots
	double a1 = 1.0, b1 = 2.0, a2 = 50, b2 = 6.0, a3 = 6.0, b3 = 7.0;
	
	cout << "By the bisection method" << endl;
	cout << "First root: " << bisection(a1, b1) << "\tSecond root: " << bisection(a2, b2) << "\tThird root: " << bisection(a3, b3) << endl;
	
	cout << "By the Newton Raphson method" << endl;
	cout << "First root: " << raphson(b1) << "\tSecond root: " << raphson(b2) << "\tThird root: " << raphson(b3) << endl;

	cout << "Using a c05adc NAG routine" << endl << "First root: ";	
	nagroutine(a1, b1);
	cout << "\tSecond root: "; 
	nagroutine(a2, b2);
	cout << "\tThird root: ";
	nagroutine(a3, b3);
	cout << endl;
	return 0;
}
