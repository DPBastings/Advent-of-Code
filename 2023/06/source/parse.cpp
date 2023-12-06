#include "aoc.hpp"

#include <fstream>
#include <istream>
#include <string>
#include <sstream>

static void	parse_input(std::ifstream&, Data&);
static void	parse_headers(std::istream&, std::istream&);
static int	parse_datum(std::istream&);

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
	std::string			str;
	std::istringstream	timess;
	std::istringstream	distss;

	std::getline(file, str);
	timess.str(str);
	std::getline(file, str);
	distss.str(str);
	parse_headers(timess, distss);
	for (int i = 0; i < 4; ++i) {
		int	time = parse_datum(timess);
		int	record = parse_datum(distss);
		data.push_back(Race(time, record));
	}
}

static void
parse_headers(std::istream& timeis, std::istream& distis) {
	std::string	header;
	timeis >> header;
	distis >> header;
}

static int
parse_datum(std::istream& is) {
	int	datum;
	
	is >> datum;
	return (datum);
}
