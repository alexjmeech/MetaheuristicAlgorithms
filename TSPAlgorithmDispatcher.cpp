#include "TSPAlgorithmDispatcher.h"
#include <limits>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include <cstring>
#include "Neighborhood.h"
#include <iostream>

pair<unsigned long*, unsigned long*> TSPAlgorithmDispatcher::GA_OX1(unsigned long* male, unsigned long* female, unsigned long size)
{
	unsigned long* child1 = new unsigned long[size];
	unsigned long* child2 = new unsigned long[size];

	unsigned long point1 = rand() % (size - (size / 5) - 1);
	unsigned long point2 = point1 + (size < 5 ? 1 : (size / 5));

	bool* crossed1 = new bool[size];
	bool* crossed2 = new bool[size];

	for (unsigned long i = point1; i < point2; i++)
	{
		child1[i] = male[i];
		child2[i] = female[i];
		crossed1[male[i]] = true;
		crossed2[female[i]] = true;
	}

	for (unsigned long i = 0; i < point1; i++)
	{
		for (unsigned long j = 0; j < size; j++)
		{
			if (!crossed1[male[j]])
			{
				child1[i] = male[j];
				crossed1[male[j]] = true;
				break;
			}
		}

		for (unsigned long j = 0; j < size; j++)
		{
			if (!crossed2[female[j]])
			{
				child2[i] = female[j];
				crossed2[female[j]] = true;
				break;
			}
		}
	}

	for (unsigned long i = size - 1; i >= point2; i--)
	{
		for (unsigned long j = size - 1; j >= 0; j > 0 ? j-- : j)
		{
			if (!crossed1[male[j]])
			{
				child1[i] = male[j];
				crossed1[male[j]] = true;
				break;
			}

			if (j == 0)
			{
				break;
			}
		}

		for (unsigned long j = size - 1; j >= 0; j > 0 ? j-- : j)
		{
			if (!crossed2[female[j]])
			{
				child2[i] = female[j];
				crossed2[female[j]] = true;
				break;
			}

			if (j == 0)
			{
				break;
			}
		}
	}

	delete[] crossed1;
	delete[] crossed2;

	return make_pair(child1, child2);
}

pair<unsigned long*, unsigned long*> TSPAlgorithmDispatcher::GA_OX2(unsigned long* male, unsigned long* female, unsigned long size)
{
	unsigned long* child1 = new unsigned long[size];
	unsigned long* child2 = new unsigned long[size];

	unsigned long pos = size < 5 ? 1 : size / 5;
	unsigned long* pos1 = new unsigned long[pos];
	bool* off1 = new bool[pos];
	unsigned long* options1 = new unsigned long[size];
	unsigned long rSize1 = size;
	unsigned long* options2 = new unsigned long[size];
	unsigned long rSize2 = size;
	unsigned long cross1 = 0;
	unsigned long* pos2 = new unsigned long[pos];
	bool* off2 = new bool[pos];
	unsigned long cross2 = 0;

	for (unsigned long i = 0; i < size; i++)
	{
		options1[i] = i;
		options2[i] = i;
	}

	for (unsigned long i = 0; i < pos; i++)
	{
		{
			unsigned long j = rand() % rSize1;
			unsigned long k = options1[j];

			pos1[i] = k;

			if (rSize1 > 1)
			{
				rSize1--;
				swap(options1[j], options1[rSize1]);
			}
		}

		{
			unsigned long j = rand() % rSize2;
			unsigned long k = options2[j];

			pos2[i] = k;

			if (rSize2 > 1)
			{
				rSize2--;
				swap(options2[j], options2[rSize2]);
			}
		}
	}

	for (unsigned long i = 0; i < size; i++)
	{
		if (cross1 < pos)
		{
			bool c = false;

			for (unsigned long j = 0; j < pos; j++)
			{
				if (!off1[j] && female[i] == male[pos1[j]])
				{
					c = true;
					child1[i] = male[pos1[j]];
					off1[j] = true;
					cross1++;
					break;
				}
			}

			if (!c)
			{
				child1[i] = female[i];
			}
		}
		else
		{
			child1[i] = female[i];
		}

		if (cross2 < pos)
		{
			bool c = false;

			for (unsigned long j = 0; j < pos; j++)
			{
				if (!off2[j] && male[i] == female[pos2[j]])
				{
					c = true;
					child2[i] = female[pos1[j]];
					off2[j] = true;
					cross2++;
					break;
				}
			}

			if (!c)
			{
				child2[i] = male[i];
			}
		}
		else
		{
			child2[i] = male[i];
		}
	}

	delete[] pos1;
	delete[] pos2;
	delete[] off1;
	delete[] off2;
	delete[] options1;
	delete[] options2;

	return make_pair(child1, child2);
}

void TSPAlgorithmDispatcher::GA_Shuffler(unsigned long* nodes, unsigned long size)
{
	unsigned long j;
	unsigned long k;

	do
	{
		j = rand() % size;
		k = rand() % size;
	}
	while (j == k);

	if (j > k)
	{
		swap(j, k);
	}

	for (unsigned long i = (k - j - 1); i > 0; i--)
	{
		swap(nodes[j + i], nodes[j + (rand() % (i + 1))]);
	}
}

