#include "Graph.h"
#include "Cycle.h"
#include <unordered_set>


// CALCULTATING CYCLE LENGTH INCORRECLYT

Cycle greedyCycle(Graph g) {
	auto visited = std::unordered_set<Point>();
	Cycle cycle;

	//pick a random point to start
	Point start = g.getNearestPoint(Point(0.5, 0.5));
	cycle.addPoint(start);
	visited.insert(start);

	while (visited.size() < g.getNumberPoints()) {
		for (Point p : g.getPointsByDistance(cycle.getLastPoint())) {
			if (visited.count(p) == 0) {//unvisited
				cycle.addPoint(p);
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


Cycle exaustiveCycle(Graph graph) {
	std::vector<Cycle>  allCycles = enumerateAllCycles(graph);

	Cycle minCycle = allCycles.front();
	for (Cycle cycle : allCycles) {
		if (cycle.distance() < minCycle.distance()) {
			minCycle = cycle;
		}
	}
	return minCycle;
}




int main(int argc, char *argv[]) { 
	Graph graph = Graph(8);

	Cycle greedy = greedyCycle(graph);
	std::cout << greedy << std::endl;

	Cycle best = exaustiveCycle(graph);
	std::cout << best;

	std::cin.get();

}