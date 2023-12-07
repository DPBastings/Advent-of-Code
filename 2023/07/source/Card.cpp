#include "Card.hpp"

// Constructors

Card::Card(char label):
	_label(label) {}

// Operators

bool
Card::operator==(Card const& that) const {
	return (_label == that._label);
}

bool
Card::operator!=(Card const& that) const {
	return (_label != that._label);
}

bool
Card::operator<(Card const& that) const {
	return (strength() < that.strength());
}

bool
Card::operator<=(Card const& that) const {
	return (strength() <= that.strength());
}

bool
Card::operator>(Card const& that) const {
	return (strength() > that.strength());
}

bool
Card::operator>=(Card const& that) const {
	return (strength() >= that.strength());
}

Card::operator std::string() const {
	return (std::string("[") + _label + "]");
}

// Public methods

int
Card::strength() const {
	int	result = 0;
	for (char const& tested: _possible_labels) {
		if (tested == _label)
			return (result);
		++result;
	}
	return (-1);
}

// Non-member functions

std::istream&
operator>>(std::istream& is, Card& card) {
	char	label;

	is >> label;
	card = Card(label);
	return (is);
}

std::ostream&
operator<<(std::ostream& os, Card const& card) {
	os << std::string(card);
	return (os);
}
