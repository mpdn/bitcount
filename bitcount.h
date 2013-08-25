#ifndef BITCOUNT_H_
#define BITCOUNT_H_

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(BITCOUNT_NO_AUTODETECT)
	#if defined(__GNUC__) || defined(__clang__)
		#define BITCOUNT_GCC
	#elif defined(_MSC_VER) && (defined(_M_X64) || defined(_M_IX86))
		#define BITCOUNT_VS_X86
	#endif
#endif

#ifdef _MSC_VER
#define BITCOUNT_INLINE static __inline
#else
#define BITCOUNT_INLINE static inline
#endif

#ifdef BITCOUNT_VS_X86
#include <intrin.h>
#pragma intrinsic(_BitScanForward,_BitScanReverse,__popcnt)
#endif

#include <limits.h>
#define BITCOUNT_BITS (sizeof(unsigned int) * CHAR_BIT)

/* General implementations for systems without intrinsics */
unsigned int bit_clz_general(unsigned int);
unsigned int bit_ctz_general(unsigned int);
unsigned int bit_popcount_general(unsigned int);

/* Returns the number of leading 0-bits in x, starting at the most significant
   bit position. If v is 0, the result is undefined. */
BITCOUNT_INLINE unsigned int bit_clz(unsigned int v)
{
	#if defined(BITCOUNT_GCC)
	return __builtin_clz(v);
	#elif defined(BITCOUNT_VS_X86)
	unsigned long result;
	_BitScanReverse(&result, v);
	return BITCOUNT_BITS - 1 - result;
	#else
	return bit_clz_general(v);
	#endif
}

/* Returns the number of trailing 0-bits in x, starting at the least significant
   bit position. If v is 0, the result is undefined. */
BITCOUNT_INLINE unsigned int bit_ctz(unsigned int v)
{
	#if defined(BITCOUNT_GCC)
	return __builtin_ctz(v);
	#elif defined(BITCOUNT_VS_X86)
	unsigned long result;
	_BitScanForward(&result, v);
	return result;
	#else
	return bit_ctz_general(v);
	#endif
}

/* Returns the number of 1-bits in v. */
BITCOUNT_INLINE unsigned int bit_popcount(unsigned int v)
{
	#if defined(BITCOUNT_GCC)
	return __builtin_popcount(v);
	#elif defined(BITCOUNT_VS_X86)
	return __popcnt(v);
	#else
	return bit_popcount_general(v);
	#endif
}

#ifdef __cplusplus
}
#endif

#endif // BITCOUNT_H_

