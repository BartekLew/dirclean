#ifndef _HAVE_FS_H
#define _HAVE_FS_H

#include "big_picture.h"

typedef void (* File_Iteration)( const char *path );

void at_fs_location(
    const char *location_string,
    void (*file_action)( struct big_picture *work ),
    void (*directory_action)( struct big_picture *work ),
    void (*not_found_action)( struct big_picture *work )
);

void iterate_directory( const char *path, File_Iteration );

#endif //_HAVE_FS_H
