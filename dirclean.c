#include <stdio.h>
#include <stdlib.h>
#include "fs.h"
#include "prompt.h"

static void user_need_reread_usage( const char *ran_path );
static void handle_directory( struct big_picture *work );

int main( int arguments_count, char **arguments ){
    if( arguments_count != 2 )
        user_need_reread_usage(arguments[0]);
    
    struct big_picture *work = 
        grow_big_picture( NULL, arguments[1] );
    handle_directory( work );
    free( work );

    return 0;
}

static void handle_directory( struct big_picture *work ){
    free_work(    
        dirty_map( &prompt_file,
            without_directories(
                in_file_order(
                    work_on_directory( work->subject )
                ),
                &handle_directory
    ) ) );
}

static const char *usage_with_name_masked =
"USAGE: %s directory\n"
"  prompts contents to decide if it should be there.\n";

static void user_need_reread_usage( const char *ran_path ){
    printf( usage_with_name_masked, ran_path );
    exit(1);
}
