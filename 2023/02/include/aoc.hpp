#ifndef AOC_HPP
# define AOC_HPP

# include "Game.hpp"
# include "CubeSet.hpp"

# include <string>

Game				parse_line(std::string const&);
std::istringstream&	parse_id(std::istringstream&, int&);
std::istringstream&	parse_set(std::istringstream&, CubeSet&);

#endif // AOC_HPP
