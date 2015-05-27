#include <stdio.h>
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
    return dirty_map( &html_for_image,
        without_directories(
            work_on_directory( location->subject ),
            &make_galery
        ), NULL
    );
}

void html_for_image( struct big_picture *location, void *user_data ){
    char name[ strlen(location->subject) + 5 ];
    sprintf( name, "%s.html", location->subject );
    
    FILE *file = fopen( name, "w" );
    if( file == NULL ){
        fprintf( stderr,
            " [lsphoto] can't open file for writing."
        );
        return;
    }

    fprintf( file,
        "<html>\n"
        "  <head> <title> %s </title> </head>\n"
        "  <body>\n"
        "    <img style=\"max-width:90%%\" src=\"%s\">\n",
        location->subject, location->subject
    );

    if( location->next != NULL ){
        char next_name[ strlen(location->next->subject) + 5 ];
        sprintf( next_name, "%s.html", location->next->subject );
        fprintf( file,
            "    <a href=\"%s\">%s</a>\n",
            next_name, next_name
        );
    }
    fprintf( file,
        "  </body>\n"
        "</html>"
    );

    fclose(file);
}
