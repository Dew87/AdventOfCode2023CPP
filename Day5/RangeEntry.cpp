#include "RangeEntry.h"

RangeEntry::RangeEntry(size_t index, size_t range) : Index(index), Range(range)
{}

std::ostream& operator << (std::ostream &o, const RangeEntry &entry)
{
	o << entry.Index << " | " << entry.Range;
	return o;
}
