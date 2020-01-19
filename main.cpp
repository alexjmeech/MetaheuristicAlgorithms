#include "TSPAlgorithmDispatcher.h"
#include "TSP.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(int argv, char** argc)
{
	srand (time(NULL));

	Algorithm* a = new TSP();
	a->Load("input/");

	for (int i = TSPAlgorithmType::GENETIC; i < TSPAlgorithmType::END_TSP; i++)
	{
		a->Select(i);

		for (unsigned long long config : TSPAlgorithmDispatcher::getAlgorithmConfigurations((TSPAlgorithmType) i))
		{
			a->Configure(config);
			a->Execute();
			a->Display();
			a->Stats();
			a->Save();
		}
	}

	return 0;
}
