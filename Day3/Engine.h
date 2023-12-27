#ifndef ENGINE_H
#define ENGINE_H

#include "Node.h"
#include "Part.h"
#include <vector>
#include <string>

struct Engine
{
	Engine(const std::vector<std::string> &schematic);
	~Engine();

	void BuildFromSchematic(const std::vector<std::string> &schematic);
	void ValidateGears();

	std::vector<Node> Nodes;
	std::vector<Part*> LinkedParts;
	std::vector<Part*> UnlinkedParts;
};

#endif
