#ifndef _HAVE_BIG_PICTURE_H
#define _HAVE_BIG_PICTURE_H

#define ALLOCATOR

struct big_picture{
    const char *subject;
    struct big_picture *next;
};

struct big_picture ALLOCATOR *grow_big_picture(
    struct big_picture *parent,
    const char *subject
);

void end_of_task( struct big_picture *task );

#endif // _HAVE_BIG_PICTURE_H
