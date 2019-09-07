#pragma once

#include "Point.h"
#include "Cycle.h"
#include <unordered_set>
#include <vector>


#include <iostream> 
#include <sstream>
#include <fstream>

class Graph {
private:
	std::unordered_set<Point> points;
	void recursiveReduceOverAllCycles(Cycle(*reductionFunction)(const Cycle c1, const Cycle c2),
		Path startingPath, Cycle* out) const;

public:
	Graph(unsigned int);
	Graph(std::unordered_set<Point>);
	Graph(std::stringstream);

	unsigned int getNumberOfPoints() const;
	Point getNearestPoint(Point) const;
	std::vector<Point> getPointsByDistance(Point) const;

	static Point getNearestUnvisitedPoint(Point, std::unordered_set<Point>& visted);
	
	Cycle getGreedyCycle(const Point&) const;
	Cycle getGreedyCycle() const;
	Cycle reduceOverAllCycles(Cycle(*reductionFunction)(const Cycle c1, const Cycle c2)) const;

	friend std::ostream& operator << (std::ostream &out, const Graph &g);
};

