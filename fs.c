#include "fs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void at_fs_location(
    const char *location_string,
    void (*file_action)( const char *name ),
    void (*directory_action)( const char *name ),
    void (*not_found_action)( const char *name )
){
    struct stat info;
    if( stat( location_string, &info ) != 0 )
        not_found_action( location_string );
    else if( S_ISDIR( info.st_mode ) )
        directory_action( location_string );
    else 
        file_action( location_string );
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
         
