#ifndef NEIGHBORHOOD_H_
#define NEIGHBORHOOD_H_

#include "Point3D.h"
#include "PathSummary.h"
#include <set>
#include "RingBuffer.h"
using namespace std;

class Neighborhood
{
public:
	typedef list<unsigned long*>(*MovementFunction)(unsigned long*, unsigned long);
private:
	Point3D* graph;
	unsigned long* nodes;
	unsigned long size;
	double distance;

	Neighborhood(Point3D*, unsigned long*, unsigned long);

	void setupNodesRandomly();
	void calculateDistance();
public:
	Neighborhood();
	Neighborhood(Point3D*, unsigned long);
	Neighborhood(const Neighborhood&);
	Neighborhood& operator=(const Neighborhood&);
	~Neighborhood();

	bool operator==(const Neighborhood&) const;
	bool operator!=(const Neighborhood&) const;
	bool operator<(const Neighborhood&) const;
	bool operator<=(const Neighborhood&) const;
	bool operator>(const Neighborhood&) const;
	bool operator>=(const Neighborhood&) const;

	PathSummary getSummary() const;
	double getDistance() const;

	set<Neighborhood> getMovementOptions(const RingBuffer<Neighborhood>&, MovementFunction) const;
};

#endif /* NEIGHBORHOOD_H_ */
