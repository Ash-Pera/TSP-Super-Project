#pragma once
#include "Point.h"
#include <vector>

class Cycle;

class Path {
protected:
	std::vector<Point> points;
public:
	Path();
	Path(std::vector<Point>);
	void addPoint(Point);
	virtual double length() const;
	int numberOfPoints() const { return (int)points.size(); };
	Point getLastPoint() const;
	bool containsPoint(Point) const;
	void reserve(int n);


	friend std::ostream & operator << (std::ostream &out, const Path &p);
	Path operator+(const Point&);

	bool operator<(const Path& p2) { return this->length() < p2.length(); }

	friend class Cycle;
};

