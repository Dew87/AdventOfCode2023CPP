#include "Engine.h"
#include <iostream>

using namespace std;

Engine::Engine()
{}

Engine::Engine(const vector<string> &schematic)
{
	BuildFromSchematic(schematic);
	ValidateGears();
}

Engine::~Engine()
{
	for (size_t i = 0; i < linkedParts.size(); ++i)
	{
		delete linkedParts[i];
	}
	for (size_t i = 0; i < unlinkedParts.size(); ++i)
	{
		delete unlinkedParts[i];
	}

	linkedParts.clear();
	unlinkedParts.clear();
}

void Engine::BuildFromSchematic(const vector<string> &schematic)
{
	vector<Part*> parts;

	for (size_t i = 0; i < schematic.size(); ++i)
	{
		for (size_t j = 0; j < schematic[i].size(); ++j)
		{
			int number = -1;

			switch (schematic[i][j])
			{
			case '.':
				// Empty
				break;

			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				// Start of part number
				size_t end;
				for (end = j; end < schematic[i].size() - 1; ++end)
				{
					char next = schematic[i][end + 1];
					if ('0' <= next && next <= '9')
					{
						continue;
					}
					break;
				}

				try
				{
					number = stoi(schematic[i].substr(j, end - j + 1));
				}
				catch (exception e)
				{
					break;
				}

				parts.push_back(new Part(Vector2i(j, i), number));
				j = end;
				break;

			case '*':
				// Gear
				nodes.push_back(Node(Vector2i(j, i), true));
				break;

			default:
				// Node
				nodes.push_back(Node(Vector2i(j, i), false));
				break;
			}
		}
	}

	// Sort parts
	for (size_t i = 0; i < parts.size(); ++i)
	{
		bool linked = false;
		Vector2i position = parts[i]->position;
		Vector2i target;
		int digits = (int)to_string(parts[i]->number).size();

		// Check neighbors above
		for (int j = position.x - 1; j < (position.x + digits + 1); ++j)
		{
			target.x = j;
			target.y = position.y - 1;
			//cout << "Checking above: " << target << "\n";
			for (size_t k = 0; k < nodes.size(); ++k)
			{
				if (nodes[k].position == target)
				{
					linked = true;
					nodes[k].linkedParts.push_back(parts[i]);
				}
			}
		}

		// Check neighbors below
		for (int j = position.x - 1; j < (position.x + digits + 1); ++j)
		{
			target.x = j;
			target.y = position.y + 1;
			//cout << "Checking below: " << target << "\n";
			for (size_t k = 0; k < nodes.size(); ++k)
			{
				if (nodes[k].position == target)
				{
					linked = true;
					nodes[k].linkedParts.push_back(parts[i]);
				}
			}
		}

		// Check neighbor left
		target.x = position.x - 1;
		target.y = position.y;
		//cout << "Checking left: " << target << "\n";
		for (size_t k = 0; k < nodes.size(); ++k)
		{
			if (nodes[k].position == target)
			{
				linked = true;
				nodes[k].linkedParts.push_back(parts[i]);
			}
		}

		// Check neighbor right
		target.x = position.x + digits;
		target.y = position.y;
		//cout << "Checking right: " << target << "\n";
		for (size_t k = 0; k < nodes.size(); ++k)
		{
			if (nodes[k].position == target)
			{
				linked = true;
				nodes[k].linkedParts.push_back(parts[i]);
			}
		}

		// Place part
		if (linked)
		{
			linkedParts.push_back(parts[i]);
		}
		else
		{
			unlinkedParts.push_back(parts[i]);
		}
	}
}

void Engine::ValidateGears()
{
	for (size_t i = 0; i < nodes.size(); ++i)
	{
		if (nodes[i].isGear)
		{
			nodes[i].isGear = (2 == (int)nodes[i].linkedParts.size());
		}
	}
}
