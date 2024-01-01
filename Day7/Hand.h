#ifndef HAND_H
#define HAND_H

#include <ostream>
#include <vector>

extern const char CARDS[];
extern const size_t HAND_SIZE;
extern const size_t NUMBER_OF_CARDS;

struct Hand
{
	Hand(std::vector<int> cards, int bid);
	void CalculateTier();
	void JackToJoker();

	std::vector<int> Cards;
	int Bid;
	int Tier;
};

bool operator < (const Hand a, const Hand b);
std::ostream& operator << (std::ostream &o, const Hand &hand);

#endif
