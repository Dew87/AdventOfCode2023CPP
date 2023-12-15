#include "Game.h"

using namespace std;

Game::Game(int ID) : ID(ID)
{}

ostream& operator << (ostream &o, const Game &game)
{
	o << "Game " << game.ID << ":";
	if (0 < game.hands.size())
	{
		for (int i = 0; i < game.hands.size() - 1; ++i)
		{
			o << " " << game.hands[i] << ";";
		}
		o << " " << game.hands[game.hands.size() - 1];
	}
	return o;
}
