
#include "core3.h"
#include "tools3.h"



namespace KHEOPS
{



void FillIndexesArray( std::vector<size_t>& inIndexes, size_t inFirstIndex, size_t inCount)
{
	inIndexes.resize( inCount);
	size_t pos = 0;
	while (pos < inCount)
	{
		inIndexes[pos] = inFirstIndex;
		++inFirstIndex;
		++pos;
	}
}



} // namespace KHEOPS