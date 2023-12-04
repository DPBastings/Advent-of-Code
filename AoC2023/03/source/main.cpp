#include "aoc.hpp"
#include "Number.hpp"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>

static int		solve1(Data const&);
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

static int
solve1(Data const& data) {
	int	result = 0;
	
	return (result);
}

static size_t
solve2(Data const& data) {
	std::vector<size_t>	counts(data.size(), 1);

	for (auto const& card: data) {
		int const	value = card.count_winners();
		for (size_t next = card.id() + 1; next <= card.id() + value; ++next) {
			try {
				counts.at(next - 1) += counts.at(card.id() - 1);
			} catch (std::out_of_range&) {
				continue;
			}
		}
	}
	return (vector_sum(counts));
}
