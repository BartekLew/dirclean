/*
   big_picture.h - unit defining a list structure and some functions for
   functional programming.
*/

#ifndef _HAVE_BIG_PICTURE_H
#define _HAVE_BIG_PICTURE_H

#include <stdbool.h>
#define ALLOCATOR
#define OPTIONAL

/*
    the structure. It's just a list of c-strings. allocated field is to know
    if structure was allocated dynamicaly. Another option is to use C99 style
    structure literal, then you skip it so false is automaticaly assigned. And
    free_work function won't make boo-boo. :-)
*/
struct big_picture{
    const char *subject;
    struct big_picture *next;
    bool allocated;
};

/*
    c-tor for the structure. parent can be NULL if we start a new list.
    Otherwise new element is bound to parent->next.
    TODO: if parent->next != NULL it's overwritten. Probably assert would
    be a good option. :-)
*/
struct big_picture ALLOCATOR *grow_big_picture(
    OPTIONAL struct big_picture *parent,
    const char *subject
);

/*
    function for performing map operation. The map is dirty because list
    is mutable, so action() can change it and next calls would see it.
    action is optional, function does nothing in such a case.
*/
struct big_picture *dirty_map(
    OPTIONAL void (*action)( struct big_picture*, void *user_data ),
    struct big_picture *work,
    void *user_data
);

/*
    d-tor. Is careful about staticaly allocated nodes.
*/
void free_work( struct big_picture *task );

#endif // _HAVE_BIG_PICTURE_H
