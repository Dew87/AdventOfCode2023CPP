#include "MapEntry.h"
#include "RangeEntry.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void GetChart(vector<string> &output, const vector<size_t> vSeed, const vector<size_t> vSoil, const vector<size_t> vFertilizer, const vector<size_t> vWater, const vector<size_t> vLight, const vector<size_t> vTemperature, const vector<size_t> vHumidity, const vector<size_t> vLocation)
{
	if (vSeed.size() == vSoil.size() && vSeed.size() == vFertilizer.size() && vSeed.size() == vWater.size() && vSeed.size() == vLight.size() && vSeed.size() == vTemperature.size() && vSeed.size() == vHumidity.size() && vSeed.size() == vLocation.size())
	{
		for (size_t i = 0; i < vSeed.size(); ++i)
		{
			ostringstream oss;
			oss << "Seed " << vSeed[i] << ", soil " << vSoil[i] << ", fertilizer " << vFertilizer[i] << ", water " << vWater[i] << ", light " << vLight[i] << ", temperature " << vTemperature[i] << ", humidity " << vHumidity[i] << ", location " << vLocation[i] << ".";
			output.push_back(oss.str());
		}
	}
}

void GetSeedRange(const vector<size_t> &input, vector<RangeEntry> &output)
{
	for (size_t i = 0; i < input.size() - 1; i += 2)
	{
		output.push_back(RangeEntry(input[i], input[i + 1]));
	}
}

void InputMap(vector<MapEntry> &output, const char *name)
{
	size_t index;
	string input;

	cout << "Start of " << name << " input (blank line to end)\n";
	getline(cin, input);
	index = input.find(name);
	if (index != string::npos)
	{
		while (true)
		{
			getline(cin, input);
			if (input != "")
			{
				size_t destination, range, source;

				stringstream stream(input);
				stream >> destination >> source >> range;

				output.push_back(MapEntry(source, destination, range));
				continue;
			}
			break;
		}
	}
	cout << "End of " << name << " input\n\n";
}

void InputSeeds(vector<size_t> &output)
{
	cout << "Start of seeds input (blank line to end)\n";
	while (true)
	{
		size_t index;
		string input;

		getline(cin, input);
		index = input.find("seeds: ");
		if (index != string::npos)
		{
			stringstream stream(input.substr(index + 7));
			size_t number;

			while (stream >> number)
			{
				output.push_back(number);
			}
			continue;
		}
		break;
	}
	cout << "End of seeds input\n\n";
}

void Lookup(const vector<RangeEntry> &input, vector<RangeEntry> &output, const vector<MapEntry> &entries)
{
	for (vector<RangeEntry>::const_iterator i = input.begin(); i != input.end(); ++i)
	{
		vector<RangeEntry> remaining = { *i };
		vector<MapEntry>::const_reverse_iterator k = entries.rbegin();

		for (size_t j = 0; j < remaining.size(); ++j)
		{
			bool overlap = false;

			for (; k != entries.rend(); ++k)
			{
				size_t aStart = remaining[j].Index;
				size_t aEnd = remaining[j].Index + remaining[j].Range - 1;
				size_t bStart = (*k).Source;
				size_t bEnd = (*k).Source + (*k).Range - 1;

				if (aStart <= bEnd && bStart <= aEnd)
				{
					overlap = true;

					size_t oStart = max(aStart, bStart);
					size_t oEnd = min(aEnd, bEnd);

					if (aStart < oStart)
					{
						size_t index = aStart;
						size_t range = oStart - aStart;
						remaining.push_back(RangeEntry(index, range));
					}
					if (oEnd < aEnd)
					{
						size_t index = oEnd + 1;
						size_t range = aEnd - oEnd;
						remaining.push_back(RangeEntry(index, range));
					}

					size_t index = (*k).Destination + oStart - bStart;
					size_t range = oEnd - oStart + 1;

					output.push_back(RangeEntry(index, range));
					break;
				}
			}

			if (!overlap)
			{
				output.push_back(remaining[j]);
			}
		}
	}
}

void Lookup(const vector<size_t> &input, vector<size_t> &output, const vector<MapEntry> &entries)
{
	for (vector<size_t>::const_iterator i = input.begin(); i != input.end(); ++i)
	{
		size_t value = *i;

		for (vector<MapEntry>::const_reverse_iterator j = entries.rbegin(); j != entries.rend(); ++j)
		{
			if (j->Source <= value && value < j->Source + j->Range)
			{
				value += j->Destination - j->Source;
				break;
			}
		}

		output.push_back(value);
	}
}

size_t MinValue(const vector<RangeEntry> &input)
{
	size_t output = SIZE_MAX;

	for (vector<RangeEntry>::const_iterator i = input.begin(); i != input.end(); ++i)
	{
		if ((*i).Index < output)
		{
			output = (*i).Index;
		}
	}

	return output == SIZE_MAX ? 0 : output;
}

