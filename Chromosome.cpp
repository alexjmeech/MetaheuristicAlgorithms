#include "Chromosome.h"
#include <stdlib.h>
#include <algorithm>
#include <utility>
using namespace std;

Chromosome::Chromosome(Point3D* baseGraph, unsigned long* offspringNodes, unsigned long baseSize, CrossoverFunction crossFunction, MutationFunction mutateFunction)
{
	graph = baseGraph;
	size = baseSize;
	nodes = offspringNodes;
	crossover = crossFunction;
	mutator = mutateFunction;
	calculateDistance();
}

void Chromosome::setupNodesRandomly()
{
	unsigned long* options = new unsigned long[size];
	unsigned long rSize = size;

	for (unsigned long i = 0; i < size; i++)
	{
		options[i] = i;
	}

	for (unsigned long i = 0; i < size; i++)
	{
		unsigned long j = rand() % rSize;
		unsigned long k = options[j];

		nodes[i] = k;

		if (rSize == 1)
		{
			break;
		}

		rSize--;
		swap(options[j], options[rSize]);
	}

	delete[] options;
}

void Chromosome::calculateDistance()
{
	distance = 0;

	for (unsigned long i = 1; i < size; i++)
	{
		distance += graph[i].distance(graph[i - 1]);
	}

	distance += graph[0].distance(graph[size - 1]);
}

Chromosome::Chromosome(Point3D* baseGraph, unsigned long baseSize, CrossoverFunction crossFunction, MutationFunction mutateFunction)
{
	graph = baseGraph;
	size = baseSize;
	nodes = new unsigned long[size];
	crossover = crossFunction;
	mutator = mutateFunction;
	setupNodesRandomly();
	calculateDistance();
}

Chromosome::Chromosome(const Chromosome& copy)
{
	graph = copy.graph;
	size = copy.size;
	nodes = new unsigned long[size];

	for (unsigned long i = 0; i < size; i++)
	{
		nodes[i] = copy.nodes[i];
	}

	distance = copy.distance;

	crossover = copy.crossover;
	mutator = copy.mutator;
}

Chromosome& Chromosome::operator=(const Chromosome& copy)
{
	if (this != &copy)
	{
		if (nodes != nullptr)
		{
			delete[] nodes;
		}

		graph = copy.graph;
		size = copy.size;
		nodes = new unsigned long[size];

		for (unsigned long i = 0; i < size; i++)
		{
			nodes[i] = copy.nodes[i];
		}

		distance = copy.distance;

		crossover = copy.crossover;
		mutator = copy.mutator;
	}

	return *this;
}

Chromosome::~Chromosome()
{
	if (nodes != nullptr)
	{
		delete[] nodes;
	}

	nodes = nullptr;
	graph = nullptr;
	size = 0;
	distance = 0;
}

bool Chromosome::operator==(const Chromosome& compare) const
{
	if (size != compare.size)
	{
		return false;
	}

	if (distance != compare.distance)
	{
		return false;
	}

	if (graph != compare.graph)
	{
		return false;
	}

	for (unsigned long i = 0; i < size; i++)
	{
		if (nodes[i] != compare.nodes[i])
		{
			return false;
		}
	}

	return true;
}

bool Chromosome::operator!=(const Chromosome& compare) const
{
	return !(*this == compare);
}

bool Chromosome::operator<(const Chromosome& compare) const
{
	if (size != compare.size)
	{
		return false;
	}

	if (graph != compare.graph)
	{
		return false;
	}

	return distance < compare.distance;
}

bool Chromosome::operator<=(const Chromosome& compare) const
{
	return (*this < compare) || (*this == compare);
}

bool Chromosome::operator>(const Chromosome& compare) const
{
	return !(*this < compare);
}

bool Chromosome::operator>=(const Chromosome& compare) const
{
	return (*this > compare) || (*this == compare);
}

PathSummary Chromosome::getSummary() const
{
	PathSummary s;

	s.addStep(nodes[0], 0);

	for (unsigned long i = 1; i < size; i++)
	{
		s.addStep(nodes[i], graph[i].distance(graph[i - 1]));
	}

	s.addStep(nodes[0], graph[0].distance(graph[size - 1]));

	return s;
}

double Chromosome::getDistance() const
{
	return distance;
}

void Chromosome::mutate()
{
	(*mutator)(nodes, size);
	calculateDistance();
}

pair<Chromosome, Chromosome> Chromosome::cross(const Chromosome& mate) const
{
	pair<unsigned long*, unsigned long*> childData = (*crossover)(nodes, mate.nodes, size);

	return make_pair(Chromosome(graph, childData.first, size, crossover, mutator), Chromosome(graph, childData.second, size, crossover, mutator));
}
