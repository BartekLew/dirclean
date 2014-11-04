#ifndef _HAVE_FS_H
#define _HAVE_FS_H

#include "big_picture.h"

struct big_picture ALLOCATOR
*work_on_directory( const char *path );

struct big_picture
*in_file_order( struct big_picture *work );

struct big_picture *without_directories(
    struct big_picture *work,
    struct big_picture *(*directory_action)(
        struct big_picture*
    )
);

#endif //_HAVE_FS_H
