#include <stdio.h>
#include <stdlib.h>
#include "fs.h"

static const char *usage_with_name_masked =
"USAGE: %s directory\n"
"  prompts contents to decide if it should be there.\n";

void user_need_reread_usage( const char *ran_path ){
    printf( usage_with_name_masked, ran_path );
    exit(1);
}

static void print_file_path( const char *path ){
    printf( "%s\n", path );
}

int main( int arguments_count, char **arguments ){
    if( arguments_count != 2 )
        user_need_reread_usage(arguments[0]);
    
    iterate_directory( arguments[1], &print_file_path );
      
    return 0;
}
