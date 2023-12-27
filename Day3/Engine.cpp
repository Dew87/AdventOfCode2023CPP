#include "Engine.h"
#include <iostream>

using namespace std;

Engine::Engine(const vector<string> &schematic)
{
	BuildFromSchematic(schematic);
}

Engine::~Engine()
{
	for (vector<Part*>::iterator i = LinkedParts.begin(); i != LinkedParts.end(); ++i)
	{
		delete *i;
	}
	for (vector<Part*>::iterator i = UnlinkedParts.begin(); i != UnlinkedParts.end(); ++i)
	{
		delete *i;
	}

	LinkedParts.clear();
	UnlinkedParts.clear();
}

void Engine::BuildFromSchematic(const vector<string> &schematic)
{
	vector<Part*> parts;

	for (size_t i = 0; i < schematic.size(); ++i)
	{
		for (size_t j = 0; j < schematic[i].size(); ++j)
		{
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
				int number;
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
				Nodes.push_back(Node(Vector2i(j, i), true));
				break;

			default:
				// Node
				Nodes.push_back(Node(Vector2i(j, i), false));
				break;
			}
		}
	}

	// Sort parts
	for (vector<Part*>::iterator i = parts.begin(); i != parts.end(); ++i)
	{
		bool linked = false;
		Vector2i position = (*i)->Position;
		Vector2i target;
		int digits = (int)to_string((*i)->Number).size();

		// Check neighbors above
		for (int j = position.X - 1; j <= (position.X + digits); ++j)
		{
			target.X = j;
			target.Y = position.Y - 1;
			for (vector<Node>::iterator k = Nodes.begin(); k != Nodes.end(); ++k)
			{
				if ((*k).Position == target)
				{
					linked = true;
					(*k).LinkedParts.push_back(*i);
				}
			}
		}

		// Check neighbors below
		for (int j = position.X - 1; j <= (position.X + digits); ++j)
		{
			target.X = j;
			target.Y = position.Y + 1;
			for (vector<Node>::iterator k = Nodes.begin(); k != Nodes.end(); ++k)
			{
				if ((*k).Position == target)
				{
					linked = true;
					(*k).LinkedParts.push_back(*i);
				}
			}
		}

		// Check neighbor left
		target.X = position.X - 1;
		target.Y = position.Y;
		for (vector<Node>::iterator k = Nodes.begin(); k != Nodes.end(); ++k)
		{
			if ((*k).Position == target)
			{
				linked = true;
				(*k).LinkedParts.push_back(*i);
			}
		}

		// Check neighbor right
		target.X = position.X + digits;
		target.Y = position.Y;
		for (vector<Node>::iterator k = Nodes.begin(); k != Nodes.end(); ++k)
		{
			if ((*k).Position == target)
			{
				linked = true;
				(*k).LinkedParts.push_back(*i);
			}
		}

		// Place part
		if (linked)
		{
			LinkedParts.push_back(*i);
		}
		else
		{
			UnlinkedParts.push_back(*i);
		}
	}
}

void Engine::ValidateGears()
{
	for (vector<Node>::iterator i = Nodes.begin(); i != Nodes.end(); ++i)
	{
		if ((*i).IsGear)
		{
			(*i).IsGear = (2 == (int)(*i).LinkedParts.size());
		}
	}
}
