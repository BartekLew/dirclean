#include <stdio.h>
#include <stdlib.h>
#include "fs.h"
#include "prompt.h"

static void user_need_reread_usage( const char *ran_path );
static void print_error( const char *path );
static void print_directory( const char *path );
static void print_from_fs( const char *path );

int main( int arguments_count, char **arguments ){
    if( arguments_count != 2 )
        user_need_reread_usage(arguments[0]);
    
    print_from_fs( arguments[1] );
          
    return 0;
}

static void print_from_fs( const char *path ){
    at_fs_location(
        path, &prompt_file, &print_directory,
        &print_error
    );
}

static void print_error( const char *path ){
    fprintf( stderr, "Error on %s.\n", path );
}

static void print_directory( const char *path ){
    iterate_directory( path, &print_from_fs );
}

static const char *usage_with_name_masked =
"USAGE: %s directory\n"
"  prompts contents to decide if it should be there.\n";

static void user_need_reread_usage( const char *ran_path ){
    printf( usage_with_name_masked, ran_path );
    exit(1);
}
