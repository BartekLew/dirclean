#ifndef _HAVE_FS_H
#define _HAVE_FS_H

#include "big_picture.h"

void at_fs_location(
    struct big_picture *work,
    void (*file_action)( struct big_picture *work ),
    void (*directory_action)( struct big_picture *work ),
    void (*not_found_action)( struct big_picture *work )
);

void iterate_directory(
    struct big_picture *work,
    void (*iteration)( struct big_picture *work )
);

#endif //_HAVE_FS_H
