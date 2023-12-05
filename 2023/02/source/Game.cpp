#include "Game.hpp"

#include <ostream>
#include <vector>

// Constructors

Game::Game(int id):
	std::vector<CubeSet>(), _id(id) {
}

// Public methods

int
Game::id() const {
	return (_id);
}

bool
Game::is_possible(CubeSet const& bag) const {
	return (max() <= bag);
}

CubeSet
Game::max() const {
	int	red = 0;
	int	green = 0;
	int	blue = 0;

	for (CubeSet const& set: *this) {
		if (set.red() > red)
			red = set.red();
		if (set.green() > green)
			green = set.green();
		if (set.blue() > blue)
			blue = set.blue();
	}
	return (CubeSet(red, green, blue));
}

CubeSet
Game::min() const {
	int	red = std::numeric_limits<int>::max();
	int	green = std::numeric_limits<int>::max();
	int	blue = std::numeric_limits<int>::max();

	for (CubeSet const& set: *this) {
		if (set.red() < red)
			red = set.red();
		if (set.green() < green)
			green = set.green();
		if (set.blue() < blue)
			blue = set.blue();
	}
	return (CubeSet(red, green, blue));
}

// Non-member functions

std::ostream&
operator<<(std::ostream& os, Game const& game) {
	os << "Game " << game.id() << " {";
	for (auto const& set: game)
		os << set;
	os << "}";
	return (os);
}
