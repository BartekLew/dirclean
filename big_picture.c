#include "big_picture.h"

#include <stdio.h>
#include <stdlib.h>

#define Alloc( TYPE, NAME, SIZE )\
    TYPE *NAME = (TYPE*) malloc( sizeof( TYPE ) * SIZE );\
    if( !NAME ){\
        fprintf( \
            stderr, "%s,%u: heap ran out.", \
            __FILE__, __LINE__ \
        ); \
        exit(1);\
    }

struct big_picture *grow_big_picture(
    struct big_picture *parent,
    const char *subject
){
    Alloc( struct big_picture, result, 1 );
    result->subject = subject;
    result->next = NULL;

    if( parent ) parent->next = result;
    return result;
}

void end_of_task( struct big_picture *task ){
    struct big_picture *next = task->next;
    task->next = NULL;
    while( next ){
        task = next;
        next = task->next;
        free( task );
    }
}
