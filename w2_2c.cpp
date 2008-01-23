#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double func(double i)
{
	double fun;	
	fun = (exp(-i)*sin(i));
	return fun;
}

double calculatedintegral()
{
	double fun;
	fun = (1-(exp(-2)*cos(2))-(exp(-2)*sin(2)))*0.5;
	return fun;
}

double area(int n)
{
	double interval, area, totalarea, left, right, i = 0;
	
	interval = 1.0/n;
 	totalarea = 0;

	while (i <= 2)
	{
		left = func(i);
		i = i + interval;
		right = func(i);

		area = ((left + right)/2)*interval;

		totalarea = totalarea + area;
	}

	return totalarea;
}

int main()
{
	ofstream fout ("w2_2c_output.txt");	
	double calculated = calculatedintegral();
	double trapezium, erroront;	

	cout << "Calculated: " << calculated << endl;	
	cout << "Intervals\tEvaluation\tDifference from calculated\n";
	fout << "Intervals\tEvaluation\tDifference from calculated\n";
	
	for (int n = 1; n <=500; n++)
	{
		trapezium = area(n);
		erroront = calculated - trapezium;		
		cout << n << "\t" << trapezium << "\t" << erroront << endl;
		fout << n << "\t" << trapezium << "\t" << erroront << endl;		
	}
}
