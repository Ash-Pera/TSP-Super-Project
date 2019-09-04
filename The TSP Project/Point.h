#pragma once
#include <iostream>

struct Point {
public:
	double x, y;
	Point() : x(0), y(0) {};
	Point(double x, double y);
	double distanceTo(const Point& p) const;

	static double euclidianDistance(const Point& p1, const Point& p2);

	friend std::ostream & operator << (std::ostream &out, const Point &p);

	bool operator==(const Point& otherpoint) const {
		return (this->x == otherpoint.x && 
			this->y == otherpoint.y);
	}

	friend bool operator <(const Point& lhs, const Point& rhs){
		return lhs.x < rhs.x;
	}
};

namespace std {
	template<> struct hash<Point> {
		typedef Point argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& s) const noexcept {
			result_type const h1(std::hash<double>{}(s.x));
			result_type const h2(std::hash<double>{}(s.y));
			return h1 ^ (h2 << 1);
		}
	};
}