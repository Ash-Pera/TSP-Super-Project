#include "Graph.h"
#include "Cycle.h"
#include <set>
#include <chrono> 



Cycle shorterCycle(const Cycle c1, const Cycle c2) {
	if (c1.length() < c2.length()) {
		return c1;
	}
	else {
		return c2;
	}
}

Cycle exaustiveSearch(Graph g) {
	return g.reduceOverAllCycles(shorterCycle);
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



int main(int argc, char *argv[]) { 
	std::cout.imbue(std::locale(""));
	Graph g = Graph(10);
	std::cout << g.getGreedyCycle() << std::endl;
	std::cin.get();

}