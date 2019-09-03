#include "path.h"



Path::Path() {
	points = std::vector<Point>();
}

Path::Path(std::vector<Point> ps): points(ps){}

// amortized const time
void Path::addPoint(Point p) {
	points.push_back(p);
}

// n time
double Path::length() const{
	if (points.size() <= 1) {
		return 0;
	}

	double dist = 0;
	for (unsigned int i = 0; i < points.size() - 1; i++) {
		dist += Point::euclidianDistance(points[i], points[i + 1]);
	}

	return dist;
}

// const time
Point Path::getLastPoint() const {
	return points.back();
}

// n time
bool Path::containsPoint(Point p) const {
	return std::find(points.begin(), points.end(), p) != points.end();
}

// amortized const time
Path Path::operator+(const Point & p) {
	Path newPath = *this;
	newPath.addPoint(p);
	return newPath;
}


std::ostream & operator << (std::ostream &out, const Path &p) {
	out << "Path of length " << p.length() << ": ";
	for (Point point : p.points) {
		out << point;
	}
	return out;
}

