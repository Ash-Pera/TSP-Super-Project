#pragma once

//#include "Node.h"
class Node;

class nodeAndDist {
public:
	Node* node;
	double dist;
	nodeAndDist(Node* node, double dist);

	bool operator==(const nodeAndDist& other) const {
		return (this->node == other.node &&
			this->dist == other.dist);
	};
};

