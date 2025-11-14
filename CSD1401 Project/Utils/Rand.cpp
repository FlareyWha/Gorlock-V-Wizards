#include "Rand.h"

int randInt(int m, int n) 
{
	return rand() % (n - m + 1) + m;
}

float randFloat(float m, float n) 
{
	return ((float)rand() / (float)RAND_MAX) * (n - m) + m;
}