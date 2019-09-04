#include "QuadTree.h"

QuadTree::QuadTree(Point topLeftBound, Point bottomRightBound) :
	topLeftBound(topLeftBound), bottomRightBound(bottomRightBound)
{
	topLeft = NULL;
	topRight = NULL;
	bottomLeft = NULL;
	bottomRight = NULL;
	data = NULL;
}

void QuadTree::insert(Point* p)
{
	// nothing in region
	if (data == NULL) {
		data = p;
	}
	else {
		
	}
}

bool QuadTree::containedInRegion(const Point& p) const
{
	return p.x >= topLeftBound.x && p.y <= topLeftBound.y &&
		p.x <= bottomRightBound.x && p.y >= bottomRightBound.y;
}
