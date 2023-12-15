#include "Game.h"
#include "Color.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string &input, const string &delimiter)
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

void InputGames(vector<Game> &vOutput)
{
	cout << "Start of games input (blank line to end)\n";
	while (true)
	{
		string input;
		getline(cin, input);

		size_t index = input.find(": ");
		if (index != string::npos)
		{
			int id = 0;

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
					break;
				}
			}

			// Initialize game
			Game game(id);

			// hands
			vector<string> sHands = split(s2, "; ");
			for (size_t i = 0; i < sHands.size(); ++i)
			{
				vector<int> colors(NUMBER_OF_COLORS);

				vector<string> sColors = split(sHands[i], ", ");
				for (size_t j = 0; j < sColors.size(); ++j)
				{
					index = sColors[j].find(" ");
					if (index != string::npos)
					{
						int number = 0;
						try
						{
							number = stoi(sColors[j].substr(0, index));
						}
						catch (exception e)
						{
							continue;
						}

						string color = sColors[j].substr(index + 1);
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

				game.hands.push_back(Hand(colors));
			}

			vOutput.push_back(game);
			continue;
		}
		break;
	}
	cout << "End of games input\n\n";
}

int SumOfIDforValidGames(const vector<Game> games, const vector<int> &vProvided)
{
	int sum = 0;

	for (size_t i = 0; i < games.size(); ++i)
	{
		vector<int> needed(NUMBER_OF_COLORS);

		for (size_t j = 0; j < games[i].hands.size(); ++j)
		{
			for (size_t k = 0; k < NUMBER_OF_COLORS; ++k)
			{
				if (needed[k] < games[i].hands[j].colors[k])
				{
					needed[k] = games[i].hands[j].colors[k];
				}
			}
		}

		bool valid = true;
		for (size_t j = 0; j < NUMBER_OF_COLORS; ++j)
		{
			if (vProvided[j] < needed[j])
			{
				valid = false;
				break;
			}
		}
		if (valid)
		{
			sum += games[i].ID;
		}
	}

	return sum;
}

int SumOfPowerForMinimumSetsOfCubes(const vector<Game> games)
{
	int sum = 0;

	for (size_t i = 0; i < games.size(); ++i)
	{
		vector<int> needed(NUMBER_OF_COLORS);

		for (size_t j = 0; j < games[i].hands.size(); ++j)
		{
			for (size_t k = 0; k < NUMBER_OF_COLORS; ++k)
			{
				if (needed[k] < games[i].hands[j].colors[k])
				{
					needed[k] = games[i].hands[j].colors[k];
				}
			}
		}

		int power = 1;
		for (size_t j = 0; j < NUMBER_OF_COLORS; ++j)
		{
			power *= needed[j];
		}
		sum += power;
	}
	return sum;
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
