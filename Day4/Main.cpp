#include "Card.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> Split(const string &input, const string &delimiter);

void CalculateMatchingNumbers(vector<Card> &cards)
{
	for (vector<Card>::iterator i = cards.begin(); i != cards.end(); ++i)
	{
		(*i).CalculateMatchingNumbers();
	}
}

void InputCards(vector<Card> &output)
{
	cout << "Start of cards input (blank line to end)\n";
	while (true)
	{
		string input;
		getline(cin, input);
		if (input != "")
		{
			size_t index = input.find(": ");
			if (index != string::npos)
			{
				int id = 0;
				vector<int> numbers;
				vector<int> winningNumbers;

				// Separate card ID from numbers
				string s1 = input.substr(0, index);
				string s2 = input.substr(index + 2);

				// Game ID
				index = s1.find(" ");
				if (index != string::npos)
				{
					try
					{
						id = stoi(s1.substr(index + 1));
					}
					catch (exception e)
					{
						continue;
					}
				}

				// Separate numbers and winning numbers
				index = s2.find(" | ");
				string s21 = s2.substr(0, index);
				string s22 = s2.substr(index + 3);
				vector<string> sWinningNumbers = Split(s21, " ");
				vector<string> sNumbers = Split(s22, " ");

				// Numbers
				for (vector<string>::iterator i = sNumbers.begin(); i != sNumbers.end(); ++i)
				{
					int number = 0;
					try
					{
						number = stoi(*i);
					}
					catch (exception e)
					{
						continue;
					}
					numbers.push_back(number);
				}

				// Winning numbers
				for (vector<string>::iterator i = sWinningNumbers.begin(); i != sWinningNumbers.end(); ++i)
				{
					int number = 0;
					try
					{
						number = stoi(*i);
					}
					catch (exception e)
					{
						continue;
					}
					winningNumbers.push_back(number);
				}

				output.push_back(Card(id, numbers, winningNumbers));
			}
			continue;
		}
		break;
	}
	cout << "End of cards input\n\n";
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

vector<string> Split(const string &input, const string &delimiter)
{
	vector<string> output;

	string remaining = input;
	for (size_t i = remaining.find(delimiter); i != string::npos; i = remaining.find(delimiter))
	{
		output.push_back(remaining.substr(0, i));
		remaining = remaining.substr(i + delimiter.size());
	}
	output.push_back(remaining);

	return output;
}

int SumOfCardScores(const vector<Card> &cards)
{
	int sum = 0;

	for (vector<Card>::const_iterator i = cards.begin(); i != cards.end(); ++i)
	{
		if (0 < (*i).MatchingNumbers)
		{
			int score = 1;
			for (size_t j = 1; j < (*i).MatchingNumbers; ++j)
			{
				score *= 2;
			}
			sum += score;
		}
	}

	return sum;
}

int SumOfScratchcards(const vector<Card> &cards)
{
	int sum = 0;
	vector<int> numberOfCards(cards.size(), 1);

	for (size_t i = 0; i < cards.size(); ++i)
	{
		for (size_t j = 1; j < (size_t)(cards[i].MatchingNumbers + 1) && (i + j) < cards.size(); ++j)
		{
			numberOfCards[i + j] += numberOfCards[i];
		}
		sum += numberOfCards[i];
	}

	return sum;
}

int main()
{
	cout << "Advent of code 2023\n";
	cout << "Day 4: Scratchcards\n";
	cout << "Program by David Erikssen\n\n";

	vector<Card> cards;

	InputCards(cards);
	CalculateMatchingNumbers(cards);
	PrintVector(cards, "cards", "\n");

	int sumOfCardScores = SumOfCardScores(cards);
	int sumOfScratchcards = SumOfScratchcards(cards);

	cout << "Sum of card scores: " << sumOfCardScores << "\n";
	cout << "Total number of scratchcards: " << sumOfScratchcards << "\n";

	return 0;
}
