#include "Engine.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void InputSchematic(vector<string> &vOutput)
{
	cout << "Start of schematic input (blank line to end)\n";
	while (true)
	{
		string input;
		getline(cin, input);
		if (input != "")
		{
			vOutput.push_back(input);
			continue;
		}
		break;
	}
	cout << "End of schematic input\n\n";
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

int SumOfGearRatios(const Engine &engine)
{
	int sum = 0;
	for (size_t i = 0; i < engine.nodes.size(); ++i)
	{
		if (engine.nodes[i].isGear)
		{
			int ratio = 1;
			for (size_t j = 0; j < engine.nodes[i].linkedParts.size(); ++j)
			{
				ratio *= engine.nodes[i].linkedParts[j]->number;
			}
			sum += ratio;
		}
	}
	return sum;
}

int SumOfPartNumbers(const Engine &engine)
{
	int sum = 0;
	for (size_t i = 0; i < engine.linkedParts.size(); ++i)
	{
		sum += engine.linkedParts[i]->number;
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

	int sumOfPartNumbers = SumOfPartNumbers(engine);
	int sumOfGearRatios = SumOfGearRatios(engine);

	cout << "Sum of part numbers: " << sumOfPartNumbers << "\n";
	cout << "Sum of gear ratios: " << sumOfGearRatios << "\n";

	return 0;
}
