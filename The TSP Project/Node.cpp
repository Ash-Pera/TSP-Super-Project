#include "node.h"

#include <algorithm>
#include <functional>
#include <iterator>



Node::Node(Point p) : point(p) {
	this->nearistNeighbors = std::unordered_set<nodeAndDist>();
}

const Point * Node::getPoint() const {
	return &point;
}


bool compareNodeDist(const nodeAndDist &nd1, const nodeAndDist &nd2) {
	return nd1.dist < nd2.dist;
}

template <typename T>
T* minElement(std::unordered_set<T> set, std::function<bool(const T&,const T&)> comparator) { 
	T* minElem = *set.begin();
	for (auto elem : set) {
		if (comparator(elem, min) {
			minElem = elem;
		}
	}
	return elem;
}


const Point * Node::getNearistNeighbor() const {
	return minElement<nodeAndDist>(nearistNeighbors, compareNodeDist)->node->getPoint();
}


bool nodeDistVisted(nodeAndDist nd) {
	return nd.node->isVisited();
}

const Point * Node::getNearistUnvisitedNeighbor() const {

	nodeAndDist nearestNeighbor = *nearistNeighbors.begin();

	for (auto neighbor : nearistNeighbors) {
		if (!neighbor.node->isVisited()) {
			if (compareNodeDist(neighbor, nearestNeighbor))
				nearestNeighbor = neighbor;
		}
	}
	return nearestNeighbor.node->getPoint();

}

void Node::calcNearistNeighbors(std::unordered_set<Node*> neighbors) {
	for (Node* neighbor : neighbors) {
		
		nearistNeighbors.insert(
			nodeAndDist(neighbor,
				point.distanceTo( *neighbor->getPoint() )) );
	}
}

void Node::setVisited() {
	this->visited = true;
}

void Node::setUnvisted() {
	this->visited = false;
}

bool Node::isVisited() const {
	return visited;
}


std::ostream & operator << (std::ostream &out, const Node &n) {
	out << n.point;
	return out;
}