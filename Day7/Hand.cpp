#include "Hand.h"
#include <algorithm>

using namespace std;

const char CARDS[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
const size_t HAND_SIZE = 5;
const size_t NUMBER_OF_CARDS = 15;

Hand::Hand(vector<int> cards, int bid) : Cards(cards), Bid(bid)
{
	CalculateTier();
}

void Hand::CalculateTier()
{
	vector<int> occurrences;
	vector<int> cards = Cards;
	sort(cards.begin(), cards.end());

	int count = 0;
	int jokers = 0;
	int value = *cards.begin();
	for (vector<int>::iterator i = cards.begin(); i != cards.end(); ++i)
	{
		if (*i == 0)
		{
			++jokers;
		}
		else if (*i == value)
		{
			++count;
		}
		else
		{
			occurrences.push_back(count);
			count = 1;
			value = *i;
		}
	}
	occurrences.push_back(count);

	// Sort occurrences in descending order
	sort(occurrences.rbegin(), occurrences.rend());
	if (occurrences[0] + jokers == 5) // Five of a kind
	{
		Tier = 6;
	}
	else if (occurrences[0] + jokers == 4) // Four of a kind
	{
		Tier = 5;
	}
	else if (occurrences[0] + jokers == 3 && occurrences[1] == 2) // Full house
	{
		Tier = 4;
	}
	else if (occurrences[0] + jokers == 3) // Three of a kind
	{
		Tier = 3;
	}
	else if (occurrences[0] + jokers == 2 && occurrences[1] == 2) // Two pair
	{
		Tier = 2;
	}
	else if (occurrences[0] + jokers == 2) // One pair
	{
		Tier = 1;
	}
	else // High card
	{
		Tier = 0;
	}
}

void Hand::JackToJoker()
{
	for (vector<int>::iterator i = Cards.begin(); i != Cards.end(); ++i)
	{
		if (*i == 11)
		{
			*i = 0;
		}
	}
}

bool operator < (const Hand a, const Hand b)
{
	if (a.Tier != b.Tier)
	{
		return a.Tier < b.Tier;
	}
	else
	{
		for (size_t i = 0; 0 < HAND_SIZE; ++i)
		{
			if (a.Cards[i] != b.Cards[i])
			{
				return a.Cards[i] < b.Cards[i];
			}
		}
	}

	return false;
}

ostream& operator << (ostream &o, const Hand &hand)
{
	for (vector<int>::const_iterator i = hand.Cards.begin(); i != hand.Cards.end(); ++i)
	{
		o << CARDS[*i];
	}

	o << " " << hand.Bid;

	return o;
}
