#include "aoc.hpp"

#include <fstream>
#include <istream>
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
	std::string	str;

	while (std::getline(file, str)) {
		std::istringstream	iss(str);
		std::array<Card, 5>	cards;
		int					bid;

		for (Card& card: cards)
			iss >> card;
		iss >> bid;
		data.push_back(Hand(cards, bid));
	}
}
