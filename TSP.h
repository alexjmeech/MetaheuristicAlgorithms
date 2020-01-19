#ifndef TSP_H_
#define TSP_H_

#include "Algorithm.h"
#include "Point3D.h"
#include "AlgorithmSummary.h"
#include <ostream>

class TSP : public Algorithm
{
private:
	Point3D* graph;
	unsigned long size;

	AlgorithmSummary summary;

	AlgorithmSummary(*algorithm)(Point3D*, unsigned long, unsigned long long);
	unsigned long long algorithmConfig = 0;

	virtual void OutputSummary(ostream&, AlgorithmSummary&, bool);
public:
	virtual void Load(string);
	virtual void Execute();
	virtual void Display();
	virtual void Stats();
	virtual void Select(int);
	virtual void Save();
	virtual void Configure(unsigned long long);

	virtual ~TSP();
};

#endif /* TSP_H_ */
