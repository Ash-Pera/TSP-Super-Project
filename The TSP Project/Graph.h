#pragma once

#include "Point.h"
#include <unordered_set>
#include <vector>

#include <iostream> 

class Graph {
private:
	std::unordered_set<Point> points;

public:
	Graph(unsigned int);
	Graph(std::unordered_set<Point>);

	Point getNearestPoint(Point p) const;
	unsigned int getNumberPoints() const;
	std::vector<Point> getPointsByDistance(Point p) const;

	//std::unordered_set<Point> getPoints() const;

	friend std::ostream & operator << (std::ostream &out, const Graph &g);
};

