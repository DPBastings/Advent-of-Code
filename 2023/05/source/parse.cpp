#include "aoc.hpp"

#include <fstream>
#include <string>
#include <sstream>

static void	parse_input(std::ifstream&, Data&);
static void	parse_seeds(std::ifstream&, Data::Seeds&, Data::SeedRanges&);
static void	parse_maps(std::ifstream&, Data::Maps&);

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
	parse_seeds(file, data.seeds, data.seed_ranges);
	parse_maps(file, data.maps);
}

static void
parse_seeds(std::ifstream& file, Data::Seeds& seeds, Data::SeedRanges& seed_ranges) {
	std::string	str;

	std::getline(file, str);

	std::istringstream	iss(str);

	iss >> str;
	while (iss.eof() == false) {
		size_t	seed;
		size_t	rnglen;
		iss >> seed >> rnglen;
		seed_ranges.push_back(Range(seed, rnglen));
		seeds.push_back(seed);
		seeds.push_back(rnglen); // Also add range length as a seed (for part 1)
	}
	std::getline(file, str); // Skip the blank line.
}

static void
parse_maps(std::ifstream& file, Data::Maps& maps) {
	std::string	line;

	while (std::getline(file, line)) {
		Map	map(line);
		while (std::getline(file, line)) {
			if (line.length() <= 1)
				break;
			std::istringstream	iss(line);
			MapLine				mapline;
			iss >> mapline;
			map.push_back(mapline);
		};
		maps.push_back(map);
	}
}
