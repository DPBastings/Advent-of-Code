#ifndef AOC_HPP
# define AOC_HPP

# include "Hand.hpp"

# include <iostream>
# include <string>
# include <vector>

using Data = std::vector<Hand>;

template<typename T>
std::ostream&
operator<<(std::ostream& os, std::vector<T> const& vec) {
	for (T const& item: vec)
		os << item << ' ';
	return (os);
}

Data	read_input(char const*);

#endif // AOC_HPP
