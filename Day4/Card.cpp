#include "Card.h"

using namespace std;

Card::Card(int ID, std::vector<int> numbers, std::vector<int> winningNumbers) : ID(ID), matchingNumbers(0), numbers(numbers), winningNumbers(winningNumbers)
{}

void Card::CalculateMatchingNumbers()
{
	matchingNumbers = 0;

	for (size_t i = 0; i < numbers.size(); ++i)
	{
		for (size_t j = 0; j < winningNumbers.size(); ++j)
		{
			if (numbers[i] == winningNumbers[j])
			{
				++matchingNumbers;
			}
		}
	}
}

ostream& operator << (ostream &o, const Card &card)
{
	o << "Card " << card.ID << ":";
	for (size_t i = 0; i < card.winningNumbers.size(); ++i)
	{
		o << " " << card.winningNumbers[i];
	}
	o << " |";
	for (size_t i = 0; i < card.numbers.size(); ++i)
	{
		o << " " << card.numbers[i];
	}
	return o;
}
