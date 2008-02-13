// Computational Modelling of Physical Systems
// Week 4, Question 3, Part A
// Program to solve a second order differential equation
// Nicholas Kyrke-Smith, 7 February 2008

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

float pi = 4 * atan(1.0);

//This function returns the value of dp/dt for a particular position
float dpdt(float x)
{
	return -x; 
}

//This function returns the value of dx/dt for a particular momentum
float dxdt(float p)
{
	return p;
}

//This function uses the second order Runge-Kutta method to solve the ODE
float rungekutta(float h, float& yr1, float& yr2)
{
	float k1a, k2a, k1b, k2b;

	k1a = h * dpdt(yr2);
	k1b = h * dpdt(yr2 + (k1a / 2.0));
	yr1 = yr1 + k1b;
	
	k2a = h * dxdt(yr1);
	k2b = h * dxdt(yr1 + (k2a / 2.0));
	yr2 = yr2 + k2b;

	return yr1;
}

//This function uses the fourth order Runge-Kutta method to solve the ODE
float rungekutta4(float h, float& y41, float& y42)
{
	float k1a, k2a, k1b, k2b, k1c, k2c, k1d, k2d;

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

//This function uses Euler's method to solve the ODE
float euler(float h, float &y1, float &y2)
{
	y1 = y1 + (h * dpdt(y2));
	y2 = y2 + (h * dxdt(y1));
	
	return y1;
}

//This function returns the calculated of the solution at a particular point for the SHO
float calculated(float yc1, float y)
{
	return (yc1 * cos(y));
}

int main()
{
	//y1 controls the amplitude
	float h = 0.1, y = 2 * pi, y1 = 2.0, y2 = 0;
	float yc1 = y1, yr1 = y1, yr2 = y2, y41 = y1, y42 = y2, cal, eul, run, ru4;	
	ofstream fout ("w4_3a_output.txt");

	cout << "X\tCalculated\tEuler\t2nd order Runge-Kutta\t4th order Runge-Kutta\n";

	float a;

	for (a = 1; a <= (y / h); a++)
	{
		//For creating the phase space plots		
		//fout << y2 << "\t" << y1 << "\n";
		//fout << yr2 << "\t" << yr1 << "\n";
		//fout << y42 << "\t" << y41 << "\n";

		//Obtain the values from the four functions at this point in the loop
		cal = calculated(yc1, (a * h));
		eul = euler(h, y1, y2);
		run = rungekutta(h, yr1, yr2);
		ru4 = rungekutta4(h, y41, y42);
		
		//Output them to a file if required
		//fout << (a * h) << "\t";
		//fout << cal << "\t";
		//fout << eul << "\t"; 
		//fout << run << "\t";
		//fout << ru4 << "\n";

		//Output the values obtained from the functions
		cout << (a * h) << "\t";
		cout << cal << "\t" << eul << "\t" << run << "\t" << ru4 << "\n";	
	}

	return 0;
}
