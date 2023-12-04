#include "aoc.hpp"
#include "Card.hpp"

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

static void
parse_input(std::ifstream& file, Data& data) {
	std::string	line;

	while (std::getline(file, line)) {
		Card				card;
		std::istringstream	iss(line);
		
		iss >> card;
		data.emplace_back(card);
	}
}
