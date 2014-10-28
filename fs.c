#include "fs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "memory.h"

void at_fs_location(
    struct big_picture *work,
    void (*file_action)( struct big_picture *work ),
    void (*directory_action)( struct big_picture *work ),
    void (*not_found_action)( struct big_picture *work )
){
    struct stat info;
    if( stat( work->subject, &info ) != 0 )
        not_found_action( work );
    else if( S_ISDIR( info.st_mode ) )
        directory_action( work );
    else 
        file_action( work );
}

    
struct big_picture *work_on_directory( const char *path ){
    struct big_picture seed = { .next = NULL },
                       *last = &seed;

    DIR *target = opendir( path );
    if( target ){
        struct dirent *entry;
        while( ( entry = readdir( target ) ) )
        {
            if( strcmp( entry->d_name, "." ) == 0 
             || strcmp( entry->d_name, ".." ) == 0 )
                continue;
    
            Alloc(
                char, name, 
                strlen( path ) +
                strlen( entry->d_name ) + 2
            );

            sprintf(
                name, "%s/%s",
                path, entry->d_name
            );
    
            last = grow_big_picture( last, name );
        }

        closedir( target );
    }

    return seed.next;
}
        
