#include "aoc.hpp"

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>

static long long	solve1(Data const&);
static long long	solve2(Data const&);

int
main(int argc, char** argv) {
	if (argc != 2)
		return (EXIT_FAILURE);
	Data const	data = read_input(argv[1]);
	std::cout << data;
	std::cout << "Solution 1:\n" << solve1(data) << '\n';
	std::cout << "Solution 2:\n" << solve2(data) << std::endl;
	return (EXIT_SUCCESS);
}

static long long
solve1(Data const& data) {
	long long	result = data.cbegin()->options();
	std::cout << data.cbegin()->options() << '\n';
	for (auto it = data.cbegin() + 1; it < data.cend(); ++it) {
		std::cout << it->options() << '\n';
		result *= it->options();
	}
	return (result);
}

static long long
solve2(Data const&) {
	Race	race(54817088, 446129210351007);
	return (race.options());
}
