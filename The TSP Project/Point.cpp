#include "point.h"
#include <math.h>

Point::Point(double x, double y) : x(x), y(y) {}

double Point::distanceTo(const Point & p) const {
	return euclidianDistance(*this, p);
}

double Point::euclidianDistance(const Point & p1, const Point & p2) {
	double xDist = p1.x - p2.x;
	double yDist = p1.y - p2.y;
	return sqrt(xDist*xDist + yDist*yDist);
}

std::ostream & operator << (std::ostream &out, const Point &p) {
	out << "(" << p.x << ", " << p.y << ") ";
	return out;
}


