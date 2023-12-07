#include "aoc.hpp"

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>

static int	solve1(Data const&);
static int	solve2(Data const&);

int
main(int argc, char** argv) {
	if (argc != 2)
		return (EXIT_FAILURE);
	Data const	data = read_input(argv[1]);
	for (auto const& hand: data)
		std::cout << hand << ": " << hand.type() << '\n';
	std::cout << "Solution 1:\n" << solve1(data) << '\n';
	std::cout << "Solution 2:\n" << solve2(data) << std::endl;
	return (EXIT_SUCCESS);
}

static int
solve1(Data const& data) {
	int	result = 0;

	Data	sorted_data(data);
	std::sort(sorted_data.begin(), sorted_data.end());
	std::cout << sorted_data << '\n';
	int	rank = sorted_data.size();
	for (Hand const& hand: sorted_data)
		result += hand.bid() * rank--;
	return (result);
}

static int
solve2(Data const&) {
	return (0);
}
