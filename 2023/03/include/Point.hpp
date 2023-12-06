#ifndef POINT_HPP
# define POINT_HPP

# include <string>

struct Point {
public:
	Point(long, long);

	bool	operator==(Point const&) const;
	bool	operator!=(Point const&) const;
			operator std::string() const;

	long	x() const;
	long	y() const;

private:
	long	_x;
	long	_y;
}; // struct Point

# endif // POINT_HPP
