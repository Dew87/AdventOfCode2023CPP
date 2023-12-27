#include "Vector2i.h"

using namespace std;

Vector2i::Vector2i() : X(0), Y(0)
{}

Vector2i::Vector2i(int x, int y) : X(x), Y(y)
{}

bool operator == (const Vector2i a, const Vector2i b)
{
	return a.X == b.X && a.Y == b.Y;
}

Vector2i operator + (const Vector2i a, const Vector2i b)
{
	return Vector2i(a.X + b.X, a.Y + b.Y);
}

ostream& operator << (ostream &o, const Vector2i &vector2I)
{
	return o << vector2I.X << "," << vector2I.Y;
}
