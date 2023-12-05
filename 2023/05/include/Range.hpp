#ifndef RANGE_HPP
# define RANGE_HPP

# include <iostream>
# include <string>

class Range {
public:
	Range() = default;
	Range(size_t, size_t);

	operator std::string() const;

	size_t	begin() const;
	size_t	length() const;
	size_t	end() const;
	size_t	offset(size_t) const;

private:
	size_t	_begin;
	size_t	_length;
};

std::ostream&	operator<<(std::ostream&, Range const&);

#endif // RANGE_HPP
