#ifndef NODE_H
#define NODE_H

#include "Vector2i.h"
#include <vector>

struct Part;

struct Node
{
	Node(Vector2i position, bool isGear);

	bool IsGear;
	Vector2i Position;
	std::vector<Part*> LinkedParts;
};

#endif
