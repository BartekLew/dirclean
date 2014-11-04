#include "fs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "memory.h"

struct big_picture *work_on_directory( const char *path ){
    struct big_picture seed = { .next = NULL },
                       *last = &seed;

    DIR *target = opendir( path );
    if( target ){
        struct dirent *entry;
        while( ( entry = readdir( target ) ) )
        {
            if( strcmp( entry->d_name, "." ) == 0 
             || strcmp( entry->d_name, ".." ) == 0 )
                continue;
    
            Alloc(
                char, name, 
                strlen( path ) +
                strlen( entry->d_name ) + 2
            );

            sprintf(
                name, "%s/%s",
                path, entry->d_name
            );
    
            last = grow_big_picture( last, name );
        }

        closedir( target );
    }

    return seed.next;
}
        
struct big_picture *in_file_order( struct big_picture *work ){
    if( !work )
        return NULL;

    struct big_picture *order_start = work,
                       *mess = work->next;
    order_start->next = NULL;

    while( mess ){
        if( strcmp(
                mess->subject,
                order_start->subject
            ) <= 0 ){
            struct big_picture *more_mess = mess->next;
            mess->next = order_start;
            order_start = mess;
            mess = more_mess;
        } else {
            struct big_picture *fit = order_start;
            while( fit->next && strcmp(
                       fit->next->subject,
                       mess->subject
                   ) <= 0 )
                fit = fit->next;
            struct big_picture *more_mess = mess->next;
            mess->next = fit->next;
            fit->next = mess;
            mess = more_mess;
        }
    }

    return order_start;
}

struct big_picture *without_directories(
    struct big_picture *work,
    struct big_picture *(*directory_action)(
        struct big_picture*
    )
){
    struct big_picture predecessor = { .next = work };
    struct big_picture *cursor = &predecessor;

    while( cursor->next ){
        struct stat info;
        if( stat( work->subject, &info ) == 0 
            && S_ISDIR( info.st_mode )
        ){
            directory_action( cursor->next );
            struct big_picture *to_remove = cursor->next;
            cursor->next = cursor->next->next;
            if( to_remove->allocated )
                free( to_remove );
        } else
            cursor = cursor->next;
    }

    return predecessor.next;
}
