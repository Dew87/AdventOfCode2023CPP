#include "Card.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> Split(const string &input, const string &delimiter);

void CalculateMatchingNumbers(vector<Card> &cards)
{
	for (size_t i = 0; i < cards.size(); ++i)
	{
		cards[i].CalculateMatchingNumbers();
	}
}

void InputCards(vector<Card> &vOutput)
{
	cout << "Start of cards input (blank line to end)\n";
	while (true)
	{
		string input;
		getline(cin, input);

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
					break;
				}
			}

			// Separate numbers and winning numbers
			index = s2.find(" | ");
			string s21 = s2.substr(0, index);
			string s22 = s2.substr(index + 3);
			vector<string> sWinningNumbers = Split(s21, " ");
			vector<string> sNumbers = Split(s22, " ");

			// Numbers
			for (size_t i = 0; i < sNumbers.size(); ++i)
			{
				int number = 0;
				try
				{
					number = stoi(sNumbers[i]);
				}
				catch (exception e)
				{
					continue;
				}
				numbers.push_back(number);
			}

			// Winning numbers
			for (size_t i = 0; i < sWinningNumbers.size(); ++i)
			{
				int number = 0;
				try
				{
					number = stoi(sWinningNumbers[i]);
				}
				catch (exception e)
				{
					continue;
				}
				winningNumbers.push_back(number);
			}

			vOutput.push_back(Card(id, numbers, winningNumbers));
			continue;
		}
		break;
	}
	cout << "End of cards input\n\n";
}

template <typename T>
void PrintVector(const vector<T> &vInput, const char *vName, const char* separation)
{
	cout << "Start of " << vName << "[" << vInput.size() << "] print\n";
	if (0 < vInput.size())
	{
		for (size_t i = 0; i < vInput.size() - 1; i++)
		{
			cout << vInput[i] << separation;
		}
		cout << vInput[vInput.size() - 1] << "\n";
	}
	cout << "End of " << vName << " print\n\n";
}

vector<string> Split(const string &input, const string &delimiter)
{
	vector<string> output;

	string s = input;
	for (size_t i = s.find(delimiter); i != string::npos; i = s.find(delimiter))
	{
		output.push_back(s.substr(0, i));
		s = s.substr(i + delimiter.size());
	}
	output.push_back(s);

	return output;
}

int SumOfCardScores(const vector<Card> &cards)
{
	int sum = 0;

	for (size_t i = 0; i < cards.size(); ++i)
	{
		if (0 < cards[i].matchingNumbers)
		{
			int score = 1;
			for (size_t j = 1; j < cards[i].matchingNumbers; ++j)
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
		for (size_t j = 1; j < (size_t)(cards[i].matchingNumbers + 1) && (i + j) < cards.size(); ++j)
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
