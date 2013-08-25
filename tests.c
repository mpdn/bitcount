#include "bitcount.h"
#include <stdio.h>

#define TEST1(func, input, expected)  { \
		int r = func(input);     \
		if (r != expected) {           \
		fprintf(stderr, #func "(" #input ") returned %d (expected " #expected ")\n", r); \
		status++; } }

#define TEST(func, input, expected)  \
	TEST1(bit_##func,input,expected); \
	TEST1(bit_##func##_general,input,expected);

int main(int argc, char **argv)
{
	int status = 0;
	
	TEST(ctz, 2, 1);
	TEST(ctz, 3, 0);
	TEST(ctz, 0x80000000, 31);
	TEST(ctz, 0x1000, 12);
	TEST(ctz, UINT_MAX, 0);
	TEST(clz, 1, 31);
	TEST(clz, 4, 29);
	TEST(clz, 0x80000000, 0);
	TEST(clz, 0x1000, 19);
	TEST(clz, UINT_MAX, 0);
	TEST(popcount, 0x1, 1);
	TEST(popcount, 0x10, 1);
	TEST(popcount, 0x101001, 3);
	TEST(popcount, 3, 2);
	TEST(popcount, UINT_MAX, BITCOUNT_BITS);
	TEST(popcount, 0, 0);
	return status;
}
