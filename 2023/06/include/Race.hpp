#ifndef RACE_HPP
# define RACE_HPP

# include <ostream>
# include <string>

class Race {
public:
	Race(long long, long long);

	operator std::string() const;

	long long	time() const;
	long long	record() const;
	long long	options() const;
private:
	long long	_time;
	long long	_record;
}; // class Race

std::ostream&	operator<<(std::ostream&, Race const&);

#endif // RACE_HPP
