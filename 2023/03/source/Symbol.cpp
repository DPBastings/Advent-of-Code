#include "Symbol.hpp"
#include "Number.hpp"

#include <ostream>
#include <string>

static void	push_adj(Point const&, std::vector<Point>&, int, int);

// Constructors

Symbol::Symbol(char value, Point const& point):
	_value(value), _point(point) {}

// Operators

Symbol::operator std::string() const {
	return (std::string("<") + _value + "> at " + std::string(_point));
}

// Public methods

char
Symbol::value() const {
	return (_value);
}

Point
Symbol::point() const {
	return (_point);
}

std::vector<Point>
Symbol::adjacent() const {
	std::vector<Point>	result;

	push_adj(_point, result, -1, 0);
	push_adj(_point, result, -1, -1);
	push_adj(_point, result, -1, 1);
	push_adj(_point, result, 0, 1);
	push_adj(_point, result, 0, -1);
	push_adj(_point, result, 1, 0);
	push_adj(_point, result, 1, -1);
	push_adj(_point, result, 1, 1);
	return (result);
}

// Non-member functions

int
Symbol::gear_ratio(std::vector<Number> const& nums) const {
	std::vector<Number>	neighbours;

	if (_value != '*')
		return (0);
	for (Point const& pt: adjacent()) {
		for (Number const& num: nums) {
			for (Point const& npt: num.points()) {
				if (npt == pt) {
					neighbours.push_back(num);
					break;
				}
			}
		}
	}
	if (neighbours.size() == 2)
		return (neighbours[0].value() * neighbours[1].value());
	return (0);
}

// Non-member functions

std::ostream&
operator<<(std::ostream& os, Symbol const& symb) {
	os << std::string(symb);
	return (os);
}

// Helpers

static void
push_adj(Point const& pt, std::vector<Point>& arr, int xoffset, int yoffset) {
	try {
		arr.push_back(Point(pt.x() + xoffset, pt.y() + yoffset));
	} catch (std::out_of_range&) {};
}
