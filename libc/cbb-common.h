/**************************************************/
/*  compiler building blocks: common definitions  */
/**************************************************/

#ifndef __ASSEMBLER__

#ifdef __cplusplus
extern "C" {
#endif


/* namespace */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif


/* a minimal, modernized libiberty */
#include <features.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>


void   xexit(int status);
int    xatexit(void (*function)(void));
void * xcalloc(size_t, size_t);
void * xrealloc(void *, size_t);
char * xstrdup(const char *);
char * xstrndup(const char *, size_t);
char * xstrerror(int);


/* compatibility layer */
#undef  __GLIBC_PREREQ
#define __GLIBC_PREREQ (ig,nored)	(1)

#define _GLIBCXX_BEGIN_NAMESPACE_VERSION
#define _GLIBCXX_END_NAMESPACE_VERSION

#define _GLIBCXX_VISIBILITY(V)		__attribute__ ((__visibility__ (#V)))


#undef  _GLIBCXX_C_LOCALE_GNU
#define _GLIBCXX_C_LOCALE_GNU		(1)

#undef   __GCC_ATOMIC_INT_LOCK_FREE
#define  __GCC_ATOMIC_INT_LOCK_FREE	(2)

#undef   ATOMIC_INT_LOCK_FREE
#define  ATOMIC_INT_LOCK_FREE 		__GCC_ATOMIC_INT_LOCK_FREE


#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLER__ */
