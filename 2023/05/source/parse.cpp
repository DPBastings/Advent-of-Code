#include "aoc.hpp"

#include <fstream>
#include <string>
#include <sstream>

static void	parse_input(std::ifstream&, Data&);

Data
read_input(char const* fname) {
	Data			data;
	std::ifstream	file;

	file.open(fname);
	parse_input(file, data);
	file.close();
	return (data);
}
