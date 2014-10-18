#include "prompt.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static const char *file_prompt =
"What to do with %s?\nsh -c '<your string>' <filepath> > ";
void prompt_file( const char *path ){
    char command[255];
    printf( file_prompt, path );
    fgets( command, 255, stdin );

    pid_t child_pid = fork();
    if( child_pid < 0 )
        printf( "%s:%u: fork failed", __FILE__, __LINE__ );
    else if( child_pid == 0 )
        execl( "/bin/sh", "sh", "-c", command, path, (char*)NULL );
    else
        waitpid( child_pid, NULL, 0 );
}

