#ifndef _HAVE_FS_H
#define _HAVE_FS_H

typedef void (* File_Iteration)( const char *path );

void iterate_directory( const char *path, File_Iteration );

#endif //_HAVE_FS_H
