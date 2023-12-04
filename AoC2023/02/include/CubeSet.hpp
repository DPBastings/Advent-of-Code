#ifndef CUBE_SET_HPP
# define CUBE_SET_HPP

# include <iostream>

class CubeSet {
public:
	CubeSet(int, int, int);

	bool	operator==(CubeSet const&);
	bool	operator!=(CubeSet const&);
	bool	operator<=(CubeSet const&);
	bool	operator>=(CubeSet const&);
			operator std::string() const;

	int	red() const;
	int	green() const;
	int	blue() const;
	int	power() const;

private:
	int	_red;
	int	_green;
	int	_blue;
};

std::istream&	operator>>(std::istream&, CubeSet&);
std::ostream&	operator<<(std::ostream&, CubeSet const&);

#endif // CUBE_SET_HPP
