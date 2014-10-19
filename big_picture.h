#ifndef _HAVE_BIG_PICTURE_H
#define _HAVE_BIG_PICTURE_H

#include <stdbool.h>

#define ALLOCATOR

struct big_picture{
    const char *subject;
    struct big_picture *next;
    bool canceled;
};

struct big_picture ALLOCATOR *grow_big_picture( const char *subject );

#endif // _HAVE_BIG_PICTURE_H
