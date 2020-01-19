#ifndef CHROMOSOME_H_
#define CHROMOSOME_H_

#include "Point3D.h"
#include "PathSummary.h"
#include <utility>
using namespace std;

class Chromosome
{
public:
	typedef pair<unsigned long*, unsigned long*>(*CrossoverFunction)(unsigned long*, unsigned long*, unsigned long);
	typedef void(*MutationFunction)(unsigned long*, unsigned long);
private:
	Point3D* graph;
	unsigned long* nodes;
	unsigned long size;
	double distance;

	CrossoverFunction crossover;
	MutationFunction mutator;

	Chromosome(Point3D*, unsigned long*, unsigned long, CrossoverFunction, MutationFunction);

	void setupNodesRandomly();
	void calculateDistance();
public:
	Chromosome(Point3D*, unsigned long, CrossoverFunction, MutationFunction);
	Chromosome(const Chromosome&);
	Chromosome& operator=(const Chromosome&);
	~Chromosome();

	bool operator==(const Chromosome&) const;
	bool operator!=(const Chromosome&) const;
	bool operator<(const Chromosome&) const;
	bool operator<=(const Chromosome&) const;
	bool operator>(const Chromosome&) const;
	bool operator>=(const Chromosome&) const;

	PathSummary getSummary() const;
	double getDistance() const;

	void mutate();
	pair<Chromosome, Chromosome> cross(const Chromosome&) const;
};

#endif /* CHROMOSOME_H_ */
