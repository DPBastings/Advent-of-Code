#include "aoc.hpp"

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>

static size_t	solve1(Data const&);
static size_t	solve2(Data const&);

static void	add_destination(std::vector<size_t>&, Data::Maps const&, size_t);

int
main(int argc, char** argv) {
	if (argc != 2)
		return (EXIT_FAILURE);
	Data const	data = read_input(argv[1]);
	// std::cout << data.seeds << '\n' << data.maps << '\n';
	std::cout << "Solution 1:\n" << solve1(data) << '\n';
	std::cout << "Solution 2:\n" << solve2(data) << std::endl;
	return (EXIT_SUCCESS);
}

static size_t
solve1(Data const& data) {
	std::vector<size_t>	results;

	for (auto const& seed: data.seeds)
		add_destination(results, data.maps, seed);
	return (*std::min_element(results.cbegin(), results.cend()));
}

static size_t
solve2(Data const& data) {
	std::vector<size_t>	results;

	for (auto const& range: data.seed_ranges) {
		for (size_t seed = range.begin(); seed < range.end(); ++seed) {
			add_destination(results, data.maps, seed);
		}
	}
	return (*std::min_element(results.cbegin(), results.cend()));
}

static void
add_destination(std::vector<size_t>& results, Data::Maps const& maps, size_t seed) {
	for (auto const& map: maps)
		seed = map.find_destination(seed);
	results.push_back(seed);
}
