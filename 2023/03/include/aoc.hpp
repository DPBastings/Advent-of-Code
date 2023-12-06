#ifndef AOC_HPP
# define AOC_HPP

# include "Number.hpp"
# include "Symbol.hpp"

# include <string>
# include <vector>

struct Data {
	std::vector<Number>	numbers;
	std::vector<Symbol>	symbols;
};

Data	read_input(char const*);

bool	check_adjacent_symbols(Data const&, Point);
int		expand_number(std::string const&, Point);

#endif // AOC_HPP
