#include "fs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void at_fs_location(
    const char *path,
    void (*file_action)( struct big_picture *work ),
    void (*directory_action)( struct big_picture *work ),
    void (*not_found_action)( struct big_picture *work )
){
    struct big_picture *work = grow_big_picture( path );

    struct stat info;
    if( stat( path, &info ) != 0 )
        not_found_action( work );
    else if( S_ISDIR( info.st_mode ) )
        directory_action( work );
    else 
        file_action( work );

    free(work); 
}

    
void iterate_directory( const char *path,
                        File_Iteration iteration)
{
    DIR *target = opendir( path );
    if( target ){
        struct dirent *entry;
        while( ( entry = readdir( target ) ) )
        {
            if( strcmp( entry->d_name, "." ) == 0 || strcmp( entry->d_name, ".." ) == 0 )
                continue;
    
            char *name = malloc( strlen( path ) + strlen( entry->d_name ) + 2 );
            if( !name )
                exit(1);
            sprintf( name, "%s/%s", path, entry->d_name );
    
            iteration( name );
            
            free( name );
        }
    }
}
         
