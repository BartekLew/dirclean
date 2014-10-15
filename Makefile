CC=gcc
CFLAGS=-Wall -pedantic -Werror -std=c99 -D_POSIX_SOURCE

dirclean: dirclean.c fs.c
	${CC} ${CFLAGS} dirclean.c fs.c -o dirclean