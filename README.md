bitcount
========

Fast cross-platform bit counting using intrinsic functions.

Bitcount is a cross-platform implementation of GCC's intrinsic `__builtin_clz`,`__builtin_ctz`, and `__builtin_popcount`. Currently only intrinsic functions are used in VS 2012 (possibly older VS versions as well), and GCC-compatible compilers (including Clang). If Bitcount is used on a system that isn't either of these, it uses a C implementation of these functions as a fallback.

The library exposes three functions which follows the same API as the corresponing GCC intrinsics (which can be found [here][1]). Note that calls to clz and ctz with the value 0 are undefined.
```c
/* Returns the number of leading 0-bits in x, starting at the most significant
   bit position. If v is 0, the result is undefined. */
unsigned int bit_clz(unsigned int v)

/* Returns the number of trailing 0-bits in x, starting at the least significant
   bit position. If v is 0, the result is undefined. */
unsigned int bit_ctz(unsigned int v)

/* Returns the number of 1-bits in v. */
unsigned int bit_popcount(unsigned int v)
```

[1]:http://gcc.gnu.org/onlinedocs/gcc-4.4.2/gcc/Other-Builtins.html
