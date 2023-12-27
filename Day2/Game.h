#ifndef GAME_H
#define GAME_H

#include "Hand.h"
#include <ostream>
#include <vector>

struct Game
{
	Game(int id, std::vector<Hand> hands);

	int ID;
	std::vector<Hand> Hands;
};

std::ostream& operator << (std::ostream &o, const Game &game);

#endif
