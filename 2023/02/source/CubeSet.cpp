#include "CubeSet.hpp"

#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>

// Constructors

CubeSet::CubeSet(int red, int green, int blue):
	_red(red), _green(green), _blue(blue) {
}

// Operators

bool
CubeSet::operator==(CubeSet const& that) {
	return (_red == that._red && _green == that._green && _blue == that._blue);
}

bool
CubeSet::operator!=(CubeSet const& that) {
	return (_red != that._red || _green != that._green || _blue != that._blue);
}

bool
CubeSet::operator<=(CubeSet const& that) {
	return (_red <= that._red && _green <= that._green && _blue <= that._blue);
}

bool
CubeSet::operator>=(CubeSet const& that) {
	return (_red >= that._red && _green >= that._green && _blue >= that._blue);
}

CubeSet::operator std::string() const {
	return ("[red: " + std::to_string(_red)
			+ ", green: " + std::to_string(_green)
			+ ", blue: " + std::to_string(_blue) + "]");
}

// Public methods

int
CubeSet::red() const {
	return (_red);
}

int
CubeSet::green() const {
	return (_green);
}

int
CubeSet::blue() const {
	return (_blue);
}

int
CubeSet::power() const {
	std::array<int, 3>	counts{_red, _green, _blue};
	int					result = 0;

	for (int const& number: counts) {
		if (number > 0) {
			if (result == 0)
				result = number;
			else
				result *= number;
		}
	}
	return (result);
}

// Non-member functions

std::ostream&
operator<<(std::ostream& os, CubeSet const& set) {
	os << std::string(set);
	return (os);
}

std::istream&
operator>>(std::istream& is, CubeSet& set) {
	int			red = 0;
	int			green = 0;
	int			blue = 0;
	std::string	str;
	while (std::getline(is, str, ',')) {
		std::istringstream	iss(str);
		int					count = 0;
		std::string			colour;
		
		iss >> count >> colour;
		if (colour == "red")
			red += count;
		else if (colour == "green")
			green += count;
		else if (colour == "blue")
			blue += count;
		else
			throw (std::logic_error("unrecognized colour name"));
	}
	set = CubeSet(red, green, blue);
	return (is);
}
