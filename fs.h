#ifndef _HAVE_FS_H
#define _HAVE_FS_H

typedef void (* File_Iteration)( const char *path );

void at_fs_location(
    const char *location_string,
    void (*file_action)( const char *name ),
    void (*directory_action)( const char *name ),
    void (*not_found_action)( const char *name )
);

void iterate_directory( const char *path, File_Iteration );

#endif //_HAVE_FS_H
