#include "Graph.h"

#include <Random>



Graph::Graph(unsigned int numberOfNodes) {
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(0, 1);

	for (unsigned int i = 0; i < numberOfNodes; i++) {
		double x = distribution(generator);
		double y = distribution(generator);
		nodes.insert(Node(Point(x, y)));
	}

	calcNeighbors();

}


Graph::Graph(std::unordered_set<Node> nodes) : nodes(nodes) {
	calcNeighbors();
}

void Graph::calcNeighbors() {
	auto nodeRefs = std::unordered_set<Node*>();
	for (Node node : nodes) {
		nodeRefs.insert(&node);
	}

	for (auto node : nodes) {
		node.calcNearistNeighbors(nodeRefs);
	}
}


std::ostream & operator << (std::ostream &out, const Graph &g) {
	for (Node node : g.nodes) {
		out << node;
	} 
	return out;
}