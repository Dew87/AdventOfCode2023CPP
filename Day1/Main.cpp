#include <iostream>
#include <string>
#include <vector>

using namespace std;

const size_t NUMBER_OF_NUMBERS = 10;

const char* NUMBERS[] =
{
	"zero",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine"
};

void InputCalibration(vector<string> &output)
{
	cout << "Start of calibration document input (blank line to end)\n";
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
	cout << "End of calibration document input\n\n";
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

int SumOfCalibrationNew(const vector<string> &input)
{
	int sum = 0;
	for (vector<string>::const_iterator i = input.begin(); i != input.end(); ++i)
	{
		char first_digit = ' ';
		char last_digit = ' ';
		int first_digit_index = INT_MAX;
		int last_digit_index = INT_MIN;

		// Find first digit
		for (int j = 0; j < (*i).size(); ++j)
		{
			if ('0' <= (*i)[j] && (*i)[j] <= '9')
			{
				first_digit = (*i)[j];
				first_digit_index = j;
				break;
			}
		}
		for (int j = 0; j < NUMBER_OF_NUMBERS; ++j)
		{
			int index = (*i).find(NUMBERS[j]);
			if (index != string::npos && index < first_digit_index)
			{
				first_digit = '0' + j;
				first_digit_index = index;
			}
		}

		// Find last digit
		for (int j = (*i).size() - 1; 0 <= j; --j)
		{
			if ('0' <= (*i)[j] && (*i)[j] <= '9')
			{
				last_digit = (*i)[j];
				last_digit_index = j;
				break;
			}
		}
		for (int j = 0; j < NUMBER_OF_NUMBERS; ++j)
		{
			int index = (*i).rfind(NUMBERS[j]);
			if (index != string::npos && last_digit_index < index)
			{
				last_digit = '0' + j;
				last_digit_index = index;
			}
		}

		// Convert string to number
		if (first_digit != ' ' && last_digit != ' ')
		{
			string number;
			number.push_back(first_digit);
			number.push_back(last_digit);

			try
			{
				int value = stoi(number);
				sum += value;
			}
			catch (exception e)
			{
				cerr << " Can't be converted to int: " << number << "\n";
			}
		}
		else
		{
			cout << "No number found: " << *i << "\n";
		}
	}
	return sum;
}

int SumOfCalibrationOld(const vector<string> &input)
{
	int sum = 0;
	for (vector<string>::const_iterator i = input.begin(); i != input.end(); ++i)
	{
		char first_digit = ' ';
		char last_digit = ' ';

		// Find first digit
		for (string::const_iterator j = (*i).begin(); j != (*i).end(); ++j)
		{
			if ('0' <= *j && *j <= '9')
			{
				first_digit = *j;
				break;
			}
		}

		// Find last digit
		for (string::const_reverse_iterator j = (*i).rbegin(); j != (*i).rend(); ++j)
		{
			if ('0' <= *j && *j <= '9')
			{
				last_digit = *j;
				break;
			}
		}

		// Convert string to number
		if (first_digit != ' ' && last_digit != ' ')
		{
			string number;
			number.push_back(first_digit);
			number.push_back(last_digit);

			try
			{
				int value = stoi(number);
				sum += value;
			}
			catch (exception e)
			{
				cerr << "Can't be converted to int: " << number << "\n";
			}
		}
		else
		{
			cout << "No number found: " << *i << "\n";
		}
	}
	return sum;
}

int main()
{
	cout << "Advent of code 2023\n";
	cout << "Day 1: Trebuchet?!\n";
	cout << "Program by David Erikssen\n\n";

	vector<string> calibration;

	InputCalibration(calibration);
	PrintVector(calibration, "calibration", "\n");

	int sumOld = SumOfCalibrationOld(calibration);
	int sumNew = SumOfCalibrationNew(calibration);

	cout << "Old sum of calibration values: " << sumOld << "\n";
	cout << "New sum of calibration values: " << sumNew << "\n";

	return 0;
}
