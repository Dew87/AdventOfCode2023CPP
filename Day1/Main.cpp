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

void InputCalibration(vector<string> &vOutput)
{
	cout << "Start of calibration document input (blank line to end)\n";
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
	cout << "End of calibration document input\n\n";
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

int SumOfCalibrationNew(const vector<string> &vInput)
{
	int sum = 0;
	for (int i = 0; i < vInput.size(); ++i)
	{
		string input = vInput[i];

		char first_digit = ' ';
		char last_digit = ' ';
		int first_digit_index = INT_MAX;
		int last_digit_index = INT_MIN;

		// Find first digit
		for (int j = 0; j < input.size(); ++j)
		{
			if ('0' <= input[j] && input[j] <= '9')
			{
				first_digit = input[j];
				first_digit_index = j;
				break;
			}
		}
		for (int j = 0; j < NUMBER_OF_NUMBERS; ++j)
		{
			int index = input.find(NUMBERS[j]);
			if (index != string::npos && index < first_digit_index)
			{
				first_digit = '0' + j;
				first_digit_index = index;
			}
		}

		// Find last digit
		for (int j = input.size() - 1; -1 < j; --j)
		{
			if ('0' <= input[j] && input[j] <= '9')
			{
				last_digit = input[j];
				last_digit_index = j;
				break;
			}
		}
		for (int j = 0; j < NUMBER_OF_NUMBERS; ++j)
		{
			int index = input.rfind(NUMBERS[j]);
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
				cerr << number << " on input[" << i << "] can't be converted to int\n";
			}
		}
		else
		{
			cout << "No number found on input[" << i << "]\n";
		}
	}
	return sum;
}

int SumOfCalibrationOld(const vector<string> &vInput)
{
	int sum = 0;
	for (int i = 0; i < vInput.size(); ++i)
	{
		string input = vInput[i];

		char first_digit = ' ';
		char last_digit = ' ';
		int first_digit_index = INT_MAX;
		int last_digit_index = INT_MIN;

		// Find first digit
		for (int j = 0; j < input.size(); ++j)
		{
			if ('0' <= input[j] && input[j] <= '9')
			{
				first_digit = input[j];
				first_digit_index = j;
				break;
			}
		}

		// Find last digit
		for (int j = input.size() - 1; -1 < j; --j)
		{
			if ('0' <= input[j] && input[j] <= '9')
			{
				last_digit = input[j];
				last_digit_index = j;
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
				cerr << number << " on input[" << i << "] can't be converted to int\n";
			}
		}
		else
		{
			cout << "No number found on input[" << i << "]\n";
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
