#include "Cycle.h"



Cycle::Cycle() {}

Cycle::Cycle(Path p) { this->points = p.points; };

double Cycle::length() const{
	if (numberOfPoints() <= 1)
		return 0;
	return Path::length() +
		Point::euclidianDistance(points.back(), points.front());
}

