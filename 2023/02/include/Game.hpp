#ifndef GAME_HPP
# define GAME_HPP

# include "CubeSet.hpp"

# include <ostream>
# include <vector>

class Game: public std::vector<CubeSet> {
public:
	Game(int);

	int		id() const;

	bool	is_possible(CubeSet const&) const;
	CubeSet	max() const;
	CubeSet	min() const;

private:
	int const	_id;
};

std::ostream&	operator<<(std::ostream&, Game const&);

#endif // GAME_HPP
