#include "Hand.hpp"

// Constructors

Hand::Hand(std::array<Card, 5> cards, int bid):
	std::array<Card, 5>(cards), _bid(bid) {}

// Operators

bool
Hand::operator<(Hand const& that) const {
	Type const	this_type = type();
	Type const	that_type = type();
	int const	rank_comparison = compare_rank(that);

	return (this_type < that_type
			|| (this_type == that_type && rank_comparison == -1));
}

bool
Hand::operator>(Hand const& that) const {
	Type const	this_type = type();
	Type const	that_type = type();
	int const	rank_comparison = compare_rank(that);

	return (this_type > that_type
			|| (this_type == that_type && rank_comparison == 1));
}

Hand::operator std::string() const {
	std::string	result;

	for (auto const& elem: *this)
		result += std::string(elem);
	result += ": ";
	result += std::to_string(_bid);
	return (result);
}

// Public methods

Hand::Type
Hand::type() const {
	std::array<int, 13>	card_counts{0};

	for (Card const& card: *this)
		++card_counts[card.strength()]; // count card occurrences

	std::array<int, 6>	combinations{0};

	for (int const count: card_counts)
		++combinations[count]; 
	if (combinations[5] == 1)
		return (five_of_a_kind);
	if (combinations[4] == 1)
		return (four_of_a_kind);
	if (combinations[3] == 1) {
		if (combinations[2] == 1)
			return (full_house);
		return (three_of_a_kind);
	}
	if (combinations[2] == 2)
		return (two_pair);
	if (combinations[2] == 1)
		return (one_pair);
	return (high_card);
}

int
Hand::bid() const {
	return (_bid);
}

int
Hand::compare_rank(Hand const& that) const {
	for (size_t i = 0; i < this->size(); ++i) {
		if ((*this)[i] < that[i])
			return (-1);
		if ((*this)[i] > that[i])
			return (1);
	}
	return (0);
}

// Non-member functions

std::ostream&
operator<<(std::ostream& os, Hand const& hand) {
	os << std::string(hand);
	return (os);
}
