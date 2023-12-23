#ifndef CARD_H
#define CARD_H

#include <ostream>
#include <vector>

struct Card
{
	Card(int ID, std::vector<int> numbers, std::vector<int> winningNumbers);

	void CalculateMatchingNumbers();

	int ID;
	int matchingNumbers;
	std::vector<int> numbers;
	std::vector<int> winningNumbers;
};

std::ostream& operator << (std::ostream &o, const Card &card);

#endif
