CC=gcc
CFLAGS=-Wall -pedantic -Werror -g -std=c99 -D_POSIX_SOURCE

dirclean: dirclean.c fs.c prompt.c big_picture.c
	${CC} ${CFLAGS} dirclean.c prompt.c fs.c big_picture.c -o dirclean
