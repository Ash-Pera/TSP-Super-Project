#include "Graph.h"

#include <Random>




Graph::Graph(unsigned int numberOfNodes) {
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(0, 1);

	for (unsigned int i = 0; i < numberOfNodes; i++) {
		double x = distribution(generator);
		double y = distribution(generator);
		points.insert(Point(x, y));
	}


}


Graph::Graph(std::unordered_set<Point> points) : points(points) {

}

Point Graph::getNearestPoint(Point p) const {
	return getPointsByDistance(p).front();
}



std::vector<Point> Graph::getPointsByDistance(Point p) const {
	auto sorted = std::vector<Point>();
	for (Point point : points) {
		sorted.push_back(point);
	}
	std::sort(sorted.begin(), sorted.end(), [p](const Point & a, const Point & b) {
		return p.distanceTo(a) > p.distanceTo(b);	});
	return sorted;
}



unsigned int Graph::getNumberPoints() const {
	return points.size();
}

std::ostream & operator << (std::ostream &out, const Graph &g) {
	for (Point point : g.points) {
		out << point << std::endl;
	} 
	return out;
}