#include "Range.hpp"

#include <ostream>

// Constructors

Range::Range(size_t begin, size_t length):
	_begin(begin), _length(length) {}

// Operators

Range::operator std::string() const {
	return (std::to_string(_begin) + '-' + std::to_string(end()));
}

// Public methods

size_t
Range::begin() const {
	return (_begin);
}

size_t
Range::length() const {
	return (_length);
}

size_t
Range::end() const {
	return (_begin + _length);
}

size_t
Range::offset(size_t num) const {
	if (num >= _begin && num < end())
		return (num - _begin);
	return (-1);
}

// Non-member functions

std::ostream&
operator<<(std::ostream& os, Range const& range) {
	os << std::string(range);
	return (os);
}
