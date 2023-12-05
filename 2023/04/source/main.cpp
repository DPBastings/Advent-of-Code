#include "aoc.hpp"
#include "Card.hpp"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>

static int		solve1(Data const&);
static size_t	solve2(Data const&);

template<typename T>
static T	vector_sum(std::vector<T> const&);

using CountedCard = std::pair<Card, unsigned int>;
using CountedData = std::vector<CountedCard>;

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
	for (auto const& card: data)
		result += card.value();
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

template<typename T>
static T	vector_sum(std::vector<T> const& vec) {
	T	sum = 0;
	for (T const& item: vec)
		sum += item;
	return (sum);
}
