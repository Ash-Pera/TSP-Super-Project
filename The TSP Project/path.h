#pragma once
#include "Point.h"
#include <vector>

class Cycle;

class Path {
private:
	std::vector<Point> points;
public:
	Path();
	Path(std::vector<Point>);
	void addPoint(Point);
	virtual double distance() const;
	int numberOfPoints() const { return points.size(); };
	Point getLastPoint() const;
	bool containsPoint(Point) const;

	friend std::ostream & operator << (std::ostream &out, const Path &p);
	Path operator+(const Point&);

	friend class Cycle;
};

