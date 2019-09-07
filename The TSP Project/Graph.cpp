#include "Graph.h"

#include <Random>
#include <set>




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

Graph::Graph(std::stringstream input) {
	while (!input.eof()) {
		int x_chord, y_chord;
		input >> x_chord;
		input >> y_chord;
		this->points.insert(Point(x_chord, y_chord));
	}
}



// runs in n log n time
std::vector<Point> Graph::getPointsByDistance(Point p) const {
	auto sorted = std::vector<Point>();
	sorted.reserve(getNumberOfPoints());
	for (Point point : points) {
		sorted.push_back(point);
	}
	std::sort(sorted.begin(), sorted.end(), [p](const Point& a, const Point& b) {
		return p.distanceTo(a) < p.distanceTo(b);	});
	return sorted;
}


//runs in n, returns null if all points visited
Point Graph::getNearestUnvisitedPoint( Point searchPoint, std::unordered_set<Point>& unvisted)
{
	Point bestSoFar = *unvisted.begin();
	for (Point p : unvisted) {
			if (searchPoint.distanceTo(p) < searchPoint.distanceTo(bestSoFar)) {
				bestSoFar = p;
			}
	}
	return bestSoFar;
}


// const time
unsigned int Graph::getNumberOfPoints() const {
	return (int) points.size();
}



void Graph::recursiveReduceOverAllCycles(Cycle(*reductionFunction)(const Cycle c1, const Cycle c2),
	Path startingPath, Cycle* out) const {
	//do reduction if cycle is compleate
	if (startingPath.numberOfPoints() == getNumberOfPoints()) {
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


Cycle Graph::reduceOverAllCycles(Cycle(*reductionFunction)(const Cycle c1, const Cycle c2)) const {
	Cycle bestSoFar = getGreedyCycle();

	// pick a random point to start and make a path with just that point
	Point start = getNearestPoint(Point(0.5, 0.5));
	Path startingPath = Path();

	startingPath.addPoint(start);

	recursiveReduceOverAllCycles(reductionFunction, startingPath, &bestSoFar);
	return bestSoFar;

}

Cycle Graph::getGreedyCycle(const Point& start) const {
	Cycle cycle;
	cycle.reserve(getNumberOfPoints());
	cycle.addPoint(start);
	auto unvisited = std::unordered_set<Point>(this->points);
	unvisited.erase(start);

	while (cycle.numberOfPoints() < getNumberOfPoints()) {
		Point lastPoint = cycle.getLastPoint();
		unvisited.erase(lastPoint);
		cycle.addPoint(getNearestUnvisitedPoint(lastPoint, unvisited));
	}
	return cycle;
}

Cycle Graph::getGreedyCycle() const {
	//pick a random point to start
	Point start = getNearestPoint(Point(0.5, 0.5));
	return getGreedyCycle(start);
}



// runs in n time
// there's probably a better way that runs in log n
Point Graph::getNearestPoint(Point p) const {
	return getPointsByDistance(p).front();
}


std::ostream & operator << (std::ostream &out, const Graph &g) {
	for (Point point : g.points) {
		out << point << std::endl;
	} 
	return out;
}