/*
    fs.h - unit with functions creating big_pictures that reflect filesystem
    and manipulating them.
*/

#ifndef _HAVE_FS_H
#define _HAVE_FS_H

#include "big_picture.h"

/*
    c-tor. Creates list with names of files found on given path.
    Random order, as readdir return.
*/
struct big_picture ALLOCATOR
*work_on_directory( const char *path );

/*
    Sort the list.
*/
struct big_picture
*in_file_order( struct big_picture *work );

/*
    Filter list against directories. Returns list with non-directories only,
    but first call directory_action() for each directory found there.
*/
struct big_picture *without_directories(
    struct big_picture *work,
    struct big_picture *(*directory_action)(
        struct big_picture*
    )
);

#endif //_HAVE_FS_H
