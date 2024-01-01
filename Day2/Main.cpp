#include "Color.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> Split(const string &input, const string &delimiter);

void InputGames(vector<Game> &output)
{
	cout << "Start of games input (blank line to end)\n";
	while (true)
	{
		string input;
		getline(cin, input);
		if (input != "")
		{
			size_t index;
			index = input.find(": ");
			if (index != string::npos)
			{
				int id;
				vector<Hand> hands;

				string s1 = input.substr(0, index);
				string s2 = input.substr(index + 2);

				// Get game ID
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

					// Get hands
					vector<string> vStringHands = Split(s2, "; ");
					for (vector<string>::iterator i = vStringHands.begin(); i != vStringHands.end(); ++i)
					{
						vector<int> colors(NUMBER_OF_COLORS, 0);
						vector<string> vStringColors = Split(*i, ", ");

						for (vector<string>::iterator j = vStringColors.begin(); j != vStringColors.end(); ++j)
						{
							index = (*j).find(" ");
							if (index != string::npos)
							{
								int number;
								try
								{
									number = stoi((*j).substr(0, index));
								}
								catch (exception e)
								{
									continue;
								}

								string color = (*j).substr(index + 1);
								for (size_t k = 0; k < NUMBER_OF_COLORS; ++k)
								{
									if (color == COLORS[k])
									{
										colors[k] = number;
										break;
									}
								}
							}
						}

						hands.push_back(Hand(colors));
					}

					output.push_back(Game(id, hands));
				}
			}
			continue;
		}
		break;
	}
	cout << "End of games input\n\n";
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

int SumOfIDforValidGames(const vector<Game> games, const vector<int> &provided)
{
	int sum = 0;

	for (vector<Game>::const_iterator i = games.begin(); i != games.end(); ++i)
	{
		vector<int> needed(NUMBER_OF_COLORS);

		for (vector<Hand>::const_iterator j = (*i).Hands.begin(); j != (*i).Hands.end(); ++j)
		{
			for (size_t k = 0; k < NUMBER_OF_COLORS; ++k)
			{
				if (needed[k] < (*j).Colors[k])
				{
					needed[k] = (*j).Colors[k];
				}
			}
		}

		bool valid = true;
		for (size_t j = 0; j < NUMBER_OF_COLORS; ++j)
		{
			if (provided[j] < needed[j])
			{
				valid = false;
				break;
			}
		}
		if (valid)
		{
			sum += (*i).ID;
		}
	}

	return sum;
}

int SumOfPowerForMinimumSetsOfCubes(const vector<Game> games)
{
	int sum = 0;

	for (vector<Game>::const_iterator i = games.begin(); i != games.end(); ++i)
	{
		vector<int> needed(NUMBER_OF_COLORS);

		for (vector<Hand>::const_iterator j = (*i).Hands.begin(); j != (*i).Hands.end(); ++j)
		{
			for (size_t k = 0; k < NUMBER_OF_COLORS; ++k)
			{
				if (needed[k] < (*j).Colors[k])
				{
					needed[k] = (*j).Colors[k];
				}
			}
		}

		int power = 1;
		for (vector<int>::iterator j = needed.begin(); j < needed.end(); ++j)
		{
			power *= *j;
		}
		sum += power;
	}

	return sum;
}

int main()
{
	cout << "Advent of code 2023\n";
	cout << "Day 2: Cube Conundrum\n";
	cout << "Program by David Erikssen\n\n";

	vector<Game> games;

	InputGames(games);
	PrintVector(games, "games", "\n");

	int sumOfIDforValidGames = SumOfIDforValidGames(games, { 12, 13, 14 });
	int sumOfPowerForMinimumSetsOfCubes = SumOfPowerForMinimumSetsOfCubes(games);

	cout << "Sum of ID for valid games: " << sumOfIDforValidGames << "\n";
	cout << "Sum of power for minimum sets of cubes: " << sumOfPowerForMinimumSetsOfCubes << "\n";

	return 0;
}
