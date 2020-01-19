#ifndef PATHSUMMARY_H_
#define PATHSUMMARY_H_

#include <list>
using namespace std;

class PathSummary
{
private:
	list<unsigned long> path;
	double distance;
public:
	PathSummary();

	const list<unsigned long>& getPath() const;

	double getPathDistance() const;

	void addStep(unsigned long, double = 0);
};

#endif /* PATHSUMMARY_H_ */
