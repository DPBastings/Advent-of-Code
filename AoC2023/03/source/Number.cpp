#include "Number.hpp"
#include "Point.hpp"

static Point	point_range(Point const&, long);

// Constructors

Number::Number(int value, Points const& points):
	_value(value), _points(points) {
}

Number::Number(int value, Point const& pt, long digitcount):
	_value(value), _points(point_range(pt, digitcount)) {
}

static Points
point_range(Point const& start, long len) {
	Points	result(1, start);
	long	offset = 1;

	while (--len)
		result.push_back(Point(start.x() + offset++, start.y()));
	return (result);
}

// Public methods

int
Number::value() const {
	return (_value);
}

Points const&
Number::points() const {
	return (_points);
}

static void	push_left(Point const&, Points&);
static void	push_right(Point const&, Points&);
static void	push_top(Point const&, Points&);
static void	push_bottom(Point const&, Points&);

Points
Number::adjacent() const {
	Points		result;
	auto const	first = _points.cbegin();
	auto const	last = _points.cend() - 1;

	push_left(*first, result);
	for (Point const& pt: _points)
		push_top(pt, result);
		push_bottom(pt, result);
	}
	push_right(*last, result);	
	return (result);
}

// Non-member functions

// Helpers

static void	push_left(Point const& pt, Points& arr) {
	try {
		arr.push_back(Point(pt.x - 1, pt.y));
	} catch (std::out_of_range&);
}

static void	push_right(Point const& pt, Points& arr) {
	try {
		arr.push_back(Point(pt.x + 1, pt.y));
	} catch (std::out_of_range&);
}

static void
push_top(Point const& pt, Points& arr) {
	try {
		arr.push_back(Point(pt.x, pt.y - 1));
	} catch (std::out_of_range&);
}

static void
push_bottom(Point const& pt, Points& arr) {
	try {
		arr.push_back(Point(pt.x, pt.y + 1));
	} catch (std::out_of_range&);
}
