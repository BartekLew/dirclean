#include "fs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

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

    
void iterate_directory(
    struct big_picture *work,
    void (*iteration)( struct big_picture *work )
){
    grow_big_picture( work, work->subject );

    DIR *target = opendir( work->subject );
    if( target ){
        struct dirent *entry;
        while( ( entry = readdir( target ) ) )
        {
            if( strcmp( entry->d_name, "." ) == 0 
             || strcmp( entry->d_name, ".." ) == 0 )
                continue;
    
            char *name = malloc(
                strlen( work->subject ) +
                strlen( entry->d_name ) + 2
            );
            if( !name )
                exit(1);

            sprintf(
                name, "%s/%s",
                work->subject, entry->d_name
            );
    
            work->next->subject = name;
            iteration( work->next );
            free( name );

            if( work->next->canceled )
                break;
        }

        closedir( target );
    }

    free( work->next );
}
         
