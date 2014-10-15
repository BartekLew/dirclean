#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <dirent.h>

void user_need_reread_usage( const char *ran_path ){
    printf(
        "USAGE: %s directory\n"
        "  prompts contents to decide if it should be there.\n"
        , ran_path
    );
    exit(1);
}

#define user_need_reread_usage user_need_reread_usage( arguments[0] );

int main( int arguments_count, char **arguments ){
    if( arguments_count != 2 )
        user_need_reread_usage
    
    DIR *target = opendir( arguments[1] );
    if( !target )
        user_need_reread_usage 
    
    struct dirent *entry;
    while( ( entry = readdir( target ) ) )
        printf( "%s\n", entry->d_name );
    
    return 0;
}
