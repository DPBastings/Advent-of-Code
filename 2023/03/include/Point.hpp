#ifndef POINT_HPP
# define POINT_HPP

struct Point {
public:
	Point(long, long);

	long	x() const;
	long	y() const;

private:
	long	_x;
	long	_y;
}; // struct Point

# endif // POINT_HPP
