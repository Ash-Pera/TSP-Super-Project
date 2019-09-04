#pragma once
#include "Point.h"

class QuadTree
{
	Point topLeftBound;
	Point bottomRightBound;


	QuadTree* topLeft; QuadTree* topRight;
	QuadTree* bottomLeft; QuadTree* bottomRight;

	Point* data;

public:
	QuadTree(Point topLeftBound, Point bottomRightBound);
	~QuadTree();

	void insert(Point* p);
	bool contains(const Point& p) const;
	const Point nearestPoint(const Point& p) const;

	bool containedInRegion(const Point& p) const;
};