void TSPAlgorithmDispatcher::GA_Swapper(unsigned long* nodes, unsigned long size)
{
	unsigned long j;
	unsigned long k;

	do
	{
		j = rand() % size;
		k = rand() % size;
	}
	while (j == k);

	swap(nodes[j], nodes[k]);
}

pair<Chromosome, Chromosome> TSPAlgorithmDispatcher::GA_Elitism(multiset<Chromosome>& chromosomes, double accumulatedDistance)
{
	return make_pair(*(chromosomes.begin()), *(++(chromosomes.begin())));
}

pair<Chromosome, Chromosome> TSPAlgorithmDispatcher::GA_Roulette(multiset<Chromosome>& chromosomes, double accumulatedDistance)
{
	const Chromosome* c1 = nullptr;
	const Chromosome* c2 = nullptr;

	long target = (long) accumulatedDistance;
	long start = rand() % target;

	for (const Chromosome& chromosome : chromosomes)
	{
		if (c1 != nullptr)
		{
			break;
		}

		start += GA_Fitness(chromosome, accumulatedDistance);

		if (start > target)
		{
			c1 = &chromosome;
		}
	}

	for (const Chromosome& chromosome : chromosomes)
	{
		if (c2 != nullptr)
		{
			break;
		}

		start += GA_Fitness(chromosome, accumulatedDistance);

		if (&chromosome != c1 && start > target)
		{
			c2 = &chromosome;
		}
	}

	return make_pair(*c1, *c2);
}

long TSPAlgorithmDispatcher::GA_Fitness(const Chromosome& chromosome, double accumulatedDistance)
{
	return (long)(accumulatedDistance - chromosome.getDistance());
}

list<unsigned long*> TSPAlgorithmDispatcher::TS_Reverse(unsigned long* nodes, unsigned long size)
{
	list<unsigned long*> neighbors;

	for (unsigned long i = 0; i < (size < 5 ? 3 : size / 4); i++)
	{
		unsigned long* neighbor = new unsigned long[size];
		memcpy(neighbor, nodes, sizeof(unsigned long) * size);
		unsigned long j;
		unsigned long k;

		do
		{
			j = rand() % size;
			k = rand() % size;
		}
		while (j == k);

		swap(neighbor[j], neighbor[k]);

		neighbors.push_back(neighbor);
	}

	return neighbors;
}

list<unsigned long*> TSPAlgorithmDispatcher::TS_Move(unsigned long* nodes, unsigned long size)
{
	list<unsigned long*> neighbors;

	for (unsigned long i = 0; i < (size < 5 ? 3 : size / 4); i++)
	{
		unsigned long* neighbor = new unsigned long[size];
		memcpy(neighbor, nodes, sizeof(unsigned long) * size);
		unsigned long j;
		unsigned long k;
		unsigned long l;

		do
		{
			j = rand() % size;
			k = rand() % size;
			l = rand() % size;
		}
		while (j == k && j != l && l != k);

		swap(neighbor[j], neighbor[k]);
		swap(neighbor[j], neighbor[l]);

		neighbors.push_back(neighbor);
	}

	return neighbors;
}

unsigned long long TSPAlgorithmDispatcher::EncodeOption(unsigned long long current, unsigned short option)
{
	return (current << 16) | option;
}

unsigned short TSPAlgorithmDispatcher::DecodeOption(unsigned long long options, unsigned short offset)
{
	unsigned long long mask = 0xFFFF;
	return (options >> (offset * 16)) & mask;
}

