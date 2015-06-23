/*
    lsphoto.c - an another program I wrote using same backend. It create html
    file with images in the directory. It's simple and buggy, but who cares?
    A lollipop for one who does. ;-)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "big_picture.h"
#include "fs.h"

static char *attached_js = NULL;

static struct big_picture *make_galery( struct big_picture* );
void html_for_image( struct big_picture*, void *user_data );

int main( int arguments_count, char **arguments ){
    if( arguments_count == 1 ){
        fprintf( stderr, "[lsphoto] no argument given.\n"
            "lsphoto dir [javascript] - make html galery in directory\n"
            "optionaly js script file [javascript] can be given to be attached\n"
        );
        return 1;
    }

    if( arguments_count == 3 )
        attached_js = arguments[2];

    free_work( make_galery(
        &(struct big_picture){
            .subject = arguments[1]
        } 
    ) );

    return 0;
}

static struct big_picture *
make_galery( struct big_picture *location ){
    FILE *output = fopen( "galery[lsphoto].html", "w" );
    if( output == NULL ){
        fprintf( stderr,
            " [lsphoto] can't open file for writing.\n"
        );
        exit(1);
    }

    fprintf( output, "<html>\n  <body>\n" );

    struct big_picture *result = dirty_map( &html_for_image,
        without_directories(
            work_on_directory( location->subject ),
            &make_galery
        ), (void *) output
    );

    if( attached_js )
        fprintf( output,
            "    <script src=\"%s\" type=\"text/javascript\"></script>\n",
            attached_js
        );

    fprintf( output, "  </body>\n</html>\n" );

    fclose(output);

    return result;
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
