#include "Engine.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void InputSchematic(vector<string> &output)
{
	cout << "Start of schematic input (blank line to end)\n";
	while (true)
	{
		string input;
		getline(cin, input);
		if (input != "")
		{
			output.push_back(input);
			continue;
		}
		break;
	}
	cout << "End of schematic input\n\n";
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

int SumOfGearRatios(const Engine &engine)
{
	int sum = 0;
	for (vector<Node>::const_iterator i = engine.Nodes.begin(); i != engine.Nodes.end(); ++i)
	{
		if ((*i).IsGear)
		{
			int ratio = 1;
			for (vector<Part*>::const_iterator j = (*i).LinkedParts.begin(); j != (*i).LinkedParts.end(); ++j)
			{
				ratio *= (*j)->Number;
			}
			sum += ratio;
		}
	}
	return sum;
}

int SumOfPartNumbers(const Engine &engine)
{
	int sum = 0;
	for (vector<Part*>::const_iterator i = engine.LinkedParts.begin(); i != engine.LinkedParts.end(); ++i)
	{
		sum += (*i)->Number;
	}
	return sum;
}

int main()
{
	cout << "Advent of code 2023\n";
	cout << "Day 3: Gear Ratios\n";
	cout << "Program by David Erikssen\n\n";

	vector<string> schematic;

	InputSchematic(schematic);
	PrintVector(schematic, "schematic", "\n");

	Engine engine(schematic);
	engine.ValidateGears();

	int sumOfPartNumbers = SumOfPartNumbers(engine);
	int sumOfGearRatios = SumOfGearRatios(engine);

	cout << "Sum of part numbers: " << sumOfPartNumbers << "\n";
	cout << "Sum of gear ratios: " << sumOfGearRatios << "\n";

	return 0;
}
