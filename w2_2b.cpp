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

int main()
{
	ofstream fout ("w2_2b.txt");	
	int n;
	double pi = 4 * atan(1);
	double intervals, area, totalarea, left, right, i = 0;
	
	cout << "How many intervals do you want to use? ";
	cin >> n;

	intervals = 1.0/n;
 	totalarea = 0;
	
	cout << "x\te^(-x)sin(x)" << endl;

	for (i = 0; i <= pi; i = i + intervals)
	{
		cout << i << "\t" << func(i) << endl;
		fout << i << "\t" << func(i) << endl;
	}
}
