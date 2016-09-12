#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <stdbool.h> 

double GetRand(double min, double max)
{
	double temp = (double)rand() / (double)RAND_MAX;


	temp = min + (max - min)*temp;


	return temp;
}


bool ell(const double x, const double y)
{
	const double x_c = 0.7;
	const double y_c = 0.5;
	const double r = 0.5;


	const double f = y_c*y_c*(x - x_c)*(x - x_c) + x_c*x_c*(y - y_c)*(y - y_c) - y_c*y_c*x_c*x_c;
	if (f > 0.0)return false;
	else return true;
}


void main()
{
	FILE*op = fopen("ell.txt", "w");
	srand((unsigned int)time(NULL));

	//make circles
	for (int i = 0; i < 10000; i++)
	{
		double x = GetRand(0.0, 1.4);
		double y = GetRand(0.0, 1.0);


		if (ell(x, y) == true)
			fprintf(op, "%f %f\n", x, y);
	}

	

	fclose(op);


}