#ifndef POINT3D_H_
#define POINT3D_H_

#include <istream>
using namespace std;

class Point3D
{
private:
	unsigned long id;
	double x;
	double y;
	double z;
public:
	static Point3D fromInput(istream&);

	Point3D(unsigned long id = 0, double = 0, double = 0, double = 0);

	unsigned long getId() const;
	double getX() const;
	double getY() const;
	double getZ() const;

	double distance(const Point3D&) const;
};

#endif /* POINT3D_H_ */
