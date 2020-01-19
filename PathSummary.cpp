#include "PathSummary.h"

PathSummary::PathSummary()
{
	distance = 0;
}

const list<unsigned long>& PathSummary::getPath() const
{
	return path;
}

double PathSummary::getPathDistance() const
{
	return distance;
}

void PathSummary::addStep(unsigned long node, double stepDistance)
{
	path.push_back(node);
	distance += stepDistance;
}
