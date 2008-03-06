// Computational Modelling of Physical Systems
// Payloads project
// Program to investigate the payload achievable for a given burn-time
// Nicholas Kyrke-Smith, 4 March 2008

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double pi = 4 * atan(1.0);

//Define the burn time, natural gravitational timescale and the critical time
double tb, tg = 804.9, tc = 10000, r0 = 6368000;

double dqdt(double t, double yr1)
{
	return (tb / (pow(tg, 2))) * ((tc / (1 - t)) - (tb / pow(yr1, 2))); 
}

double dsdt(double q)
{
	return q;
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

double energy(double y42, double y41)
{
	return ((1.0 / 2.0) * (pow(y42, 2))) - ((pow(tb, 2) / pow(tg, 2)) * (1.0 / y41));
}

int main()
{
	ofstream fout ("Project5_output.dat");

	//y1 is the start point, y2 is the initial momentum
	double h = 0.0001, y1 = 1, y2 = 0;

	cout << "What burn time would you like to use?\n";
	cin >> tb;
	/*while (tb <= 0)
	{
		cout << "Please enter a number greater than 0.\n";
		cin >> tb;
	}*/

	//The values of y1 and y2 are copied to variables specifically for each of the two Runge-Kutta methods
	double yr1 = y1, yr2 = y2, y41 = y1, y42 = y2, run, ru4;
	double a, t;
for (tb = 1; tb < 2000; tb = tb + 10)
{
	for (t = h; t < 0.9999999999; t = t + h)
	{
		//Obtain the values from the function at this point in the loop
		ru4 = rungekutta4(h, y41, y42, t);

		if (energy(y42, y41) > 0)
		{
			//cout << "The maximum payload is " << (1 - t) * 100 << "% of the entire rocket.\n";
			cout << tb << "\t" << (1 - t) << endl;
			fout << tb << "\t" << (1 - t) << endl;			
			break;
		}
	}
	
	if (energy(y42, y41) < 0)
	{
		cout << "Did not escape";
	}
}
	return 0;
}
