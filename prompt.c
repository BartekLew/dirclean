#include "prompt.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define String_array( CONTENT ) \
    (char*[]){ CONTENT, NULL }

// for some reason not loaded from stdlib:
void setenv( const char *, const char *, int );

static void present_file( const char *path );
static bool simple_fork();

static const char *intro = "$file = %s\n";
void prompt_file( struct big_picture *work ){
    const char *path = work->subject;
    present_file( path );

    char *shell = getenv( "SHELL" );
    setenv( "file", path, true );

    printf( intro, path );
    if( simple_fork() )
        execv( shell, String_array( shell ) );
}

static void present_file( const char *path ){
    const char *command = NULL;
    const char *extension = path + strlen(path) - 4;

    if( strcmp( extension, ".mp3" ) == 0
        || strcmp( extension, ".ogg" ) == 0 )
        command = "/usr/bin/mplayer";

    if( command ){
        if( simple_fork() )
            execl( command, command, path, (char*)NULL );
    }
}

static bool simple_fork(){
    pid_t child_pid = fork();
    if( child_pid < 0 )
        printf( "%s:%u: fork failed", __FILE__, __LINE__ );
    else if ( child_pid != 0 )
        waitpid( child_pid, NULL, 0 );
    else return true;

    return false;
}
