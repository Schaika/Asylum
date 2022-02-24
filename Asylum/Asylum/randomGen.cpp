#include "randomGen.h"
#include <ctime>
#include <cstdlib>
int randomGen::getNumber(int a, int n)
{
	int number = a + rand() % n;
	return number;
}
int randomGen::getNumberBetween(int a, int b)
{
	int n = b - a + 1;
	return getNumber(a, n);
}
int randomGen::getNumberBool()
{
	return getNumberBetween(0, 1);
}