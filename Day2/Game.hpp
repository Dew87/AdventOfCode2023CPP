#ifndef GAME_H
#define GAME_H

#include "Hand.hpp"
#include <ostream>
#include <vector>

struct Game
{
	Game(int ID);

	int ID;
	std::vector<Hand> hands;
};

std::ostream& operator << (std::ostream &o, const Game &game);

#endif
