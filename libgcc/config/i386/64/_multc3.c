#ifdef SHARED
#ifndef __MIDIPIX
#define __multc3 __multc3_shared
#endif
#endif

#define L_multc3
#include "libgcc2.c"

#ifdef SHARED
#ifndef __MIDIPIX
#undef __multc3
extern __typeof__ (__multc3_shared) __multc3_compat __attribute__((alias ("__multc3_shared")));
#endif

#if !defined(_WIN32) && !defined(__MIDIPIX)
asm (".symver __multc3_compat,__multc3@GCC_4.0.0");
asm (".symver __multc3_shared,__multc3@@GCC_4.3.0");
#endif
#endif