AlgorithmSummary TSPAlgorithmDispatcher::GeneticAlgorithm(Point3D* graph, unsigned long size, unsigned long long options)
{
	unsigned short selectionType = DecodeOption(options, 2);
	pair<Chromosome, Chromosome>(*selectionFunc)(multiset<Chromosome>&, double) = nullptr;

	switch (selectionType)
	{
	case ELITISM:
		selectionFunc = &(TSPAlgorithmDispatcher::GA_Elitism);
		break;
	case ROULETTE:
		selectionFunc = &(TSPAlgorithmDispatcher::GA_Roulette);
		break;
	default:
		break;
	}

	unsigned short crossoverType = DecodeOption(options, 1);
	Chromosome::CrossoverFunction crossoverFunc = nullptr;

	switch (crossoverType)
	{
	case OX1:
		crossoverFunc = &(TSPAlgorithmDispatcher::GA_OX1);
		break;
	case OX2:
		crossoverFunc = &(TSPAlgorithmDispatcher::GA_OX2);
		break;
	default:
		break;
	}

	unsigned short mutationType = DecodeOption(options, 0);
	Chromosome::MutationFunction mutationFunc = nullptr;

	switch (mutationType)
	{
	case SWAPPER:
		mutationFunc = &(TSPAlgorithmDispatcher::GA_Swapper);
		break;
	case SHUFFLER:
		mutationFunc = &(TSPAlgorithmDispatcher::GA_Shuffler);
		break;
	default:
		break;
	}

	AlgorithmSummary summary("Genetic Algorithm");
	summary.addConfiguration("Selection Type", selectionType);
	summary.addConfiguration("Crossover Type", crossoverType);
	summary.addConfiguration("Mutation Type", mutationType);

	multiset<Chromosome> population;
	double accumulated = 0;

	for (unsigned long i = 0; i < (size < 6 ? size * 2 : 12); i++)
	{
		Chromosome c = Chromosome(graph, size, crossoverFunc, mutationFunc);
		population.insert(c);
		accumulated += c.getDistance();
	}

	summary.addSnapshot(0, population.begin()->getDistance());

	auto start = std::chrono::high_resolution_clock::now();

	int steps = 0;

	while (true)
	{
		auto cur = std::chrono::high_resolution_clock::now();

		long long epoch = (cur - start).count();

		pair<Chromosome, Chromosome> mates = (*selectionFunc)(population, accumulated);
		pair<Chromosome, Chromosome> children = mates.first.cross(mates.second);

		if (rand() % 101 == 1)
		{
			children.first.mutate();
			children.second.mutate();
		}

		accumulated += children.first.getDistance();
		accumulated += children.second.getDistance();
		population.insert(children.first);
		population.insert(children.second);

		multiset<Chromosome>::iterator r1 = prev(population.end());
		Chromosome c1 = *r1;
		multiset<Chromosome>::iterator r2 = prev(r1);
		Chromosome c2 = *r2;

		accumulated -= c1.getDistance();
		accumulated -= c2.getDistance();
		population.erase(r1);
		population.erase(r2);

		summary.addSnapshot(epoch, population.begin()->getDistance());

		if (epoch >= 600000000000)
		{
			break;
		}
	}

	summary.setBestPath(population.begin()->getSummary());

	return summary;
}

AlgorithmSummary TSPAlgorithmDispatcher::TabuSearchAlgorithm(Point3D* graph, unsigned long size, unsigned long long options)
{
	unsigned short identificationType = DecodeOption(options, 1);
	list<unsigned long*>(*identificationFunc)(unsigned long*, unsigned long) = nullptr;

	switch (identificationType)
	{
	case REVERSER:
		identificationFunc = &(TSPAlgorithmDispatcher::TS_Reverse);
		break;
	case MOVER:
		identificationFunc = &(TSPAlgorithmDispatcher::TS_Move);
		break;
	default:
		break;
	}

	unsigned short bufferSize = DecodeOption(options, 0);
	RingBuffer<Neighborhood> buffer(size / bufferSize);

	AlgorithmSummary summary("Tabu Search Algorithm");
	summary.addConfiguration("Neighborhood Identification Type", identificationType);
	summary.addConfiguration("Tabu List Size Dividend", bufferSize);

	Neighborhood best(graph, size);
	Neighborhood current = best;
	buffer.push_back(current);

	summary.addSnapshot(0, best.getDistance());

	auto start = std::chrono::high_resolution_clock::now();

	while (true)
	{
		auto cur = std::chrono::high_resolution_clock::now();

		long long epoch = (cur - start).count();

		current = *(current.getMovementOptions(buffer, identificationFunc).begin());
		buffer.push_back(current);

		if (current < best)
		{
			best = current;
		}

		summary.addSnapshot(epoch, best.getDistance());

		if (epoch >= 600000000000)
		{
			break;
		}
	}

	summary.setBestPath(best.getSummary());

	return summary;
}

AlgorithmFunction TSPAlgorithmDispatcher::getAlgorithm(TSPAlgorithmType type)
{
	switch (type)
	{
	case GENETIC:
		return &(TSPAlgorithmDispatcher::GeneticAlgorithm);
	case TABU_SEARCH:
		return &(TSPAlgorithmDispatcher::TabuSearchAlgorithm);
	default:
		return nullptr;
	}
}

vector<unsigned long long> TSPAlgorithmDispatcher::getAlgorithmConfigurations(TSPAlgorithmType type)
{
	vector<unsigned long long> options;

	switch (type)
	{
	case GENETIC:
		for (unsigned short i = 0; i < GeneticSelectionType::END_SELECTIONS; i++)
		{
			for (unsigned short j = 0; j < GeneticCrossoverType::END_CROSSOVERS; j++)
			{
				for (unsigned short k = 0; k < GeneticMutationType::END_MUTATIONS; k++)
				{
					options.push_back(EncodeOption(EncodeOption(EncodeOption(0, i), j), k));
				}
			}
		}

		break;
	case TABU_SEARCH:
		for (unsigned short i = 0; i < TabuIdentificationType::END_IDENTIFICATIONS; i++)
		{
			for (unsigned short j = TabuListSizes::TWO; j < TabuListSizes::END_SIZES; j++)
			{
				options.push_back(EncodeOption(EncodeOption(0, i), j));
			}
		}

		break;
	default:
		break;
	}

	return options;
}
