// Computational Modelling of Physical Systems
// Week 4, Question 3, Part D
// Program to solve a fourth order differential equation
// Nicholas Kyrke-Smith, 7 February 2008

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double pi = 4 * atan(1.0);

//This function returns the value of dp/dt for a particular position
double dpdt(double x)
{
	return -(pow(x, 3)); 
}

//This function returns the value of dx/dt for a particular momentum
double dxdt(double p)
{
	return p;
}

//This function uses the fourth order Runge-Kutta method to solve the ODE
double rungekutta4(double h, double& y41, double& y42)
{
	double k1a, k2a, k1b, k2b, k1c, k2c, k1d, k2d;

	k1a = h * dpdt(y42);
	k1b = h * dpdt(y42 + (k1a / 2.0));
	k1c = h * dpdt(y42 + (k1b / 2.0));
	k1d = h * dpdt(y42 + k1c);
	y41 = y41 + ((1.0 / 6.0) * (k1a + (2.0 * k1b) + (2.0 * k1c) + k1d));
	
	k2a = h * dxdt(y41);
	k2b = h * dxdt(y41 + (k1a / 2.0));
	k2c = h * dxdt(y41 + (k1b / 2.0));
	k2d = h * dxdt(y41 + k1c);
	y42 = y42 + ((1.0 / 6.0) * (k2a + (2.0 * k2b) + (2.0 * k2c) + k2d));

	return y41;
}

int main()
{
	//y1 controls the amplitude
	double h = 0.01, y = (8 * pi), y1 = 10, y2 = 0;
	double y41 = y1, y42 = y2, ru4, oldru4 = 0, olderru4, oldah;	
	ofstream fout ("w4_3d_output.txt");

	cout << "X\tRunge-Kutta\n";

	double a;

	for (a = 1; a <= (y / h); a++)
	{
		//Obtain the value from the functions at this point in the loop
		olderru4 = oldru4;
		oldru4 = ru4;
		oldah = ((a - 1) * h);	
		ru4 = rungekutta4(h, y41, y42);
		
		//Output it to a file if required
		//fout << (a * h) << "\t";
		//fout << ru4 << "\n";

		//Output the values obtained from the functions
		cout << (a * h) << "\t";
		cout << ru4 << "\n";

		//Tests to see if the previous position was a maximum, and if it was, outputs this position
		//This is the period of oscillation		
		//if ((oldru4 > ru4) && (oldru4 > olderru4))
		//{
		//	cout << oldah << "\n";
		//}
	}

	return 0;
}
