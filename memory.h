/*
    memory.h - I leave it without comment. Maybe some day? ;-)
*/

#ifndef _HAVE_MEMORY_H
#define _HAVE_MEMORY_H

#define Alloc( TYPE, NAME, SIZE )\
    TYPE *NAME = (TYPE*) malloc( sizeof( TYPE ) * SIZE );\
    if( !NAME ){\
        fprintf( \
            stderr, "%s,%u: heap ran out.", \
            __FILE__, __LINE__ \
        ); \
        exit(1);\
    }

#endif // _HAVE_MEMORY_H
