#include "Card.h"

using namespace std;

Card::Card(int id, std::vector<int> numbers, std::vector<int> winningNumbers) : ID(id), MatchingNumbers(0), Numbers(numbers), WinningNumbers(winningNumbers)
{}

void Card::CalculateMatchingNumbers()
{
	MatchingNumbers = 0;

	for (vector<int>::iterator i = Numbers.begin(); i != Numbers.end(); ++i)
	{
		for (vector<int>::iterator j = WinningNumbers.begin(); j != WinningNumbers.end(); ++j)
		{
			if (*i == *j)
			{
				++MatchingNumbers;
			}
		}
	}
}

ostream& operator << (ostream &o, const Card &card)
{
	o << "Card " << card.ID << ":";
	for (vector<int>::const_iterator i = card.WinningNumbers.begin(); i != card.WinningNumbers.end(); ++i)
	{
		o << " " << *i;
	}
	o << " |";
	for (vector<int>::const_iterator i = card.Numbers.begin(); i < card.Numbers.end(); ++i)
	{
		o << " " << *i;
	}
	return o;
}
