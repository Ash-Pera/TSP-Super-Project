#include "Graph.h"
#include "Cycle.h"
#include <set>
#include <chrono> 


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
		Cycle greedy = graph.getGreedyCycle();
		auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);

		std::cout << sizeOfGraph << ", " << duration.count() << std::endl;
	}
}


Cycle shorterCycle(const Cycle c1, const Cycle c2) {
	if (c1.length() < c2.length()) {
		return c1;
	}
	else {
		return c2;
	}
}


int main(int argc, char *argv[]) { 
	//std::cout.imbue(std::locale(""));

	Graph graph = Graph(6);

	Cycle oldBest = exaustiveSearch(graph);

	Cycle newBest = graph.reduceOverAllCycles(shorterCycle);
	std::cout << "old "<<oldBest << std::endl << std::endl;
	
	std::cout << newBest;

	std::cin.get();

}