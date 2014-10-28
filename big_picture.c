#include "big_picture.h"

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

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
