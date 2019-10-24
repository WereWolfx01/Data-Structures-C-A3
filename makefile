CFLAGS = -ansi -pedantic -Wall
CC = gcc
COMMON = common.h
BINARY = binary.h
NAME = name.h
TITLE = title.h
PRINCIPALS = principals.h

all: binary name title principals a3

binary: $(COMMON) binary.c
	$(CC) $(CFLAGS) binary.c -o binary.o -c

name: $(COMMON) $(BINARY) name.c
	$(CC) $(CFLAGS) name.c -o name.o -c

title: $(COMMON) $(BINARY) title.c
	$(CC) $(CFLAGS) title.c -o title.o -c

principals: $(COMMON) $(BINARY) principals.c
	$(CC) $(CFLAGS) principals.c -o principals.o -c

a3: $(COMMON) $(BINARY) $(NAME) $(TITLE) $(PRINCIPALS) a3.c binary name title principals
	$(CC) $(CFLAGS) a3.c binary.o name.o title.o principals.o -o a3

clean:
	rm *.o
