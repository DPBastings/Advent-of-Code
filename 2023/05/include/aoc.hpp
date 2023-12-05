#ifndef AOC_HPP
# define AOC_HPP

# include "Range.hpp"

# include <iostream>
# include <string>
# include <vector>

class MapLine {
public:
	MapLine() = default;
	MapLine(Range const&, Range const&);

	Range const&	source() const;
	Range const&	destination() const;
	size_t			map(size_t) const;

private:
	Range	_source;
	Range	_destination;
};

std::istream&	operator>>(std::istream&, MapLine&);
std::ostream&	operator<<(std::ostream&, MapLine const&);

class Map: public std::vector<MapLine> {
public:
	Map(std::string const&);
	
	operator std::string() const;

	size_t				find_destination(size_t) const;
	std::string const&	title() const;

private:
	std::string	_title;
};

std::ostream&	operator<<(std::ostream&, Map const&);

struct Data {
public:
	using Seeds = std::vector<size_t>;
	using SeedRanges = std::vector<Range>;
	using Maps = std::vector<Map>;

	Seeds		seeds;
	SeedRanges	seed_ranges;
	Maps		maps;
};

template<typename T>
std::ostream&
operator<<(std::ostream& os, std::vector<T> const& vec) {
	for (T const& item: vec)
		os << item << ' ';
	return (os);
}

Data	read_input(char const*);

#endif // AOC_HPP
