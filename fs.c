#include "fs.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

void iterate_directory( const char *path,
                        File_Iteration iteration)
{
    DIR *target = opendir( path );
    if( !target ){
        printf( "Target %s is not a directory\n", path );
        exit(1);
    }
    
    struct dirent *entry;
    while( ( entry = readdir( target ) ) )
        iteration( entry->d_name );
}
 
