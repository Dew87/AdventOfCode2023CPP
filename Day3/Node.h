#ifndef NODE_H
#define NODE_H

#include "Vector2i.h"
#include <vector>

struct Part;

struct Node
{
	Node(Vector2i position, bool isGear);

	bool isGear;
	Vector2i position;
	std::vector<Part*> linkedParts;
};

#endif
