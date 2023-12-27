#include "MapEntry.h"

MapEntry::MapEntry(size_t source, size_t destination, size_t range) : Source(source), Destination(destination), Range(range)
{}

std::ostream& operator << (std::ostream &o, const MapEntry &entry)
{
	o << entry.Source << " => " << entry.Destination << " | " << entry.Range;
	return o;
}
