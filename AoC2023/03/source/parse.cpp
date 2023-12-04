#include "aoc.hpp"

#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>

static void	parse_input(std::ifstream&, Data&);

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
		for (size_t x = 0; x < line.length(), ++x) {
			if (line[x] == '.')
				++x;
			else if (std::isdigit(line[x])) {
				size_t	len = 1;
				while (std::isdigit(line[x + len]))
					len++;
				long	num = std::stol(std::substr(line, x, len));
				data.numbers.push_back(Number(num, Point(x, y), len));
				x += len;
			}
		++y;
	}
}
