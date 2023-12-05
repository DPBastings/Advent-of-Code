#include "Card.hpp"

#include <array>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

static size_t	get_id(std::string const&);

template<typename T, size_t N>
static bool	array_contains(std::array<T, N> const&, T);
template<typename T, size_t N>
static void	get_array(std::string const&, std::array<T, N>&);

// Constructors

Card::Card(size_t id, Card::Winners const& winners, Card::Numbers const& numbers):
	_id(id), _winners(winners), _numbers(numbers) {
}

// Operators

Card::operator std::string() const {
	std::string	str("Card " + std::to_string(_id) + ": ");

	for (auto const& num: _winners) {
		str += std::to_string(num);
		str += ' ';
	}
	str += "| ";
	for (auto const& num: _numbers) {
		str += std::to_string(num);
		str += ' ';
	}
	return (str);
}

// Public methods

size_t
Card::id() const {
	return (_id);
}

int
Card::count_winners() const {
	int	n = 0;

	for (auto const& win: _winners)
		if (win != 0 && array_contains(_numbers, win))
			++n;
	return (n);
}

int
Card::value() const {
	int const	n = count_winners();

	switch (n) {
		case 0:
			return (0);
		case 1:
			return (1);
		default:
			return (std::pow(2, n));
	}
}

// Non-member functions

std::ostream&
operator<<(std::ostream& os, Card const& card) {
	os << std::string(card);
	return (os);
}

std::istream&
operator>>(std::istream& is, Card& card) {
	std::string	strs[3];

	std::getline(is, strs[0], ':');
	std::getline(is, strs[1], '|');
	std::getline(is, strs[2]);

	Card::Winners	winners{0};
	Card::Numbers	numbers{0};
	get_array(strs[1], winners);
	get_array(strs[2], numbers);
	card = Card(get_id(strs[0]), winners, numbers);
	return (is);
}

// Helpers

template<typename T, size_t N>
static bool
array_contains(std::array<T, N> const& array, T value) {
	for (T const& item: array)
		if (item == value)
			return (true);
	return (false);
}

static size_t
get_id(std::string const& str) {
	std::istringstream	iss(str);
	std::string			title;
	size_t				result;
	
	iss >> title >> result;
	// check for eof + proper title;
	return (result);
}

template<typename T, size_t N>
static void
get_array(std::string const& str, std::array<T, N>& array) {
	std::istringstream	iss(str);

	for (T& item: array)
		iss >> item;
	// check for eof
}
