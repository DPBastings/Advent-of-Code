#include "aoc.hpp"
#include "CubeSet.hpp"
#include "Game.hpp"

#include <string>
#include <sstream>

Game
parse_line(std::string const& line) {
	std::istringstream	iss(line);
	std::string			identifier;
	int					id;

	std::getline(iss, identifier, ':');
	std::istringstream	hiss(identifier);
	parse_id(hiss, id);

	Game	game(id);
	CubeSet	cset(0, 0, 0);

	while (parse_set(iss, cset))
		game.emplace_back(cset);
	return (game);
}

std::istringstream&
parse_id(std::istringstream& iss, int& num) {
	std::string	header;

	iss >> header;
	iss >> num;
	return (iss);
}

std::istringstream&
parse_set(std::istringstream& iss, CubeSet& cset) {
	std::string	str;

	std::getline(iss, str, ';');
	std::istringstream(str) >> cset;
	return (iss);
};
