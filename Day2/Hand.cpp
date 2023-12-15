#include "Hand.hpp"
#include "Color.hpp"

using namespace std;

Hand::Hand(const vector<int> &colors) : colors(colors)
{}

ostream& operator << (ostream &o, const Hand &hand)
{
	bool empty = true;
	for (size_t i = 0; i < NUMBER_OF_COLORS; ++i)
	{
		int number = hand.colors[i];
		if (0 < number)
		{
			if (!empty) { o << ", "; }
			o << number << " " << COLORS[i];
			empty = false;
		}
	}
	return o;
}
