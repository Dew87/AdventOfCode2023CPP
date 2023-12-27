#ifndef MAP_ENTRY_H
#define MAP_ENTRY_H

#include <ostream>

struct MapEntry
{
	MapEntry(size_t source, size_t destination, size_t range);

	size_t Destination, Range, Source;
};

std::ostream& operator << (std::ostream &o, const MapEntry &entry);

#endif
