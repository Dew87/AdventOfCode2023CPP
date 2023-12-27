#ifndef RANGE_ENTRY_H
#define RANGE_ENTRY_H

#include <ostream>

struct RangeEntry
{
	RangeEntry(size_t index, size_t range);

	size_t Index, Range;
};

std::ostream& operator << (std::ostream &o, const RangeEntry &entry);

#endif
