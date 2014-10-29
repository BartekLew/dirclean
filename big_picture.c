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

struct big_picture *dirty_map(
    void (*action)( struct big_picture* ),
    struct big_picture *work
){
    struct big_picture *current = work;
    while( current ){
        action( current );
        current = current->next;
    }
    return work;
}

void free_work( struct big_picture *task ){
    while( task ){
        struct big_picture *next = task->next;
        free( (void*)task->subject );
        free( task );
        task = next;
    }
}

void cancel_remaining_tasks( struct big_picture *task ){
    free_work( task->next );
    task->next = NULL;
}
