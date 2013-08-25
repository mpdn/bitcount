#include "bitcount.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*
 All general implementations are heavily based on the following webpage:
 http://graphics.stanford.edu/~seander/bithacks.html
*/

unsigned int bit_clz_general(unsigned int v)
{
	if (BITCOUNT_BITS == 32)
	{
		//see http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogDeBruijn

		static const int MultiplyDeBruijnBitPosition[32] = 
		{
		  0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
		  8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
		};

		v |= v >> 1; // first round down to one less than a power of 2 
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;

		return BITCOUNT_BITS - 1 - MultiplyDeBruijnBitPosition[(uint32_t)(v * 0x07C4ACDDU) >> 27];
	}
	else
	{
		//see http://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious
		unsigned int r = 0; // r will be lg(v)
		while (v >>= 1) // unroll for more speed...
			r++;
		return r;
	}
}

unsigned int bit_ctz_general(unsigned int v)
{
	//see http://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup
	static const int MultiplyDeBruijnBitPosition[32] = 
	{
		0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8, 
		31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
	};
	return MultiplyDeBruijnBitPosition[((uint32_t)((v & -(int)v) * 0x077CB531U)) >> 27];
}

unsigned int bit_popcount_general(unsigned int v)
{
	if (BITCOUNT_BITS == 32)
	{
		//see http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
		unsigned int c;
		v = v - ((v >> 1) & 0x55555555);                    // reuse input as temporary
		v = (v & 0x33333333) + ((v >> 2) & 0x33333333);     // temp
		c = ((v + (v >> 4) & 0xF0F0F0F) * 0x1010101) >> 24; // count
		return c;
	}
	else
	{
		//see http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan
		unsigned int c; // c accumulates the total bits set in v
		for (c = 0; v; c++)
			v &= v - 1; // clear the least significant bit set
		return c;
	}
}

#ifdef __cplusplus
}
#endif