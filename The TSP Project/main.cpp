#include "Graph.h"
#include "Cycle.h"
#include <set>
#include <chrono> 

// n^2 or n^3 time
Cycle greedySearch(Graph g) {
	auto visited = std::set<Point>();
	Cycle cycle;

	//pick a random point to start
	Point start = g.getNearestPoint(Point(0.5, 0.5));
	cycle.addPoint(start);
	visited.insert(start);

	// n time
	while (visited.size() < g.getNumberPoints()) {
		// n time
						// n time
		for (Point p : g.getPointsByDistance(cycle.getLastPoint())) {
				// log n
			if (visited.count(p) == 0) { //unvisted
			//if (!visited.contains(p)) { c++20
				// am const time
				cycle.addPoint(p);
				// avg const time
				visited.insert(p);
				break;
			}
		}
	}

	return cycle;
}


void recursiveEnumerateAllCycles(Path startingPath, Graph& graph, std::vector<Cycle>& out) {
	if (startingPath.numberOfPoints() == graph.getNumberPoints()) {
		out.push_back(Cycle(startingPath));
		return;
	}

	for (Point p : graph.getPointsByDistance(startingPath.getLastPoint())) {
		if (!startingPath.containsPoint(p)) {
			//might have to fix +
			recursiveEnumerateAllCycles(startingPath + p, graph, out);
		}
	}
}

std::vector<Cycle> enumerateAllCycles(Graph graph) {
	auto out = std::vector<Cycle>();
	//pick random starting point
	Point start = graph.getNearestPoint(Point(0.5, 0.5));
	Path startingPath = Path();
	startingPath.addPoint(start);

	recursiveEnumerateAllCycles(startingPath, graph, out);
	return out;
}


Cycle exaustiveSearch(Graph graph) {
	std::vector<Cycle>  allCycles = enumerateAllCycles(graph);

	Cycle minCycle = allCycles.front();
	for (Cycle cycle : allCycles) {
		if (cycle.distance() < minCycle.distance()) {
			minCycle = cycle;
		}
	}
	return minCycle;
}

using namespace std::chrono;
void timeExaustiveSearch(int sizeOfGraph, int numberOfTimes) {
	for (int i = 0; i < numberOfTimes; i++) {
		Graph graph = Graph(sizeOfGraph);

		auto start = high_resolution_clock::now();
		Cycle exaustive = exaustiveSearch(graph);
		auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);

		std::cout << sizeOfGraph << ", " << duration.count() << std::endl;
	}
}

void timeGreedySearch(int sizeOfGraph, int numberOfTimes) {
	for (int i = 0; i < numberOfTimes; i++) {
		Graph graph = Graph(sizeOfGraph);

		auto start = high_resolution_clock::now();
		Cycle greedy = greedySearch(graph);
		auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);

		std::cout << sizeOfGraph << ", " << duration.count() << std::endl;
	}
}



int main(int argc, char *argv[]) { 
	//std::cout.imbue(std::locale(""));

	//for (int i = 1; i < 1000; i+=10) {
		timeGreedySearch(10, 10);
	//}
	//timeExaustiveSearch(12, 10);


	std::cin.get();

}