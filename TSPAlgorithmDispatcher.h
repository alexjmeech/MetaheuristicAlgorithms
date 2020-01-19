#ifndef TSPALGORITHMDISPATCHER_H_
#define TSPALGORITHMDISPATCHER_H_

#include "AlgorithmSummary.h"
#include "Point3D.h"
#include "Chromosome.h"
#include <utility>
#include <set>
#include <vector>
using namespace std;

enum TSPAlgorithmType
{
	GENETIC,
	TABU_SEARCH,
	END_TSP
};

enum GeneticSelectionType: unsigned short
{
	ELITISM,
	ROULETTE,
	END_SELECTIONS
};

enum GeneticCrossoverType: unsigned short
{
	OX1,
	OX2,
	END_CROSSOVERS
};

enum GeneticMutationType: unsigned short
{
	SWAPPER,
	SHUFFLER,
	END_MUTATIONS
};

enum TabuIdentificationType: unsigned short
{
	REVERSER,
	MOVER,
	END_IDENTIFICATIONS
};

enum TabuListSizes: unsigned short
{
	TWO = 2,
	THREE = 3,
	END_SIZES
};

typedef AlgorithmSummary(*AlgorithmFunction)(Point3D*, unsigned long, unsigned long long);

class TSPAlgorithmDispatcher
{
private:
	static pair<unsigned long*, unsigned long*> GA_OX1(unsigned long*, unsigned long*, unsigned long);
	static pair<unsigned long*, unsigned long*> GA_OX2(unsigned long*, unsigned long*, unsigned long);

	static void GA_Swapper(unsigned long*, unsigned long);
	static void GA_Shuffler(unsigned long*, unsigned long);

	static pair<Chromosome, Chromosome> GA_Elitism(multiset<Chromosome>&, double);
	static pair<Chromosome, Chromosome> GA_Roulette(multiset<Chromosome>&, double);

	static long GA_Fitness(const Chromosome&, double);

	static list<unsigned long*> TS_Reverse(unsigned long*, unsigned long);
	static list<unsigned long*> TS_Move(unsigned long*, unsigned long);

	static unsigned long long EncodeOption(unsigned long long, unsigned short);
	static unsigned short DecodeOption(unsigned long long, unsigned short);

	static AlgorithmSummary GeneticAlgorithm(Point3D*, unsigned long, unsigned long long);

	static AlgorithmSummary TabuSearchAlgorithm(Point3D*, unsigned long, unsigned long long);

	TSPAlgorithmDispatcher() {}
public:
	static AlgorithmFunction getAlgorithm(TSPAlgorithmType);
	static vector<unsigned long long> getAlgorithmConfigurations(TSPAlgorithmType);
};

#endif /* TSPALGORITHMDISPATCHER_H_ */
