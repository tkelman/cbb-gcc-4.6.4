#ifdef SHARED
#ifndef __MIDIPIX
#define __divtc3 __divtc3_shared
#endif
#endif

#define L_divtc3
#include "libgcc2.c"

#ifdef SHARED
#ifndef __MIDIPIX
#undef __divtc3
extern __typeof__ (__divtc3_shared) __divtc3_compat __attribute__((alias ("__divtc3_shared")));
#endif

#if !defined(_WIN32) && !defined(__MIDIPIX)
asm (".symver __divtc3_compat,__divtc3@GCC_4.0.0");
asm (".symver __divtc3_shared,__divtc3@@GCC_4.3.0");
#endif
#endif
