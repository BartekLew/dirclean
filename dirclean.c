#include <stdio.h>
#include <stdlib.h>
#include "fs.h"
#include "prompt.h"

static void user_need_reread_usage( const char *ran_path );
static struct big_picture *handle_directory( struct big_picture *work );

int main( int arguments_count, char **arguments ){
    if( arguments_count != 2 )
        user_need_reread_usage(arguments[0]);
   
    free_work( handle_directory(
        &(struct big_picture){
            .subject = arguments[1] 
        }
    ) );

    return 0;
}

static struct big_picture
*handle_directory( struct big_picture *work ){
    return dirty_map( &prompt_file,
        without_directories(
            in_file_order(
                work_on_directory( work->subject )
            ),
            &handle_directory
    ), NULL );
}

static const char *usage_with_name_masked =
"USAGE: %s directory\n"
"  prompts contents to decide if it should be there.\n";

static void user_need_reread_usage( const char *ran_path ){
    printf( usage_with_name_masked, ran_path );
    exit(1);
}
