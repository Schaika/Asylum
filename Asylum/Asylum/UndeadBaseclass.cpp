#include "UndeadBaseclass.h"
#include "randomGen.h"
#include "InitialValues.h"
UndeadBaseclass::UndeadBaseclass()
{
	{
		int number = randomGen::getNumberBetween(0, 99);
		if (number > 33) sex = 1; else sex = 0;
	}
	score = randomGen::getNumberBetween(InitialValues.a2, InitialValues.b2);
}

UndeadBaseclass::~UndeadBaseclass()
{
}

std::wstring UndeadBaseclass::getName()
{
	return name;
}
