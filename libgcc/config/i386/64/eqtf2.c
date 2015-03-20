#ifdef SHARED
#ifndef __MIDIPIX
#define __netf2 __netf2_shared
#endif
#endif

#include "config/soft-fp/eqtf2.c"

#ifdef SHARED
#ifndef __MIDIPIX
#undef __netf2
strong_alias (__netf2_shared, __netf2_compat);
#endif

#if !defined(_WIN32) && !defined(__MIDIPIX)
asm (".symver __netf2_compat,__netf2@GCC_3.0");
asm (".symver __netf2_shared,__netf2@@GCC_4.3.0");
#endif
#endif
