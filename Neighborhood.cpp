#include "Neighborhood.h"
#include <stdlib.h>
#include <algorithm>
#include <utility>
using namespace std;

Neighborhood::Neighborhood(Point3D* baseGraph, unsigned long* offspringNodes, unsigned long baseSize)
{
	graph = baseGraph;
	size = baseSize;
	nodes = offspringNodes;
	calculateDistance();
}

void Neighborhood::setupNodesRandomly()
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

void Neighborhood::calculateDistance()
{
	distance = 0;

	for (unsigned long i = 1; i < size; i++)
	{
		distance += graph[i].distance(graph[i - 1]);
	}

	distance += graph[0].distance(graph[size - 1]);
}

Neighborhood::Neighborhood()
{
	graph = nullptr;
	size = 0;
	nodes = nullptr;
	distance = 0;
}

Neighborhood::Neighborhood(Point3D* baseGraph, unsigned long baseSize)
{
	graph = baseGraph;
	size = baseSize;
	nodes = new unsigned long[size];
	setupNodesRandomly();
	calculateDistance();
}

Neighborhood::Neighborhood(const Neighborhood& copy)
{
	graph = copy.graph;
	size = copy.size;

	if (copy.nodes != nullptr)
	{
		nodes = new unsigned long[size];

		for (unsigned long i = 0; i < size; i++)
		{
			nodes[i] = copy.nodes[i];
		}
	}
	else
	{
		nodes = nullptr;
	}

	distance = copy.distance;
}

Neighborhood& Neighborhood::operator=(const Neighborhood& copy)
{
	if (this != &copy)
	{
		if (nodes != nullptr)
		{
			delete[] nodes;
		}

		graph = copy.graph;
		size = copy.size;

		if (copy.nodes != nullptr)
		{
			nodes = new unsigned long[size];

			for (unsigned long i = 0; i < size; i++)
			{
				nodes[i] = copy.nodes[i];
			}
		}
		else
		{
			nodes = nullptr;
		}

		distance = copy.distance;
	}

	return *this;
}

Neighborhood::~Neighborhood()
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

bool Neighborhood::operator==(const Neighborhood& compare) const
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

bool Neighborhood::operator!=(const Neighborhood& compare) const
{
	return !(*this == compare);
}

bool Neighborhood::operator<(const Neighborhood& compare) const
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

bool Neighborhood::operator<=(const Neighborhood& compare) const
{
	return (*this < compare) || (*this == compare);
}

bool Neighborhood::operator>(const Neighborhood& compare) const
{
	return !(*this < compare);
}

bool Neighborhood::operator>=(const Neighborhood& compare) const
{
	return (*this > compare) || (*this == compare);
}

PathSummary Neighborhood::getSummary() const
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

double Neighborhood::getDistance() const
{
	return distance;
}

set<Neighborhood> Neighborhood::getMovementOptions(const RingBuffer<Neighborhood>& tabu, MovementFunction movement) const
{
	set<Neighborhood> neighbors;
	list<unsigned long*> neighborData = (*movement)(nodes, size);

	for (unsigned long* data : neighborData)
	{
		Neighborhood n(graph, data, size);

		if (find(tabu.getBacking().begin(), tabu.getBacking().end(), n) == tabu.getBacking().end())
		{
			neighbors.insert(n);
		}
	}

	return neighbors;
}
