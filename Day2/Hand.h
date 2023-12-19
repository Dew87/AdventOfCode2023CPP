#ifndef HAND_H
#define HAND_H

#include <ostream>
#include <vector>

struct Hand
{
	Hand(const std::vector<int> &colors);

	std::vector<int> colors;
};

std::ostream& operator << (std::ostream &o, const Hand &hand);

#endif
