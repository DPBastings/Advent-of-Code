#ifndef NUMBER_HPP
# define NUMBER_HPP

# include "Point.hpp"

# include <vector>

class Number {
public:
	using Points = std::vector<Point>;
	Number(int, Points const&);

	int				value() const;
	Points const&	points() const;
	Points			adjacent() const;

private:
	int		_value;
	Points	_points;
}; // class Number

#endif // NUMBER_HPP
