#include "aoc.hpp"
#include "CubeSet.hpp"
#include "Game.hpp"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using Games = std::vector<Game>;

static void	games_read(std::ifstream&, Games&);
static int	solve1(Games const&);
static int	solve2(Games const&);

CubeSet const	g_bag(12, 13, 14);

int
main(int argc, char** argv) {
	if (argc != 2)
		return (EXIT_FAILURE);
	std::ifstream	input;
	input.open(argv[1]);

	Games	games;
	games_read(input, games);
	input.close();
	std::cout << "Solution 1: " << solve1(games) << '\n';
	std::cout << "Solution 2: " << solve2(games) << std::endl;
	return (EXIT_SUCCESS);
}

static void
games_read(std::ifstream& inf, Games& games) {
	std::string	line;

	while (std::getline(inf, line))
		games.emplace_back(parse_line(line));
}

static int
solve1(Games const& games) {
	int	result = 0;

	for (Game const& game: games)
		if (game.is_possible(g_bag))
			result += (game.id());
	return (result);
}

static int
solve2(Games const& games) {
	int	result = 0;

	for (Game const& game: games) {
		CubeSet const	maxset = game.max();
		int const		power = maxset.power();
		result += power;
	}
	return (result);
}
