#ifndef AOC_HPP
# define AOC_HPP

# include "Range.hpp"

# include <iostream>
# include <vector>

class Map: public std::vector<std::pair<Range>> {
public:
	size_t	lowest_correspondence(size_t) const;
};

struct Data {
public:
	std::vector<int>	seeds;
	std::vector<Map>	maps;
};

Data	read_input(char const*);

#endif // AOC_HPP
