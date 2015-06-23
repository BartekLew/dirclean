/*
    dirclean.c - a program for cleaning directories, a main program so to speak.
    At the time I write it the code is so staightforward that trying to explain
    it would insult your inteligence, so I don't do it. :-)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fs.h"
#include "prompt.h"

static void user_need_reread_usage( const char *ran_path );
static struct big_picture *handle_directory( struct big_picture *work );
void prompt_group( struct big_picture *work, void *user_data );

static void (*file_handler)( struct big_picture*, void * ) = &prompt_file;

int main( int arguments_count, char **arguments ){
    char *directory = NULL;
    for( int i = 1; i < arguments_count; i++ ){
        if( arguments[i][0] == '-' ){
            if( strcmp( arguments[i], "--group" ) == 0 )
                file_handler = NULL;
            else if( strcmp( arguments[i], "--help" ) == 0 )
                user_need_reread_usage( arguments[0] );
        } else{
            if( directory != NULL )
                user_need_reread_usage( arguments[0] );
            else
                directory = arguments[i];
        }
    }

    if( directory == NULL )
        directory = ".";

    free_work( handle_directory(
        &(struct big_picture){
            .subject = directory
        }
    ) );

    return 0;
}

static struct big_picture
*handle_directory( struct big_picture *work ){
    struct big_picture *result = dirty_map( file_handler,
        without_directories(
            in_file_order(
                work_on_directory( work->subject )
            ),
            &handle_directory
    ), NULL );

    if( file_handler == NULL )
        prompt_file( work, NULL );

    return result;
}

static const char *usage_with_name_masked =
"USAGE: %s [--help] [--group] [directory=.]\n"
"  prompts contents to decide if it should be there.\n"
"  --help prints this message.\n"
"  --group prompt only directories with non-directories in it.\n";

static void user_need_reread_usage( const char *ran_path ){
    printf( usage_with_name_masked, ran_path );
    exit(1);
}
