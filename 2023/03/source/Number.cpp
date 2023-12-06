#include "Number.hpp"
#include "Point.hpp"
#include "Symbol.hpp"

#include <stdexcept>

// Constructors

Number::Number(int value, Number::Points const& points):
	_value(value), _points(points) {
}

// Operators

Number::operator std::string() const {
	std::string	result(std::to_string(_value) + " at { ");

	for (Point const& pt: _points)
		result += std::string(pt) + ' ';
	result += '}';
	return (result);
}

// Public methods

int
Number::value() const {
	return (_value);
}

Number::Points const&
Number::points() const {
	return (_points);
}

bool
Number::is_partnum(std::vector<Symbol> const& symbols) const {
	for (Point const& pt: this->adjacent())
		for (Symbol const& symb: symbols)
			if (symb.point() == pt)
				return (true);
	return (false);
}

static void	push_adj(Point const&, Number::Points&, int = 0, int = 0);

Number::Points
Number::adjacent() const {
	Points		result;
	auto const	first = _points.cbegin();
	auto const	last = _points.cend() - 1;

	push_adj(*first, result, -1, 0);
	push_adj(*first, result, -1, -1);
	push_adj(*first, result, -1, 1);
	for (Point const& pt: _points) {
		push_adj(pt, result, 0, 1);
		push_adj(pt, result, 0, -1);
	}
	push_adj(*last, result, 1, 0);
	push_adj(*last, result, 1, -1);
	push_adj(*last, result, 1, 1);
	return (result);
}

// Non-member functions

std::ostream&
operator<<(std::ostream& os, Number const& num) {
	os << std::string(num);
	return (os);
}

// Helpers

static void
push_adj(Point const& pt, Number::Points& arr, int xoffset, int yoffset) {
	try {
		arr.push_back(Point(pt.x() + xoffset, pt.y() + yoffset));
	} catch (std::out_of_range&) {};
}
