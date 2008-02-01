// Computational Modelling of Physical Systems
// Week 3, Question 2, Part B
// Program to find the value of the integral limits that give a certain value of the Gaussian integral
// Nicholas Kyrke-Smith, 30 January 2008

#include <iostream>
#include <cmath>
#include <fstream>
#include <nag.h>
#include <nag_stdlib.h>
#include <nagd01.h>
#include <nagx01.h>

using namespace std;

double pi = 4 * atan(1);

//This returns the value of e^(-(x^2)/2) at a given point
double funct(double x)
{
	return exp((-(x*x))/2);
}

//This function rounds a value to a certain number of decimal places
double rounded(double num, double places)
{
	num = num * pow(10, places);
	num = num + 0.5;
	num = floor(num);
	num = num / pow(10, places);
	return num;
}

//This is a NAG routine that integrates the function between two given points
double integral(double a, double b)
{
	double epsabs, abserr, epsrel, result;
	int max_num_subint = 200;

	Nag_QuadProgress qp;
  	static NagError fail;
	
	epsabs = 0.0;
	epsrel = 0.000001;

 	nag_1d_quad_gen(funct, a, b, epsabs, epsrel, max_num_subint, &result, &abserr, &qp, &fail);

	if (fail.code != NE_NOERROR)
	{
		cout << fail.message;
	}
	if (fail.code != NE_INT_ARG_LT && fail.code != NE_ALLOC_FAIL && fail.code != NE_NO_LICENCE)
    	{
		NAG_FREE(qp.sub_int_beg_pts);
      		NAG_FREE(qp.sub_int_end_pts);
		NAG_FREE(qp.sub_int_result);
		NAG_FREE(qp.sub_int_error);
		return result;
    	}
  	else
	{		return EXIT_FAILURE;
	}
}

//This function multiplies the integral by the factor of 1/(root(2pi)
double overallfunction(double a, double b)
{
	double integralpart = integral(a,b);
	return (1/(sqrt(2*pi)))*integralpart;
}

int main()
{
	double p;
	
	//Tollerance defines the number of decimal places to which the overall function should be accurate
	//Note also the tollerance within the integration routine
	int tollerance = 6;
	
	//These are declared so it can be seen later whether the loop has completed because of the limit or the required accuracy
	int j, looplimit = 100000;
	
	cout << "This program will find the limits of the integral that give a certain overall value of the Gaussian integral. \n";
	cout << "What overall value of the Gaussian integral (greater than 0 and less than or equal to 1) do you want? ";
	cin >> p;

	//Handles input errors	
	while ((p <= 0) || (p > 1))
	{
		cout << "You entered " << p << ". The value must be greater than 0 and less than or equal to 1. Please re-enter a value. ";
		cin >> p;
	}
	
	//Uses the bisection method to find the limit at which the function gives the required value
	double estp = 0, loweresta, mida, upperesta = 0, interval = (1.0/100000), evaluated;	
	
	for (double i = interval; estp < p; i = i + interval)
	{	
		loweresta = upperesta;		
		upperesta = i;		
		estp = overallfunction(-i,i);
	}

	for (j = 1; j < looplimit && (rounded(overallfunction(-mida, mida), tollerance) != rounded(p, tollerance)); j++)
	{	
		mida = (loweresta + upperesta)/2.0;
	
		if (overallfunction(-mida, mida) > p)
		{
			mida = (loweresta + mida)/2.0;
		}
		else
		{
			mida = (upperesta + mida)/2.0;
		}
	}

	evaluated = overallfunction(-mida, mida);

	cout << "Evaluation of the Gaussian integral between -" << mida << " and " << mida << " gives " << evaluated << ".\n";

	//If the loop has been exited because the function had given the required accuracy, output the value of the tollerance variable
	if (j < looplimit)
	{
		cout << "The Gaussian integral has been evaluated so it is accurate to " << tollerance << " decimal places.\n";
	}

	//Otherwise find out how accurate the evaluation is
	else
	{
		for (double i = tollerance; (rounded(overallfunction(-mida, mida), i) != rounded(p, i)); i--)
		{
			if (rounded(overallfunction(-mida, mida), (i-1)) == rounded(p, (i-1)))
			{
				cout << "The Gaussian integral has been evaluated so it is accurate to " << i << " decimal places.\n";
			}
		}
	}

	return 0;
}
