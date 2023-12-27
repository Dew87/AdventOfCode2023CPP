#ifndef PART_H
#define PART_H

#include "Vector2i.h"

struct Part
{
	Part(Vector2i position, int number);

	int Number;
	Vector2i Position;
};

#endif
