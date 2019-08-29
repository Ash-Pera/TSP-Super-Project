#pragma once
#include "Point.h"
#include <vector>
#include <set>
#include <functional>

#include <unordered_set>

#include "nodeAndDist.h"

class Node {
private:
	const Point point;
	bool visited;
	std::unordered_set<nodeAndDist> nearistNeighbors;

public:
	Node(Point p);
	/*Node(double x, double y);*/

	const Point * getPoint() const;
	const Point * getNearistNeighbor() const;
	const Point * getNearistUnvisitedNeighbor() const;

	void calcNearistNeighbors(std::unordered_set<Node*>);

	void setVisited();
	void setUnvisted();

	bool isVisited() const;

	friend std::ostream & operator << (std::ostream &out, const Node &c);

	bool operator==(const Node& othernode) const {
		return (this->point == othernode.point);
	}
};

namespace std {
	template<> struct hash<Node> {
		typedef Node argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& s) const noexcept {

			return std::hash<Point>(*s.getPoint());
		}
	};
}
