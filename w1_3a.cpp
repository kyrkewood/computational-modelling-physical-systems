#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double N, phi;

int main()
{
	ofstream fout ("output.txt");	
	cout << "What power do you want to raise Phi to? ";
	cin >> N;
	phi = (-1+(sqrt(5)))/2;

	for(int power = 0; power <= N; power++) 
	{
		fout << "Phi^" << power << "\t" << pow(phi,power) << endl;
	}	
	return 0;
}

