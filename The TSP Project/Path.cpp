#include "path.h"



Path::Path() {
	points = std::vector<Point>();
}

Path::Path(std::vector<Point> ps): points(ps){}

void Path::addPoint(Point p) {
	points.push_back(p);
}

double Path::distance() const{
	double dist = 0;
	if (points.size() <= 1)
		return 0;
	for (unsigned int i = 0; i < points.size() - 1; i++) {
		dist += Point::euclidianDistance(points[i], points[i + 1]);
	}
	return dist;
}


Point Path::getLastPoint() const {
	return points.back();
}

bool Path::containsPoint(Point p) const {
	return std::find(points.begin(), points.end(), p) != points.end();
}

Path Path::operator+(const Point & p) {
	Path newPath = *this;
	newPath.addPoint(p);
	return newPath;
}


std::ostream & operator << (std::ostream &out, const Path &p) {
	out << "Path of length " << p.distance() << ": ";
	for (Point point : p.points) {
		out << point;
	}
	return out;
}

