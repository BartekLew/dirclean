#ifndef _HAVE_BIG_PICTURE_H
#define _HAVE_BIG_PICTURE_H

#include <stdbool.h>
#define ALLOCATOR
#define OPTIONAL

struct big_picture{
    const char *subject;
    struct big_picture *next;
    bool allocated;
};

struct big_picture ALLOCATOR *grow_big_picture(
    struct big_picture *parent,
    const char *subject
);

struct big_picture *dirty_map(
    void (*action)( struct big_picture*, void *user_data ),
    struct big_picture *work,
    void *user_data
);

void cancel_remaining_tasks( struct big_picture *task );
void free_work( struct big_picture *task );

#endif // _HAVE_BIG_PICTURE_H
