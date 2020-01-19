#include "Point3D.h"
#include <cmath>
#include <cstring>
using namespace std;

Point3D Point3D::fromInput(istream& input)
{
	unsigned long id;
	double x;
	double y;
	double z;

	string buf;

	getline(input, buf, ',');
	id = strtoul(buf.c_str(), NULL, 0);

	getline(input, buf, ',');
	x = strtod(buf.c_str(), NULL);

	getline(input, buf, ',');
	y = strtod(buf.c_str(), NULL);

	getline(input, buf);
	z = strtod(buf.c_str(), NULL);

	return Point3D(id - 1, x, y, z);
}

Point3D::Point3D(unsigned long id, double x, double y, double z)
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->z = z;
}

unsigned long Point3D::getId() const
{
	return id;
}

double Point3D::getX() const
{
	return x;
}

double Point3D::getY() const
{
	return y;
}

double Point3D::getZ() const
{
	return z;
}

double Point3D::distance(const Point3D& other) const
{
	return sqrt(pow(other.getX() - getX(), 2) + pow(other.getY() - getY(), 2) + pow(other.getZ() - getZ(), 2));
}