size_t MinValue(const vector<size_t> &input)
{
	size_t output = SIZE_MAX;

	for (vector<size_t>::const_iterator i = input.begin(); i != input.end(); ++i)
	{
		if (*i < output)
		{
			output = *i;
		}
	}

	return output == SIZE_MAX ? 0 : output;
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

int main()
{
	cout << "Advent of code 2023\n";
	cout << "Day 5: If You Give A Seed A Fertilizer\n";
	cout << "Program by David Erikssen\n\n";

	vector<size_t> vFertilizer;
	vector<size_t> vHumidity;
	vector<size_t> vLight;
	vector<size_t> vSeed;
	vector<size_t> vSoil;
	vector<size_t> vWater;
	vector<size_t> vTemperature;
	vector<size_t> vLocation;

	vector<MapEntry> vFertilizerToWater;
	vector<MapEntry> vHumidityToLocation;
	vector<MapEntry> vLightToTemperature;
	vector<MapEntry> vSeedToSoil;
	vector<MapEntry> vSoilToFertilizer;
	vector<MapEntry> vTemperatureToHumidity;
	vector<MapEntry> vWaterToLight;

	vector<RangeEntry> vFertilizerRange;
	vector<RangeEntry> vHumidityRange;
	vector<RangeEntry> vLightRange;
	vector<RangeEntry> vSeedRange;
	vector<RangeEntry> vSoilRange;
	vector<RangeEntry> vWaterRange;
	vector<RangeEntry> vTemperatureRange;
	vector<RangeEntry> vLocationRange;

	vector<string> vOldChart;

	InputSeeds(vSeed);
	InputMap(vSeedToSoil, "seed-to-soil map");
	InputMap(vSoilToFertilizer, "soil-to-fertilizer map");
	InputMap(vFertilizerToWater, "fertilizer-to-water map");
	InputMap(vWaterToLight, "water-to-light map");
	InputMap(vLightToTemperature, "light-to-temperature map");
	InputMap(vTemperatureToHumidity, "temperature-to-humidity map");
	InputMap(vHumidityToLocation, "humidity-to-location map");

	GetSeedRange(vSeed, vSeedRange);

	Lookup(vSeed, vSoil, vSeedToSoil);
	Lookup(vSoil, vFertilizer, vSoilToFertilizer);
	Lookup(vFertilizer, vWater, vFertilizerToWater);
	Lookup(vWater, vLight, vWaterToLight);
	Lookup(vLight, vTemperature, vLightToTemperature);
	Lookup(vTemperature, vHumidity, vTemperatureToHumidity);
	Lookup(vHumidity, vLocation, vHumidityToLocation);

	Lookup(vSeedRange, vSoilRange, vSeedToSoil);
	Lookup(vSoilRange, vFertilizerRange, vSoilToFertilizer);
	Lookup(vFertilizerRange, vWaterRange, vFertilizerToWater);
	Lookup(vWaterRange, vLightRange, vWaterToLight);
	Lookup(vLightRange, vTemperatureRange, vLightToTemperature);
	Lookup(vTemperatureRange, vHumidityRange, vTemperatureToHumidity);
	Lookup(vHumidityRange, vLocationRange, vHumidityToLocation);

	GetChart(vOldChart, vSeed, vSoil, vFertilizer, vWater, vLight, vTemperature, vHumidity, vLocation);

	PrintVector(vSeed, "old seeds", "\n");
	PrintVector(vSeedToSoil, "seed-to-soil map", "\n");
	PrintVector(vSoilToFertilizer, "soil-to-fertilizer map", "\n");
	PrintVector(vFertilizerToWater, "fertilizer-to-water map", "\n");
	PrintVector(vWaterToLight, "water-to-light map", "\n");
	PrintVector(vLightToTemperature, "light-to-temperature map", "\n");
	PrintVector(vTemperatureToHumidity, "temperature-to-humidity map", "\n");
	PrintVector(vHumidityToLocation, "humidity-to-location map", "\n");
	PrintVector(vOldChart, "old initial seed chart", "\n");

	PrintVector(vSeedRange, "new seed ranges", "\n");
	PrintVector(vSoilRange, "new soil range", "\n");
	PrintVector(vFertilizerRange, "new fertilizer range", "\n");
	PrintVector(vWaterRange, "new water range", "\n");
	PrintVector(vLightRange, "new light range", "\n");
	PrintVector(vTemperatureRange, "new temperature range", "\n");
	PrintVector(vHumidityRange, "new humidity range", "\n");
	PrintVector(vLocationRange, "new location range", "\n");

	size_t lowestLocationOld = MinValue(vLocation);
	size_t lowestLocationNew = MinValue(vLocationRange);

	cout << "Old lowest location number: " << lowestLocationOld << "\n";
	cout << "New lowest location number: " << lowestLocationNew << "\n";

	return 0;
}
