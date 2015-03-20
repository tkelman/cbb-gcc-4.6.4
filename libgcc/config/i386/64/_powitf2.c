#ifdef SHARED
#ifndef __MIDIPIX
#define __powitf2 __powitf2_shared
#endif
#endif

#define L_powitf2
#include "libgcc2.c"

#ifdef SHARED
#ifndef __MIDIPIX
#undef __powitf2
extern __typeof__ (__powitf2_shared) __powitf2_compat __attribute__((alias ("__powitf2_shared")));
#endif

#if !defined(_WIN32) && !defined(__MIDIPIX)
asm (".symver __powitf2_compat,__powitf2@GCC_4.0.0");
asm (".symver __powitf2_shared,__powitf2@@GCC_4.3.0");
#endif
#endif
