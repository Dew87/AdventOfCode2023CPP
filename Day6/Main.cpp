#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

size_t GetNumber(const vector<size_t> &input)
{
	size_t number = 0;
	stringstream stream;

	for (vector<size_t>::const_iterator i = input.begin(); i != input.end(); ++i)
	{
		stream << *i;
	}

	stream >> number;
	return number;
}

void Input(vector<size_t> &output, string name)
{

	size_t index;
	string input;

	cout << "Start of " << name << " input (blank line to end)\n";
	getline(cin, input);
	index = input.find(name);
	if (index != string::npos)
	{
		stringstream stream(input.substr(index + name.size() + 1));
		size_t number;

		while (stream >> number)
		{
			output.push_back(number);
		}
	}
	cout << "End of " << name << " input\n\n";
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

size_t Product(const vector<size_t> &input)
{
	size_t product = 1;

	for (vector<size_t>::const_iterator i = input.begin(); i != input.end(); ++i)
	{
		product *= *i;
	}

	return product;
}

void WaitForIt(const vector<size_t> &vTime, const vector<size_t> &vDistance, vector<size_t> &output)
{
	if (vTime.size() != vDistance.size())
	{
		cout << "Mismatch time[" << vTime.size() << "] and distance[" << vDistance.size() << "] sizes\n";
		return;
	}

	for (size_t i = 0; i < vTime.size(); ++i)
	{
		size_t sum = 0;
		size_t time = vTime[i];
		size_t record = vDistance[i];

		for (size_t j = 0; j <= time; ++j)
		{
			size_t chargeTime = j;
			size_t travelTime = time - j;
			size_t distance = chargeTime * travelTime;

			if (record < distance)
			{
				++sum;
			}
		}

		output.push_back(sum);
	}
}

int main()
{
	cout << "Advent of code 2023\n";
	cout << "Day 6: Wait For It\n";
	cout << "Program by David Erikssen\n\n";

	vector<size_t> vOldTime;
	vector<size_t> vOldDistance;
	vector<size_t> vOldBeat;

	vector<size_t> vNewTime;
	vector<size_t> vNewDistance;
	vector<size_t> vNewBeat;

	Input(vOldTime, "Time");
	Input(vOldDistance, "Distance");

	vNewTime.push_back(GetNumber(vOldTime));
	vNewDistance.push_back(GetNumber(vOldDistance));

	WaitForIt(vOldTime, vOldDistance, vOldBeat);
	WaitForIt(vNewTime, vNewDistance, vNewBeat);

	PrintVector(vOldTime, "Time", "\n");
	PrintVector(vOldDistance, "Distance", "\n");
	PrintVector(vOldBeat, "times previous records beaten", "\n");

	PrintVector(vNewTime, "New time", "\n");
	PrintVector(vNewDistance, "New distance", "\n");
	PrintVector(vNewBeat, "New times previous records beaten", "\n");

	size_t oldBeatProduct = Product(vOldBeat);
	size_t newBeatProduct = Product(vNewBeat);

	cout << "Old product of times previous records beaten: " << oldBeatProduct << "\n";
	cout << "New product of times previous records beaten: " << newBeatProduct << "\n";

	return 0;
}
