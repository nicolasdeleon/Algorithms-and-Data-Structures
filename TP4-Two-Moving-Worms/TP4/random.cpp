#include "random.h"




double randNormalize()
{
	return rand() / (double)RAND_MAX;
}

double randBetweenReal(double a, double b)
{
	return randNormalize()*(b - a) + a;
}