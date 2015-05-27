CC=gcc
CFLAGS=-Wall -pedantic -Werror -g -std=c99 -D_POSIX_SOURCE

all: lsphoto dirclean

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

libcleandir.a: fs.o prompt.o big_picture.o
	ar rcs libcleandir.a fs.o prompt.o big_picture.o

dirclean: dirclean.c libcleandir.a
	${CC} -L. ${CFLAGS} dirclean.c -lcleandir -o dirclean

lsphoto: lsphoto.c libcleandir.a
	${CC} -L. ${CFLAGS} lsphoto.c -lcleandir -o lsphoto

install: dirclean
	cp dirclean ~/.local/bin
