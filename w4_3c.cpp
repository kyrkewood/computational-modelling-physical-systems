// Computational Modelling of Physical Systems
// Week 4, Question 3, Part C
// Program to solve a second order differential equation
// Nicholas Kyrke-Smith, 7 February 2008

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

float pi = 4 * atan(1.0);

float dpdt(float x)
{
	return -x; 
}

float dxdt(float p)
{
	return p;
}

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

float euler(float h, float &y1, float &y2)
{
	y1 = y1 + (h * dpdt(y2));
	y2 = y2 + (h * dxdt(y1));
	
	return y1;
}

float calculated(float yc1, float y)
{
	return (yc1 * cos(y));
}

int main()
{
	float h = 0.1, y = 2 * pi, y1 = 2.0, y2 = 0;
	float yc1 = y1, yr1 = y1, yr2 = y2, y41 = y1, y42 = y2, cal, eul, run, ru4, e, er, e4;
	ofstream fout ("w4_3a_output.txt");

	//cout << "X\tCalculated\tEuler\tRunge-Kutta\n";
	
	for (h = 0.000001; h <= 1; h = h * 2.0)	
	{
		for (float a = 1; a <= (y / h); a++)
		{
			//fout << y2 << "\t" << y1 << "\n";
			//fout << yr2 << "\t" << yr1 << "\n";
			//fout << y42 << "\t" << y41 << "\n";
			
			e = e + (y1 * y1 / 2.0) + (y2 * y2 / 2.0);
			er = er + (yr1 * yr1 / 2.0) + (yr2 * yr2 / 2.0);
			e4 = e4 + (y41 * y41 / 2.0) + (y42 * y42 / 2.0);
	
			cal = calculated(yc1, (a * h));
			eul = euler(h, y1, y2);
			run = rungekutta(h, yr1, yr2);
			ru4 = rungekutta4(h, y41, y42);
			
			//fout << (a * h) << "\t";
			//fout << cal << "\t";
			//fout << eul << "\t"; 
			//fout << run << "\t";
			//fout << ru4 << "\n";
	
			//cout << (a * h) << "\t";
			//cout << cal << "\t" << eul << "\t" << run << "\t" << ru4 << "\n";	
		}

		e = e / (y / h);
		er = er / (y / h);
		e4 = e4 / (y / h);
	
		fout << h << "\t";
		//fout << e - 2.0 << "\t";
		//fout << er - 2.0 << "\t";
		fout << 2.0 - e4 << "\n"; 
	}

	return 0;
}
