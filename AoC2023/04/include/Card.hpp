#ifndef CARD_HPP
# define CARD_HPP

# include <array>
# include <iostream>
# include <string>

class Card {
public:
	using Winners = std::array<int, 10>;
	using Numbers = std::array<int, 25>;

	Card() = default;
	Card(size_t, Winners const&, Numbers const&);

	operator std::string() const;

	size_t	id() const;
	int		count_winners() const;
	int		value() const;

private:
	size_t	_id;
	Winners	_winners;
	Numbers	_numbers;

};

std::istream&	operator>>(std::istream&, Card&);
std::ostream&	operator<<(std::ostream&, Card const&);

#endif // CARD_HPP
