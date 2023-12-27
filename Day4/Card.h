#ifndef CARD_H
#define CARD_H

#include <ostream>
#include <vector>

struct Card
{
	Card(int id, std::vector<int> numbers, std::vector<int> winningNumbers);

	void CalculateMatchingNumbers();

	int ID;
	int MatchingNumbers;
	std::vector<int> Numbers;
	std::vector<int> WinningNumbers;
};

std::ostream& operator << (std::ostream &o, const Card &card);

#endif
