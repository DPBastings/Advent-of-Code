#include "aoc.hpp"

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>

static int	solve1(Data const&);
static int	solve2(Data const&);

Card::possible_labels = {
	'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'
};
Card::uses_jokers = false;

int
main(int argc, char** argv) {
	if (argc != 2)
		return (EXIT_FAILURE);
	Data const	data = read_input(argv[1]);
	std::cout << "Solution 1:\n" << solve1(data) << '\n';
	std::cout << "Solution 2:\n" << solve2(data) << std::endl;
	return (EXIT_SUCCESS);
}

static int
solve1(Data data) {
	int	result = 0;

	std::sort(data.begin(), data.end(), std::greater<Hand>());
	for (auto const& hand: data)
		std::cout << hand << ": " << hand.type() << '\n';
	int	rank = 1;
	for (Hand const& hand: sorted_data)
		result += hand.bid() * rank++;
	return (result);
}

static int
solve2(Data data) {
	Card::possible_labels = {
		'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A'
	};
	Card::uses_jokers = true;

	int	result = 0;
	std::sort(data.begin(), data.end(), std::greater<Hand>());
	for (auto const& hand: data)
		std::cout << hand << ": " << hand.type() << '\n';
	int	rank = 1;
	for (Hand const& hand: sorted_data)
		result += hand.bid() * rank++;
	return (0);
}
