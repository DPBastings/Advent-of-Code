#ifndef CARD_HPP
# define CARD_HPP

# include <array>
# include <iostream>
# include <string>

class Card {
public:
	Card() = default;
	Card(char);

	bool	operator==(Card const&) const;
	bool	operator!=(Card const&) const;
	bool	operator<(Card const&) const;
	bool	operator<=(Card const&) const;
	bool	operator>(Card const&) const;
	bool	operator>=(Card const&) const;
			operator std::string() const;

	int	strength() const;

	static std::array<char, 13>	possible_labels;
	static bool					uses_jokers;

private:
	char	_label;
}; // class Card

std::istream&	operator>>(std::istream&, Card&);
std::ostream&	operator<<(std::ostream&, Card const&);

#endif // CARD_HPP
