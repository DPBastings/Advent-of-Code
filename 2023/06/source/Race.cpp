#include "Race.hpp"

#include <ostream>
#include <string>

// Constructors

Race::Race(long long time, long long record):
	_time(time), _record(record) {}

// Operators

Race::operator std::string() const {
	return (std::string("Race: ")
			+ std::to_string(_time)
			+ ", "
			+ std::to_string(_record));
}

// Public methods

long long
Race::time() const {
	return (_time);
}

long long
Race::record() const {
	return (_record);
}

#include <iostream>

long long
Race::options() const {
	long long	result = 0;
	for (long long time_pressed = 0; time_pressed < _time; ++time_pressed) {
		long long const	time_to_move = _time - time_pressed;
		long long const	distance = time_pressed * time_to_move;
		if (distance > _record)
			++result;
	}
	return (result);
}

// Non-member functions

std::ostream&
operator<<(std::ostream& os, Race const& race) {
	os << std::string(race);
	return (os);
}
