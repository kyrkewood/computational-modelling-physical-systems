// Computational Modelling of Physical Systems
// Payloads project
// Program to solve the motion of a rocket under a uniform gravitational field
// Nicholas Kyrke-Smith, 6 March 2008

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double pi = 4 * atan(1.0);

//Define the burn time, natural gravitational timescale and the critical time
double tb = 4000, tg = 804.9, tc = 10000;

double dqdt(double t, double yr1)
{
	return (pow(tb, 2) / pow(tg, 2)) * (((tc / tb) * (1 / (1 - t))) - 1); 
}

double dsdt(double q)
{
	return q;
}

//Returns the calculated velocity at a particular time
double calculatedv(double t)
{
	return ((-tb * tc / pow(tg, 2)) * log(1 - t)) - (pow(tb, 2) * t / pow(tg, 2));
}

//Returns the calculated position at a particular time
double calculateds(double y1, double t)
{
	return ((tb * tc / pow(tg, 2)) * (((1 - t) * log(1 - t)) + t)) - ((pow(tb, 2) / pow(tg, 2)) * (pow(t, 2) / 2)) + 1;
}

double rungekutta(double h, double& yr1, double& yr2, double t)
{
	double k1a, k2a, k1b, k2b;

	k1a = h * dsdt(yr2);
	k2a = h * dqdt(t, yr1);

	k1b = h * dsdt(yr2 + (k2a / 2.0));
	k2b = h * dqdt((t + (h / 2.0)), (yr1 + (k1a / 2.0)));

	yr1 = yr1 + ((k1a + k1b) / 2.0);
	yr2 = yr2 + ((k2a + k2b) / 2.0);

	return yr1; 
}

double rungekutta4(double h, double& y41, double& y42, double t)
{
	double k1a, k2a, k1b, k2b, k1c, k2c, k1d, k2d;

	k1a = h * dsdt(y42);
	k2a = h * dqdt(t, y41);

	k1b = h * dsdt(y42 + (k2a / 2.0));
	k2b = h * dqdt((t + (h / 2.0)), (y41 + (k1a / 2.0)));

	k1c = h * dsdt(y42 + (k2b / 2.0));
	k2c = h * dqdt((t + (h / 2.0)), (y41 + (k1b / 2.0)));

	k1d = h * dsdt(y42 + k2c);
	k2d = h * dqdt((t + h), (y41 + k1c));	

	y41 = y41 + ((1.0 / 6.0) * (k1a + (2.0 * k1b) + (2.0 * k1c) + k1d));
	y42 = y42 + ((1.0 / 6.0) * (k2a + (2.0 * k2b) + (2.0 * k2c) + k2d));

	return y41;
}

int main()
{
	ofstream fout ("Project4c_output.dat");

	//y1 is the start point, y2 is the initial velocity
	double h = 0.0001, y1 = 1, y2 = 0;

	//The values of y1 and y2 are copied to variables specifically for each of the two Runge-Kutta methods
	double yr1 = y1, yr2 = y2, y41 = y1, y42 = y2, run, ru4;

	cout << "log(h)\tError using RU2\tError using RU4\n";

	double ru2error = 0, ru4error = 0;
	double a, t;

	for (t = h; t < 0.9999999999; t = t + h)
	{
		//Obtain the values from the functions at this point in the loop
		run = rungekutta(h, yr1, yr2, t);
		ru4 = rungekutta4(h, y41, y42, t);

		ru2error = pow(((calculateds(y1, t) - run) * (calculateds(y1, t) - run)), 0.5);
		ru4error = pow(((calculateds(y1, t) - ru4) * (calculateds(y1, t) - ru4)), 0.5);

		cout << t << "\t" << ru2error << "\t" << ru4error << endl;
		fout << t << "\t" << ru2error << "\t" << ru4error << endl;
	}

	return 0;
}
