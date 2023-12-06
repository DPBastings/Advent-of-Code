#include "aoc.hpp"

#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>

static void		parse_input(std::ifstream&, Data&);
static Number	parse_number(std::string const&, size_t&, size_t);
static Symbol	parse_symbol(std::string const&, size_t&, size_t);

Data
read_input(char const* fname) {
	Data			data;
	std::ifstream	file;

	file.open(fname);
	if (!file.good())
		throw (std::runtime_error("bad file"));
	parse_input(file, data);
	file.close();
	return (data);
}

static void
parse_input(std::ifstream& file, Data& data) {
	std::string	line;
	size_t		y = 0;

	while (std::getline(file, line)) {
		size_t	x = 0;
		while (x < line.length()) {
			if (std::isdigit(line[x]))
				data.numbers.push_back(parse_number(line, x, y));
			else if (line[x] != '.')
				data.symbols.push_back(parse_symbol(line, x, y));
			else
				++x;
		}
		++y;
	}
}

static Number
parse_number(std::string const& line, size_t& x, size_t y) {
	long			value = 0;
	Number::Points	positions;
	while (std::isdigit(line[x])) {
		value = value * 10 + line[x] - '0';
		positions.push_back(Point(x, y));
		++x;
	}
	return (Number(value, positions));
}

static Symbol
parse_symbol(std::string const& line, size_t& x, size_t y) {
	char	value = line[x];
	Point	pt(x, y);
	++x;
	return (Symbol(value, pt));
}
