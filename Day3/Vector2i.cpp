#include "Vector2i.h"

using namespace std;

Vector2i::Vector2i() : x(0), y(0)
{}

Vector2i::Vector2i(int x, int y) : x(x), y(y)
{}

bool operator == (const Vector2i a, const Vector2i b)
{
	return a.x == b.x && a.y == b.y;
}

Vector2i operator + (const Vector2i a, const Vector2i b)
{
	return Vector2i(a.x + b.x, a.y + b.y);
}

ostream& operator << (ostream &o, const Vector2i &vector2I)
{
	return o << vector2I.x << "," << vector2I.y;
}
