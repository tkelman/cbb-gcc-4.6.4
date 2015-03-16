#define _GNU_SOURCE

#include <stddef.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

#include <config.h>

void   xexit(int status) 			{_exit(status); return;}
int    xatexit(void (*function)(void))		{return atexit(function);}
void * xcalloc(size_t nmemb, size_t size)	{return calloc(nmemb,size);}
void * xrealloc(void *ptr, size_t size) 	{return realloc(ptr,size);}
char * xstrdup(const char *s)			{return strdup(s);}
char * xstrndup(const char *s, size_t n)	{return strndup(s,n);}
char * xstrerror(int errnum)			{return strerror(errnum);}
void * xmalloc(size_t block_size)		{return malloc(block_size);}

void * xmemdup (const void * src, size_t copy_size, size_t alloc_size)
{
	void * dst = calloc (1, alloc_size);
	return dst ? memcpy(dst, src, copy_size) : 0;
}

void xmalloc_set_program_name (const char *s)
{
	return;
}

void xmalloc_failed (size_t size)
{
	fputs("malloc failed, aborting.\n\0",stderr);
	_exit(1);
}
