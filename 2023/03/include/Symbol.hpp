#ifndef SYMBOL_HPP
# define SYMBOL_HPP

# include "Point.hpp"
# include "Number.hpp"

# include <ostream>
# include <string>
# include <vector>

class Symbol {
public:
	Symbol(char, Point const&);

	operator std::string() const;

	char				value() const;
	Point				point() const;
	std::vector<Point>	adjacent() const;
	int					gear_ratio(std::vector<Number> const&) const;

private:
	char	_value;
	Point	_point;
}; // class Symbol

std::ostream&	operator<<(std::ostream&, Symbol const&);

#endif // SYMBOL_HPP
