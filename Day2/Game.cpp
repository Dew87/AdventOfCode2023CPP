#include "Game.h"

using namespace std;

Game::Game(int id, vector<Hand> hands) : ID(id), Hands(hands)
{}

ostream& operator << (ostream &o, const Game &game)
{
	o << "Game " << game.ID << ":";
	if (!game.Hands.empty())
	{
		vector<Hand>::const_iterator i, end;
		for (i = game.Hands.begin(), end = --game.Hands.end(); i != end; ++i)
		{
			o << " " << *i << ";";
		}
		o << " " << *i;
	}
	return o;
}
