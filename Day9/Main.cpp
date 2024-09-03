#include <deque>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void Input(deque<deque<int>> &output)
{
	cout << "Start of input (blank line to end)\n";
	while (true)
	{
		string input;
		getline(cin, input);
		if (input != "")
		{
			int number;
			stringstream stream(input);
			deque<int> numbers;

			while (stream >> number)
			{
				numbers.push_back(number);
			}

			output.push_back(numbers);
			continue;
		}
		break;
	}
	cout << "End of input\n\n";
}

void Prediction(const deque<deque<int>> &input, deque<int> &outputNext, deque<int> &outputPrevious)
{
	for (deque<deque<int>>::const_iterator itr = input.begin(); itr != input.end(); ++itr)
	{
		deque<deque<int>> data = { *itr };
		bool all_zero = false;
		size_t depth = 0;

		// Iterate until difference is all zero
		while (!all_zero)
		{
			all_zero = true;
			data.push_back(deque<int>{});

			for (size_t i = 0; i < data[depth].size() - 1; ++i)
			{
				int difference = data[depth][i + 1] - data[depth][i];
				data[depth + 1].push_back(difference);
				if (difference != 0)
				{
					all_zero = false;
				}
			}

			++depth;
		}

		// Input prediction for all depths
		data[depth].push_back(0);
		data[depth].push_front(0);
		for (; 0 < depth; --depth)
		{
			// Next
			deque<int>::reverse_iterator ni = data[depth].rbegin();
			deque<int>::reverse_iterator nj = data[depth - 1].rbegin();
			if (ni != data[depth].rend() && nj != data[depth - 1].rend())
			{
				data[depth - 1].push_back(*ni + *nj);
			}

			// Previous
			deque<int>::iterator pi = data[depth].begin();
			deque<int>::iterator pj = data[depth - 1].begin();
			if (pi != data[depth].end() && pj != data[depth - 1].end())
			{
				data[depth - 1].push_front(*pj - *pi);
			}
		}

		// Extract prediction of next value at depth 0 to output
		deque<int>::reverse_iterator ni = data[0].rbegin();
		if (ni != data[0].rend())
		{
			outputNext.push_back(*ni);
		}

		// Extract prediction of previous value at depth 0 to output
		deque<int>::iterator pi = data[0].begin();
		if (pi != data[0].end())
		{
			outputPrevious.push_front(*pi);
		}
	}
}

template <typename T>
void PrintDeque(const deque<T> &input, const char *name, const char* delimiter)
{
	cout << "Start of " << name << "[" << input.size() << "] print\n";
	if (!input.empty())
	{
		typename deque<T>::const_iterator i, end;
		for (i = input.begin(), end = --input.end(); i != end; ++i)
		{
			cout << *i << delimiter;
		}
		cout << *i << "\n";
	}
	cout << "End of " << name << " print\n\n";
}

template <typename T>
void PrintDeque(const deque<deque<T>> &input, const char *name, const char* innerDelimiter, const char* outerDelimiter)
{
	cout << "Start of " << name << "[" << input.size() << "] print\n";
	if (!input.empty())
	{
		typename deque<deque<T>>::const_iterator outer, outerEnd;
		for (outer = input.begin(), outerEnd = --input.end(); outer != outerEnd; ++outer)
		{
			if (!outer->empty())
			{
				typename deque<T>::const_iterator inner, innerEnd;
				for (inner = outer->begin(), innerEnd = --outer->end(); inner != innerEnd; ++inner)
				{
					cout << *inner << innerDelimiter;
				}
				cout << *inner << outerDelimiter;
			}
		}
		if (!outer->empty())
		{
			typename deque<T>::const_iterator inner, innerEnd;
			for (inner = outer->begin(), innerEnd = --outer->end(); inner != innerEnd; ++inner)
			{
				cout << *inner << innerDelimiter;
			}
			cout << *inner << "\n";
		}
	}
	cout << "End of " << name << " print\n\n";
}

int Sum(const deque<int> &input)
{
	int output = 0;

	for (deque<int>::const_iterator i = input.begin(); i != input.end(); ++i)
	{
		output += *i;
	}

	return output;
}

int main()
{
	cout << "Advent of code 2023\n";
	cout << "Day 9: Mirage Maintenance\n";
	cout << "Program by David Erikssen\n\n";
	
	deque<deque<int>> input;
	deque<int> predictionNext;
	deque<int> predictionPrevious;

	Input(input);
	PrintDeque(input, "input", " ", "\n");

	Prediction(input, predictionNext, predictionPrevious);
	PrintDeque(predictionNext, "prediction next", "\n");
	PrintDeque(predictionPrevious, "prediction previous", "\n");

	int sumNext = Sum(predictionNext);
	int sumPrevious = Sum(predictionPrevious);

	cout << "Sum of extrapolated next values: " << sumNext << "\n";
	cout << "Sum of extrapolated previous values: " << sumPrevious << "\n";

	return 0;
}
