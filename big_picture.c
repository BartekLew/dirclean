#include "big_picture.h"

#include <stdio.h>
#include <stdlib.h>

#define DEFINE_ALLOCATED_ARRAY( TYPE, NAME, SIZE )\
    TYPE *NAME = (TYPE*) malloc( sizeof( TYPE ) * SIZE );\
    if( !NAME ){\
        fprintf( stderr, "%s,%u: heap ran out.", __FILE__, __LINE__ );\
        exit(1);\
    }

struct big_picture *grow_big_picture( const char *subject ){
    DEFINE_ALLOCATED_ARRAY( struct big_picture, result, 1 );
    result->subject = subject;
    result->next = NULL;
    result->canceled = false;
    return result;
}
