#include "aoc.hpp"
#include "Card.hpp"

#include <cstddef>
#include <stdexcept>
#include <string>

static size_t	solve1(Data const&);
static size_t	solve2(Data const&);

int
main(int argc, char** argv) {
	if (argc != 2)
		return (EXIT_FAILURE);
	Data const	data = read_input(argv[1]);
	std::cout << "Solution 1: " << solve1(data) << '\n';
	std::cout << "Solution 2: " << solve2(data) << std::endl;
	return (EXIT_SUCCESS);
}

static size_t
solve1(Data const& data) {
	int	result = 0;
	return (result);
}

static size_t
solve2(Data const& data) {
}
