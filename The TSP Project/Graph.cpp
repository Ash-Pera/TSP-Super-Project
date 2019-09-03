#include "Graph.h"

#include <Random>
#include <set>



void Graph::recursiveReduceOverAllCycles(Cycle(*reductionFunction)(const Cycle c1, const Cycle c2),
	Path startingPath, Cycle* out) const
{
	//do reduction if cycle is compleate
	if (startingPath.numberOfPoints() == getNumberPoints()) {
		*out = reductionFunction(*out, Cycle(startingPath));
		return;
	}
	 
	// otherwise recurse
	for (Point p : getPointsByDistance(startingPath.getLastPoint())) {
		if (!startingPath.containsPoint(p)) {
			recursiveReduceOverAllCycles(reductionFunction, startingPath + p, out);
		}
	}
}


Cycle Graph::reduceOverAllCycles(Cycle(*reductionFunction)(const Cycle c1, const Cycle c2)) const
{
	Cycle bestSoFar = getGreedyCycle();

	// pick a random point to start and make a path with just that point
	Point start = getNearestPoint(Point(0.5, 0.5));
	Path startingPath = Path();

	startingPath.addPoint(start);

	recursiveReduceOverAllCycles(reductionFunction, startingPath, &bestSoFar);
	return bestSoFar;

}

Cycle Graph::getGreedyCycle() const
{
	auto visited = std::set<Point>();
	Cycle cycle;

	//pick a random point to start
	Point start = getNearestPoint(Point(0.5, 0.5));
	cycle.addPoint(start);
	visited.insert(start);

	while (visited.size() < getNumberPoints()) {
		for (Point p : getPointsByDistance(cycle.getLastPoint())) {
			if (visited.count(p) == 0) { //unvisted
				cycle.addPoint(p);
				visited.insert(p);
				break;
			}
		}
	}

	return cycle;
}



Graph::Graph(unsigned int numberOfNodes) {
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(0, 1);

	for (unsigned int i = 0; i < numberOfNodes; i++) {
		double x = distribution(generator);
		double y = distribution(generator);
		points.insert(Point(x, y));
	}


}


Graph::Graph(std::unordered_set<Point> points) : points(points) { }

// runs in n time
// there's probably a better way that runs in log n
Point Graph::getNearestPoint(Point p) const {
	return getPointsByDistance(p).front();
}


// runs in n time
std::vector<Point> Graph::getPointsByDistance(Point p) const {
	auto sorted = std::vector<Point>();
	sorted.reserve(getNumberPoints());
	for (Point point : points) {
		sorted.push_back(point);
	}
	std::sort(sorted.begin(), sorted.end(), [p](const Point & a, const Point & b) {
		return p.distanceTo(a) > p.distanceTo(b);	});
	return sorted;
}


// const time
unsigned int Graph::getNumberPoints() const {
	return (int)points.size();
}

std::ostream & operator << (std::ostream &out, const Graph &g) {
	for (Point point : g.points) {
		out << point << std::endl;
	} 
	return out;
}