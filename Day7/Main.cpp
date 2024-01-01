#include "Hand.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void InputHands(vector<Hand> &output)
{
	cout << "Start of hands input (blank line to end)\n";
	while (true)
	{
		string input;
		getline(cin, input);
		if (input != "")
		{
			size_t index;
			index = input.find(" ");
			if (index != string::npos)
			{
				int bid;
				vector<int> cards;

				string sCards = input.substr(0, index);
				string sBid = input.substr(index + 1);

				// Get cards
				for (string::iterator i = sCards.begin(); i != sCards.end(); ++i)
				{
					for (size_t j = 2; j < NUMBER_OF_CARDS; ++j)
					{
						if (*i == CARDS[j])
						{
							cards.push_back(j);
							break;
						}
					}
				}

				// Get bid
				try
				{
					bid = stoi(sBid);
				}
				catch (exception e)
				{
					continue;
				}

				// Add if input is valid
				if (cards.size() == HAND_SIZE)
				{
					output.push_back(Hand(cards, bid));
				}
			}
			continue;
		}
		break;
	}
	cout << "End of hands input\n\n";
}

template <typename T>
void PrintVector(const vector<T> &input, const char *name, const char* delimiter)
{
	cout << "Start of " << name << "[" << input.size() << "] print\n";
	if (!input.empty())
	{
		typename vector<T>::const_iterator i, end;
		for (i = input.begin(), end = --input.end(); i != end; ++i)
		{
			cout << *i << delimiter;
		}
		cout << *i << "\n";
	}
	cout << "End of " << name << " print\n\n";
}

size_t NewTotalWinnings(const vector<Hand> &input)
{
	size_t sum = 0;
	vector<Hand> hands = input;

	for (vector<Hand>::iterator i = hands.begin(); i != hands.end(); ++i)
	{
		i->JackToJoker();
		i->CalculateTier();
	}

	sort(hands.begin(), hands.end());

	for (size_t i = 0; i < hands.size(); ++i)
	{
		sum += hands[i].Bid * (i + 1);
	}

	return sum;
}

size_t OldTotalWinnings(const vector<Hand> &input)
{
	size_t sum = 0;
	vector<Hand> hands = input;

	sort(hands.begin(), hands.end());

	for (size_t i = 0; i < hands.size(); ++i)
	{
		sum += hands[i].Bid * (i + 1);
	}

	return sum;
}

int main()
{
	cout << "Advent of code 2023\n";
	cout << "Day 7: Camel Cards\n";
	cout << "Program by David Erikssen\n\n";

	vector<Hand> hands;

	InputHands(hands);

	PrintVector(hands, "hands", "\n");

	size_t oldTotalWinnings = OldTotalWinnings(hands);
	size_t newTotalWinnings = NewTotalWinnings(hands);

	cout << "Old total winnings: " << oldTotalWinnings << "\n";
	cout << "New total winnings: " << newTotalWinnings << "\n";

	return 0;
}
