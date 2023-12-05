#ifndef RANGE_HPP
# define RANGE_HPP

# include <iostream>
# include <string>

class Range {
public:
	Range(size_t, size_t);

	operator std::string() const;

	size_t	begin() const;
	bool	contains(size_t) const;
	size_t	end() const;

private:
	size_t	_begin;
	size_t	_end;
};

std::istream&	operator>>(std::istream&, Range&);
std::ostream&	operator<<(std::ostream&, Range const&);

#endif // RANGE_HPP
