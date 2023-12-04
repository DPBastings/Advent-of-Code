#include "Point.hpp"

Point::Point(long x, long y):
	_x(x), _y(y) {
	if (_x < 0 || _y < 0)
		throw (std::out_of_range("no negative coordinates"));
}

long
Point::x() const {
	return (_x);
}

long
Point::y() const {
	return (_y);
}
