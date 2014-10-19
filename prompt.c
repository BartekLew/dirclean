#include "prompt.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void present_file( const char *path );
static bool simple_fork();

static const char *file_prompt =
"What to do with %s?\nsh -c '<your string>' <filepath> > ";
void prompt_file( struct big_picture *work ){
    const char *path = work->subject;
    present_file( path );

    char command[255];
    printf( file_prompt, path );
    scanf( "%255s", command );

    if( strcmp( command, "next" ) == 0 )
        work->canceled = true;
    else if( simple_fork() )
        execl( "/bin/sh", "sh", "-c", command, path, (char*)NULL );
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
