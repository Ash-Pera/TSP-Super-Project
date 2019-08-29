#pragma once

#include "Node.h"
#include <unordered_set>

#include <iostream> 

class Graph {
private:
	std::unordered_set<Node> nodes;

	void calcNeighbors();
public:
	Graph(unsigned int);
	Graph(std::unordered_set<Node>);

	friend std::ostream & operator << (std::ostream &out, const Graph &g);
};

