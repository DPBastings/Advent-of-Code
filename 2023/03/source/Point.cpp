#include "Point.hpp"

#include <stdexcept>

// Constructors

Point::Point(long x, long y):
	_x(x), _y(y) {
	if (_x < 0 || _y < 0)
		throw (std::out_of_range("no negative coordinates"));
}

// Operators

bool
Point::operator==(Point const& that) const {
	return (_x == that._x && _y == that._y);
}

bool
Point::operator!=(Point const& that) const {
	return (_x != that._x || _y != that._y);
}

Point::operator std::string() const {
	return ("[" + std::to_string(_x) + ", " + std::to_string(_y) + "]");
}

// Public methods

long
Point::x() const {
	return (_x);
}

long
Point::y() const {
	return (_y);
}
