#include "aoc.hpp"
#include "Number.hpp"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>

static int	solve1(Data const&);
static int	solve2(Data const&);

template<typename T>
std::ostream&
operator<<(std::ostream& os, std::vector<T> const& vec) {
	for (T const& item: vec)
		os << item << ", ";
	return (os);
}

int
main(int argc, char** argv) {
	if (argc != 2)
		return (EXIT_FAILURE);
	Data const	data = read_input(argv[1]);
	// std::cout << data.numbers << '\n';
	// std::cout << data.symbols << '\n';
	std::cout << "Solution 1: " << solve1(data) << '\n';
	std::cout << "Solution 2: " << solve2(data) << std::endl;
	return (EXIT_SUCCESS);
}

static int
solve1(Data const& data) {
	int	result = 0;

	for (Number const& num: data.numbers) {
		if (num.is_partnum(data.symbols)) {
			std::cout << num.value() << ' ';
			result += num.value();
		}
	}
	std::cout << '\n';
	return (result);
}

static int
solve2(Data const& data) {
	int	result = 0;

	for (Symbol const& sym: data.symbols)
		result += sym.gear_ratio(data.numbers);
	return (result);
}
