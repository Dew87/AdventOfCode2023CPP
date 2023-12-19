#ifndef VECTOR2I_H
#define VECTOR2I_H

#include <ostream>

struct Vector2i
{
	Vector2i();
	Vector2i(int x, int y);

	int x;
	int y;
};

bool operator == (const Vector2i a, const Vector2i b);
Vector2i operator + (const Vector2i a, const Vector2i b);

std::ostream& operator << (std::ostream &o, const Vector2i &vector2D);

#endif
