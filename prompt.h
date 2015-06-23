/*
    prompt.h - a unit for letting user know what we want from him, that
    is to tell us what to do with all this stuff he left on the drive and
    forgot. :-)
*/

#ifndef _HAVE_PROMPT_H
#define _HAVE_PROMPT_H

#include "big_picture.h"

void prompt_file( struct big_picture *work, void *user_data );

#endif // _HAVE_PROMPT_H
