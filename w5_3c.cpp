// Computational Modelling of Physical Systems
// Week 5, Question 3, Parts C and D
// Program to evaluate oscillating masses connected by springs
// Nicholas Kyrke-Smith, 14 February 2008

#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <nag.h>
#include <nag_stdlib.h>
#include <nagf02.h>

using namespace std;

#define A(I,J) a[(I)*tda + J]
#define V(I,J) v[(I)*tdv + J]

//Uses the NAG routine nag_real_symm_eigensystem (f02abc)
//Once compiled as a.out, the program should be run by typing ./a.out < w5_3c.d

int main()
{
	ofstream fout ("w5_3c_output.txt");
	
	Integer exit_status=0, i, j, n, tda, tdv;
	NagError fail;

	double *a=0, *r=0, *v=0;

	INIT_FAIL(fail);

	//Skip heading in data file
	Vscanf("%*[^\n]");
	Vscanf("%ld", &n);
	if (n >= 1)
	{
		if ( !( a = NAG_ALLOC(n*n, double)) || !( r = NAG_ALLOC(n, double)) || !( v = NAG_ALLOC(n*n, double)) )
		{
			cout << "Allocation failure\n";
			exit_status = -1;
			goto END;
		}
		tda = n;
		tdv = n;
	}

	else
	{
		cout << "Invalid n.\n";
		exit_status = 1;
		return exit_status;
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			Vscanf("%lf", &A(i,j));
		}
	}
	
	nag_real_symm_eigensystem(n, a, tda, r, v, tdv, &fail);

	if (fail.code != NE_NOERROR)
	{
		cout << "Error from nag_real_symm_eigensystem (f02abc).\n" << fail.message;
		exit_status = 1;
		goto END;
	}

	cout << "Eigenvalues\n\t";

	for (i = 0; i < n; i++)
	{
		cout << setprecision(4) << fixed << r[i] << "\t";

		if (i % 8 == 7)
		{
			cout << endl << endl; 
		}		
	}

	cout << "Eigenvectors\n";

	for (i = 0; i < n; i++)
	{
		cout << i << "\t";
		fout << i << "\t";		

		for (j = 0; j < n; j++)
		{
			cout << setprecision(4) << fixed << V(i,j) << "\t";
			fout << setprecision(4) << fixed << V(i,j) << "\t";
			if (j % 8 == 7)
			{
				cout << endl;
				fout << endl;
			}	
		}
	}

	END:
	if (a) NAG_FREE(a);
	if (r) NAG_FREE(r);
	if (v) NAG_FREE(v);
	return exit_status;
}
