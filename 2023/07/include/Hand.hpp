#ifndef HAND_HPP
# define HAND_HPP

# include "Card.hpp"

# include <array>
# include <iostream>
# include <string>

class Hand: public std::array<Card, 5> {
public:
	enum Type {
		high_card, one_pair, two_pair, three_of_a_kind, full_house,
		four_of_a_kind, five_of_a_kind
	};

	Hand(std::array<Card, 5>, int);

	bool	operator==(Hand const&) const;
	bool	operator!=(Hand const&) const;
	bool	operator<(Hand const&) const;
	bool	operator<=(Hand const&) const;
	bool	operator>(Hand const&) const;
	bool	operator>=(Hand const&) const;
			operator std::string() const;

	Type	type() const;
	int		bid() const;
	int		compare_rank(Hand const&) const;

private:
	int	_bid;
}; // class Hand

std::istream&	operator>>(std::istream&, Hand&);
std::ostream&	operator<<(std::ostream&, Hand const&);

#endif // HAND_HPP
