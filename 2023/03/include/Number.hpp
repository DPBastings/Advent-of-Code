#ifndef NUMBER_HPP
# define NUMBER_HPP

# include "Point.hpp"

# include <ostream>
# include <string>
# include <vector>

class Symbol;

class Number {
public:
	using Points = std::vector<Point>;
	Number(int, Points const&);

	operator	std::string() const;

	int				value() const;
	Points const&	points() const;
	Points			adjacent() const;
	bool			is_partnum(std::vector<Symbol> const&) const;

private:
	int		_value;
	Points	_points;
}; // class Number

std::ostream&	operator<<(std::ostream&, Number const&);

#endif // NUMBER_HPP
