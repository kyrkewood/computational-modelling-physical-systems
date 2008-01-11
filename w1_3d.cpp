#include <iostream>
#include <cmath>

//Included when a file output is required
//#include <fstream>

using namespace std;

//The variables used for the calculated value and for the recursive double calculation
double phi, olderphi, oldphi, phin, phi1, phi0;

//The variables used for the recursive float calculation
float folderphi, foldphi, fphin, fphi1, fphi0;
int N;

int main()
{
	//Used when the output is required in a file 	
	//ofstream fout ("output.txt");
	
	//Choose the power to which phi is raised	
	cout << "What do you want to raise Phi to? ";
	cin >> N;
	
	//Headings for the output table	
	cout << "Power\tCalculated\tRecursive (double)\tRecursive (float)\n";	
	//Used when outputting to a file	
	//fout << "Power\tCalculated\tRecursive (double)\tRecursive (float)\n";
	
	phi = (-1+(sqrt(5)))/2;		//For the calculated values
	phi1= (-1+(sqrt(5)))/2;		//The initial value of phi for the recursive double calculation
	phi0 = 1;			//The initial value of phi^0 for the recursive double calculation
	oldphi = phi0 - phi1;		//phi^2 calculated for the recursive double calculation
	olderphi = phi1; 		//The initial value for the lower value in the relation phi^(n+1) = phi^(n-1) - phi^n
	fphi1 = (-1+(sqrt(5)))/2;	//The initial value of phi for the recursive float calculation
	fphi0 = 1;			//The initial value of phi^0 for the recursive float calculation
	foldphi = fphi0 - fphi1;	//phi^2 calculated for the recursive float calculation
	folderphi = fphi1;		//The initial value for the lower value in the relation for the float calculation
	
	//Loop through until the values are calculated for the highest power	
	for(int power = 0; power <= N; power++)
	{
		//A switch statement to cover the special cases of lower values		
		switch (power)
		{
		
		//This is known to be 1, and cannot really be calculated using the phi^(n+1) = phi^(n-1) - phi^n relationship		
		case 0:
			phin = 1;
			fphin = 1;
			cout << power << "\t" << pow(phi,power) << "\t\t" << phin << "\t\t\t" << fphin << endl;

			//Used when outputting to a file		
			//fout << power << "\t" << pow(phi,power) << "\t" << phin << "\t" << fphin << endl;			
			break;

		//This is phi itself, and cannot really be calculated using the phi^(n+1) = phi^(n-1) - phi^n relationship
		case 1:
			phin = (-1+(sqrt(5)))/2;
			fphin = (-1+(sqrt(5)))/2;
			cout << power << "\t" << pow(phi,power) << "\t" << phin << "\t\t" << fphin << endl;

			//Used when outputting to a file
			//fout << power << "\t" << pow(phi,power) << "\t" << phin << "\t" << fphin << endl;	
			break;
		
		//This is the first value that is calculated using the phi^(n+1) = phi^(n-1) - phi^n relationship, but phi^0 is 1	
		case 2:
			phin = 1 - (-1+(sqrt(5)))/2;
			fphin = 1 - (-1+(sqrt(5)))/2;
			cout << power << "\t" << pow(phi,power) << "\t" << phin << "\t\t" << fphin << endl;

			//Used when outputting to a file
			//fout << power << "\t" << pow(phi,power) << "\t" << phin << "\t" << fphin << endl;	
			break;

		//All other cases are covered using the phi^(n+1) = phi^(n-1) - phi^n relationship	
		default:
			//The next value towards phi^N is calculated using both the double and float relationships		
			phin = olderphi - oldphi;		
			fphin = folderphi - foldphi;		

			//The values are output, along with the power and a calculated value using cmath's pow			
			cout << power << "\t" << pow(phi,power) << "\t" << phin << "\t\t" << fphin << endl;
			
			//Used when outputting to a file
			//fout << power << "\t" << pow(phi,power) << "\t" << phin << "\t" << fphin << endl;

			//The values are moved into the correct variables for the next time round the loop
			olderphi = oldphi;		
			oldphi = phin;			
			folderphi = foldphi;		
			foldphi = fphin;
			break;
		}
	}
	return 0;
}
