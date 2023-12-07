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

private:
	static constexpr std::array<char, 13>	_possible_labels = {
		'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'
	};

	char	_label;
}; // class Card

std::istream&	operator>>(std::istream&, Card&);
std::ostream&	operator<<(std::ostream&, Card const&);

#endif // CARD_HPP
