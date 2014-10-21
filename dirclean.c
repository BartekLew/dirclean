#include <stdio.h>
#include <stdlib.h>
#include "fs.h"
#include "prompt.h"

static void user_need_reread_usage( const char *ran_path );
static void handle_file( struct big_picture *work );
static void print_error( struct big_picture *work );
static void handle_directory( struct big_picture *work );
static void handle_node( const char *work );

int main( int arguments_count, char **arguments ){
    if( arguments_count != 2 )
        user_need_reread_usage(arguments[0]);
    
    handle_node( arguments[1] );

    return 0;
}

static void handle_node( const char *path ){
    at_fs_location(
        path, &handle_file,
        &handle_directory, &print_error
    );
}

static void handle_file( struct big_picture *work ){
    do{
        prompt_file( work );
    } while( !work->canceled );
}

static void print_error( struct big_picture *work ){
    fprintf( stderr, "Error on %s.\n", work->subject );
}

static void handle_directory( struct big_picture *work ){
    iterate_directory( work->subject, &handle_node );
}

static const char *usage_with_name_masked =
"USAGE: %s directory\n"
"  prompts contents to decide if it should be there.\n";

static void user_need_reread_usage( const char *ran_path ){
    printf( usage_with_name_masked, ran_path );
    exit(1);
}
