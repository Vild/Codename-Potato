#ifndef STDDEF_H
#define STDDEF_H

typedef unsigned int size_t;

#define UINT_MAX 4294967295

#undef NULL
#define NULL ((void *)0)

#define offsetof(st, m) \
    ((size_t)((char*)&((st*)(0))->m - (char*)0))
#endif