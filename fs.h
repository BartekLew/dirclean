#ifndef _HAVE_FS_H
#define _HAVE_FS_H

#include "big_picture.h"

void at_fs_location(
    struct big_picture *work,
    void (*file_action)( struct big_picture *work ),
    void (*directory_action)( struct big_picture *work ),
    void (*not_found_action)( struct big_picture *work )
);

struct big_picture ALLOCATOR
*work_on_directory( const char *path );

struct big_picture
*in_file_order( struct big_picture *work );

struct big_picture *without_directories(
    struct big_picture *work,
    void (*directory_action)( struct big_picture* )
);

#endif //_HAVE_FS_H
