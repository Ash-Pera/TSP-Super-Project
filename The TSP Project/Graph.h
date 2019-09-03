#pragma once

#include "Point.h"
#include "Cycle.h"
#include <unordered_set>
#include <vector>


#include <iostream> 

class Graph {
private:
	std::unordered_set<Point> points;
	void recursiveReduceOverAllCycles(Cycle(*reductionFunction)(const Cycle c1, const Cycle c2),
		Path startingPath, Cycle* out);

public:
	Graph(unsigned int);
	Graph(std::unordered_set<Point>);

	Point getNearestPoint(Point p) const;
	unsigned int getNumberPoints() const;
	std::vector<Point> getPointsByDistance(Point p) const;

	Cycle reduceOverAllCycles(Cycle(*reductionFunction)(const Cycle c1, const Cycle c2));
	Cycle getGreedyCycle();

	//std::unordered_set<Point> getPoints() const;

	friend std::ostream & operator << (std::ostream &out, const Graph &g);
};

