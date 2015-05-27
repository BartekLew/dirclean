#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "big_picture.h"
#include "fs.h"

static struct big_picture *make_galery( struct big_picture* );
void html_for_image( struct big_picture*, void *user_data );

int main( int arguments_count, char **arguments ){
    if( arguments_count == 0 ){
        fprintf( stderr, "[lsphoto] no argument given.\n"
            "lsphoto dir - make html galery in directory" );
        return 1;
    }

    free_work( make_galery( &(struct big_picture){
            .subject = arguments[1]
    } ) );

    return 0;
}

static struct big_picture *
make_galery( struct big_picture *location ){
    FILE *output = fopen( "galery[lsphoto].html", "w" );
    if( output == NULL ){
        fprintf( stderr,
            " [lsphoto] can't open file for writing."
        );
        exit(1);
    }

    fprintf( output, "<html>\n  <body>\n" );

    return dirty_map( &html_for_image,
        without_directories(
            work_on_directory( location->subject ),
            &make_galery
        ), (void *) output
    );

    fprintf( output, "  </body>\n</html>" );

    fclose(output);
}

void html_for_image( struct big_picture *location, void *user_data ){
    char name[ strlen(location->subject) + 5 ];
    sprintf( name, "%s.html", location->subject );
    
    FILE *file = (FILE*) user_data;

    fprintf( file,
        "    <div>\n"
        "      <img style=\"max-width:90%%\" src=\"%s\"><br>\n"
        "      <b>%s</b>\n"
        "    </div>\n",
        location->subject, location->subject
    );
}
